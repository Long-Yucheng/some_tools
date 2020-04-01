#include "KafkaProducerClient.h"

KafkaProducerClient::KafkaProducerClient()
{
    m_kafka_handle = NULL;
    m_kafka_conf = NULL;
    m_partitionCount = 0;
}

//注意：千万不要调用 rd_kafka_conf_destroy， 会导致段错误，官方例子也没有调用
KafkaProducerClient::~KafkaProducerClient()
{
    rd_kafka_flush(m_kafka_handle, 10 * 1000); //wait for max 10 seconds       
    freeTopicMap();
    rd_kafka_destroy(m_kafka_handle);
}

void KafkaProducerClient::freeTopicMap()
{
    std::map<std::string, rd_kafka_topic_t *>::iterator it = m_mapStrTopic2RdTopic.begin();

    for (; it != m_mapStrTopic2RdTopic.end();)
    {
        rd_kafka_topic_destroy(it->second);
        it = m_mapStrTopic2RdTopic.erase(it);
    }

    m_mapStrTopic2RdTopic.clear();
}

int32_t KafkaProducerClient::init(std::string brokers)
{
    int32_t ret = 0;
    rd_kafka_conf_res_t ret_conf = RD_KAFKA_CONF_OK;
    char errstr[512] = { 0 };

    m_kafka_conf = rd_kafka_conf_new();

    rd_kafka_conf_set_dr_msg_cb(m_kafka_conf, dr_msg_cb);
    rd_kafka_conf_set_error_cb(m_kafka_conf, err_cb);
    rd_kafka_conf_set_throttle_cb(m_kafka_conf, throttle_cb);
    rd_kafka_conf_set_offset_commit_cb(m_kafka_conf, offset_commit_cb);
    rd_kafka_conf_set_stats_cb(m_kafka_conf, stats_cb);

    //---------Producer config-------------------
    ret_conf = rd_kafka_conf_set(m_kafka_conf, "queue.buffering.max.messages", "10000000", errstr, sizeof(errstr));

    if (ret_conf != RD_KAFKA_CONF_OK) { 
        printf("Error: rd_kafka_conf_set() failed 1; ret_conf=%d; errstr:%s\n", ret_conf, errstr); 
        return -1; 
    }

    ret_conf = rd_kafka_conf_set(m_kafka_conf, "message.send.max.retries", "3", errstr, sizeof(errstr));

    if (ret_conf != RD_KAFKA_CONF_OK) { 
        printf("Error: rd_kafka_conf_set() failed 2; ret_conf=%d; errstr:%s\n", ret_conf, errstr); 
        return -1; 
    }

    ret_conf = rd_kafka_conf_set(m_kafka_conf, "retry.backoff.ms", "500", errstr, sizeof(errstr));

    if (ret_conf != RD_KAFKA_CONF_OK) { 
        printf("Error: rd_kafka_conf_set() failed 3; ret_conf=%d; errstr:%s\n", ret_conf, errstr); 
        return -1; 
    }

    //---------Add broker(s)-------------------
    //另外，可以使用 rd_kafka_brokers_add 进行动态的broker添加
    ret_conf = rd_kafka_conf_set(m_kafka_conf, "bootstrap.servers", brokers.data(), errstr, sizeof(errstr)); 
    if (ret_conf != RD_KAFKA_CONF_OK) { 
        printf("Error: set brokers failed; ret_conf=%d; errstr:%s\n", ret_conf, errstr); 
        return -1; 
    }
    
    //---------Create Kafka handle-------------------
    m_kafka_handle = rd_kafka_new(RD_KAFKA_PRODUCER, m_kafka_conf, errstr, sizeof(errstr));
    if (m_kafka_handle == NULL) { 
        printf("Error: Failed to create Kafka producer: %s\n", errstr); 
        return -1; 
    }

    return ret;
}

int32_t KafkaProducerClient::addTopic(std::string topic)
{
    rd_kafka_topic_t* kafka_topic = rd_kafka_topic_new(m_kafka_handle, topic.data(), NULL); //Explicitly create topic to avoid per-msg lookups
    m_mapStrTopic2RdTopic.insert(std::pair<std::string, rd_kafka_topic_t *>(topic, kafka_topic));

    return 0;
}

int32_t KafkaProducerClient::getPartitonCount(std::string topic)
{
    if (topic.empty())
    {
        return 0;
    }

    std::map<std::string, rd_kafka_topic_t *>::iterator it = m_mapStrTopic2RdTopic.find(topic);

    if (it == m_mapStrTopic2RdTopic.end())
    {
        return -1;
    }

    rd_kafka_topic_t * rkt = it->second;

    rd_kafka_resp_err_t err;
    const struct rd_kafka_metadata *metadata;

    /* Fetch metadata */
    err = rd_kafka_metadata(m_kafka_handle, rkt ? 0 : 1, rkt, &metadata, 5000);

    if (err != RD_KAFKA_RESP_ERR_NO_ERROR) {
        printf("%% Failed to acquire metadata: %s\n", rd_kafka_err2str(err));
    }

    size_t i = 0;

    for (; i < metadata->topic_cnt; i++)
    {
        const struct rd_kafka_metadata_topic *t = &metadata->topics[i];

        std::string metaTopic(t->topic);

        if (topic == metaTopic)
        {
            m_partitionCount = t->partition_cnt;
            break;
        }
    }

    rd_kafka_metadata_destroy(metadata);

    return m_partitionCount;
}

int32_t KafkaProducerClient::sendMessage(std::string topic, int32_t partition, char *buf, int32_t len)
{
    int32_t ret = 0;

    if (topic.empty() 
        //|| partition < 0 
        //|| partition >= m_partitionCount 
        || buf == NULL
        || len <= 0) 
    {
        return -1; 
    }
 
    std::map<std::string, rd_kafka_topic_t *>::iterator it = m_mapStrTopic2RdTopic.find(topic);

    if (it == m_mapStrTopic2RdTopic.end())
    {
        return -2;
    }

    rd_kafka_topic_t * kafka_topic = it->second;

    //------------向kafka服务器发送消息----------------
    ret = rd_kafka_produce(kafka_topic, partition, RD_KAFKA_MSG_F_COPY, buf, len, NULL, 0, NULL);

    if (ret == -1)
    {
        rd_kafka_resp_err_t err = rd_kafka_last_error();

        if (err == RD_KAFKA_RESP_ERR__UNKNOWN_PARTITION)
        {
            printf("Error: No such partition: %"PRId32"\n", partition);
        }
        else
        {
            printf("Error: produce error: %s%s\n", rd_kafka_err2str(err), err == RD_KAFKA_RESP_ERR__QUEUE_FULL ? " (backpressure)" : "");
        }

        rd_kafka_poll(m_kafka_handle, 10); //Poll to handle delivery reports

        ret = -2;
        return ret;
    }

    ret = rd_kafka_poll(m_kafka_handle, 0);

    return ret;
}


void KafkaProducerClient::dr_msg_cb(rd_kafka_t *rk, const rd_kafka_message_t *rkmessage, void *opaque)
{
    if (rkmessage->err)
        printf("%% Message delivery failed: %s\n", rd_kafka_err2str(rkmessage->err));
    else
        printf("%% Message delivered (%zd bytes, partition %"PRId32")\n", rkmessage->len, rkmessage->partition);
}

void KafkaProducerClient::err_cb(rd_kafka_t *rk, int err, const char *reason, void *opaque)
{
    printf("%% ERROR CALLBACK: %s: %s: %s\n", rd_kafka_name(rk), rd_kafka_err2str((rd_kafka_resp_err_t)err), reason);
}

void KafkaProducerClient::throttle_cb(rd_kafka_t *rk, const char *broker_name, int broker_id, int throttle_time_ms, void *opaque)
{
    printf("%% THROTTLED %dms by %s (%"PRId32")\n", throttle_time_ms, broker_name, broker_id);
}

void KafkaProducerClient::offset_commit_cb(rd_kafka_t *rk, rd_kafka_resp_err_t err, rd_kafka_topic_partition_list_t *offsets, void *opaque)
{
    printf("==== offset_commit_cb \n");
    int i;
    int verbosity = 1;

    if (err || verbosity >= 2)
    {
        printf("%% Offset commit of %d partition(s): %s\n", offsets->cnt, rd_kafka_err2str(err));
    }

    for (i = 0; i < offsets->cnt; i++)
    {
        rd_kafka_topic_partition_t * rktpar = &offsets->elems[i];

        if (rktpar->err || verbosity >= 2)
        {
            printf("%%  %s [%"PRId32"] @ %"PRId64": %s\n", rktpar->topic, rktpar->partition, rktpar->offset, rd_kafka_err2str(err));
        }
    }
}

int KafkaProducerClient::stats_cb(rd_kafka_t *rk, char *json, size_t json_len, void *opaque)
{
    printf("%s\n", json);
    return 0;
}

