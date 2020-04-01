#pragma once

#include <map>
#include <string>

#include "rdkafka.h"

class KafkaProducerClient
{
public:
    KafkaProducerClient();
    ~KafkaProducerClient();

    int32_t init(std::string brokers); //brokers="192.168.1.42:9092,192.168.1.43:9092"; 
    int32_t addTopic(std::string topic);
    int32_t getPartitonCount(std::string topic); //获取某个topic的partition数量
    int32_t sendMessage(std::string topic, int32_t partition, char *str, int32_t len); //向kafka服务器发送消息
    

private:
    static void dr_msg_cb(rd_kafka_t *rk, const rd_kafka_message_t *rkmessage, void *opaque);
    static void err_cb(rd_kafka_t *rk, int err, const char *reason, void *opaque);
    static void throttle_cb(rd_kafka_t *rk, const char *broker_name, int broker_id, int throttle_time_ms, void *opaque);
    static void offset_commit_cb(rd_kafka_t *rk, rd_kafka_resp_err_t err, rd_kafka_topic_partition_list_t *offsets, void *opaque);
    static int stats_cb(rd_kafka_t *rk, char *json, size_t json_len, void *opaque);

    void freeTopicMap();
private:
    rd_kafka_t *                         m_kafka_handle;  //kafka消息生产者句柄
    rd_kafka_conf_t *                    m_kafka_conf;    //kafka消息配置

    std::map<std::string, rd_kafka_topic_t *> m_mapStrTopic2RdTopic;

    uint32_t m_partitionCount; //partition 数量
};

