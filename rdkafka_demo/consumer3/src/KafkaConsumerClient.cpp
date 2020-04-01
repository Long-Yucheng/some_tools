#include "KafkaConsumerClient.h"

static int is_printable(const char *buf, size_t size) {
    size_t i;

    for (i = 0; i < size; i++)
        if (!isprint((int)buf[i]))
            return 0;

    return 1;
}

KafkaConsumerClient::KafkaConsumerClient()
{
    m_kafka_handle = NULL;
    m_consumer_callback = NULL;
    m_consumer_callback_param = NULL;
}

KafkaConsumerClient::~KafkaConsumerClient()
{
    rd_kafka_flush(m_kafka_handle, 10 * 1000); //wait for max 10 seconds
    rd_kafka_destroy(m_kafka_handle);
}

int32_t KafkaConsumerClient::initConfig(char *brokers, char *groupId)
{
    rd_kafka_conf_t * kafka_conf = rd_kafka_conf_new();
    rd_kafka_conf_set_error_cb(kafka_conf, err_cb);
    rd_kafka_conf_set_throttle_cb(kafka_conf, throttle_cb);
    rd_kafka_conf_set_offset_commit_cb(kafka_conf, offset_commit_cb);
    rd_kafka_conf_set_stats_cb(kafka_conf, stats_cb);
    rd_kafka_conf_set_log_cb(kafka_conf, logger);

    //---------Consumer config-------------------
    // 默认的配置，请参考文档：https://github.com/edenhill/librdkafka/blob/master/CONFIGURATION.md

    rd_kafka_conf_res_t ret_conf = RD_KAFKA_CONF_OK;
    char errstr[512] = { 0 };

    // add brokers
    if ((ret_conf = rd_kafka_conf_set(kafka_conf, "bootstrap.servers", brokers, errstr, sizeof(errstr))) != RD_KAFKA_CONF_OK) {
        printf("Error: rd_kafka_conf_set() failed 1; ret_conf=%d; errstr:%s\n", ret_conf, errstr);
        rd_kafka_conf_destroy(kafka_conf);
        return -1;
    }

    // 设置消费组
    if ((ret_conf = rd_kafka_conf_set(kafka_conf, "group.id", groupId, errstr, sizeof(errstr))) != RD_KAFKA_CONF_OK) {
        printf("Error: rd_kafka_conf_set() failed 2; ret_conf=%d; errstr:%s\n", ret_conf, errstr);
        return -1;
    }

    if ((ret_conf = rd_kafka_conf_set(kafka_conf, "queued.min.messages", "1000000", errstr, sizeof(errstr))) != RD_KAFKA_CONF_OK) {
        printf("Error: rd_kafka_conf_set() failed 3; ret_conf=%d; errstr:%s\n", ret_conf, errstr);
        return -1;
    }

    if ((ret_conf = rd_kafka_conf_set(kafka_conf, "session.timeout.ms", "6000", errstr, sizeof(errstr))) != RD_KAFKA_CONF_OK) {
        printf("Error: rd_kafka_conf_set() failed 4; ret_conf=%d; errstr:%s\n", ret_conf, errstr);
        return -1;
    }

    if ((ret_conf = rd_kafka_conf_set(kafka_conf, "auto.offset.reset", "largest", errstr, sizeof(errstr))) != RD_KAFKA_CONF_OK) {
        printf("Error: rd_kafka_conf_set() failed 5; ret_conf=%d; errstr:%s\n", ret_conf, errstr);
        rd_kafka_conf_destroy(kafka_conf);
        return -1;
    }

    //---------Create Kafka handle-------------------
    m_kafka_handle = rd_kafka_new(RD_KAFKA_CONSUMER, kafka_conf, errstr, sizeof(errstr));

    if (m_kafka_handle == NULL)
    {
        printf("Error: Failed to create Kafka producer: %s\n", errstr);
        return -2;
    }

    kafka_conf = NULL;  //rdkafka 官方例子解释，已经释放了，直接给NULL就好 https://github.com/edenhill/librdkafka/blob/master/examples/consumer.c

    return 0;
}

int32_t KafkaConsumerClient::subTopic(std::vector<std::string> topics)
{
    if (topics.empty()) { return -1; }

    rd_kafka_poll_set_consumer(m_kafka_handle); //Redirect rd_kafka_poll() to consumer_poll()

    // 订阅
    rd_kafka_topic_partition_list_t *subscription;
    uint32_t topic_cnt = topics.size();
    subscription = rd_kafka_topic_partition_list_new(topic_cnt);

    uint32_t i = 0;
    for (i = 0; i < topic_cnt; i++)
        rd_kafka_topic_partition_list_add(subscription,
            topics[i].data(),
            /* the partition is ignored
             * by subscribe() */
            RD_KAFKA_PARTITION_UA);

    rd_kafka_resp_err_t err;
    err = rd_kafka_subscribe(m_kafka_handle, subscription);

    if (err) {
        printf("%% Failed to subscribe to %d topics: %s\n",
            subscription->cnt, rd_kafka_err2str(err));
        rd_kafka_topic_partition_list_destroy(subscription);
        rd_kafka_destroy(m_kafka_handle);
        return -3;
    }

    printf("%% Subscribed to %d topic(s), "
        "waiting for rebalance and messages...\n",
        subscription->cnt);

    rd_kafka_topic_partition_list_destroy(subscription);

    return 0;
}

int KafkaConsumerClient::getMessage()
{
    while (1) {
        rd_kafka_message_t *rkm;

        rkm = rd_kafka_consumer_poll(m_kafka_handle, 100);
        if (!rkm)
            continue; /* Timeout: no message within 100ms,
                       *  try again. This short timeout allows
                       *  checking for `run` at frequent intervals.
                       */

                       /* consumer_poll() will return either a proper message
                        * or a consumer error (rkm->err is set). */
        if (rkm->err) {
            /* Consumer errors are generally to be considered
             * informational as the consumer will automatically
             * try to recover from all types of errors. */
            printf("%% Consumer error: %s\n",
                rd_kafka_message_errstr(rkm));
            rd_kafka_message_destroy(rkm);
            continue;
        }

        /* Proper message. */
        printf("Message on %s [%"PRId32"] at offset %"PRId64":\n",
            rd_kafka_topic_name(rkm->rkt), rkm->partition,
            rkm->offset);

        /* Print the message key. */
        if (rkm->key && is_printable((const char *)rkm->key, rkm->key_len))
            printf(" Key: %.*s\n",
            (int)rkm->key_len, (const char *)rkm->key);
        else if (rkm->key)
            printf(" Key: (%d bytes)\n", (int)rkm->key_len);

        /* Print the message value/payload. */
        if (rkm->payload && is_printable((const char *)rkm->payload, rkm->len))
            printf(" Value: %.*s\n",
            (int)rkm->len, (const char *)rkm->payload);
        else if (rkm->key)
            printf(" Value: (%d bytes)\n", (int)rkm->len);

        rd_kafka_message_destroy(rkm);
    }


    /* Close the consumer: commit final offsets and leave the group. */
    fprintf(stderr, "%% Closing consumer\n");
    rd_kafka_consumer_close(m_kafka_handle);


    /* Destroy the consumer */
    rd_kafka_destroy(m_kafka_handle);

    return 0;
}

void KafkaConsumerClient::err_cb(rd_kafka_t *rk, int err, const char *reason, void *opaque)
{
    printf("%% ERROR CALLBACK: %s: %s: %s\n", rd_kafka_name(rk), rd_kafka_err2str((rd_kafka_resp_err_t)err), reason);
}

void KafkaConsumerClient::throttle_cb(rd_kafka_t *rk, const char *broker_name, int32_t broker_id, int throttle_time_ms, void *opaque)
{
    printf("%% THROTTLED %dms by %s (%"PRId32")\n", throttle_time_ms, broker_name, broker_id);
}

void KafkaConsumerClient::offset_commit_cb(rd_kafka_t *rk, rd_kafka_resp_err_t err, rd_kafka_topic_partition_list_t *offsets, void *opaque)
{
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

int KafkaConsumerClient::stats_cb(rd_kafka_t *rk, char *json, size_t json_len, void *opaque)
{
    printf("%s\n", json);
    return 0;
}

void KafkaConsumerClient::logger(const rd_kafka_t *rk, int level, const char *fac, const char *buf)
{
    fprintf(stdout, "RDKAFKA-%i-%s: %s: %s\n", level, fac, rd_kafka_name(rk), buf);
}

void KafkaConsumerClient::msg_consume(rd_kafka_message_t *rkmessage, void *opaque)
{
    printf("--- into KafkaConsumerClient::msg_consume");
    KafkaConsumerClient * p = (KafkaConsumerClient *)opaque;

    if (p && p->m_consumer_callback)
    {
        p->m_consumer_callback(rkmessage, p->m_consumer_callback_param);
        return;
    }

    if (rkmessage->err)
    {
        if (rkmessage->err == RD_KAFKA_RESP_ERR__PARTITION_EOF)
        {
            printf("[INFO] Consumer reached end of %s [%"PRId32"] message queue at offset %"PRId64"\n", rd_kafka_topic_name(rkmessage->rkt), rkmessage->partition, rkmessage->offset);
            return;
        }

        printf("Error: Consume error for topic \"%s\" [%"PRId32"] offset %"PRId64": %s\n", rkmessage->rkt ? rd_kafka_topic_name(rkmessage->rkt) : "", rkmessage->partition, rkmessage->offset, rd_kafka_message_errstr(rkmessage));

        return;
    }

    if (rkmessage->key_len)
    {
        printf("Key: %d: %s\n", (int)rkmessage->key_len, (char *)rkmessage->key);
    }

    printf("%d: %s\n", (int)rkmessage->len, (char *)rkmessage->payload);
}


