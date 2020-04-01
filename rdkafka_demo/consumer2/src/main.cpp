#include <iostream>

#include "KafkaConsumerClient.h"

static void msg_consume(rd_kafka_message_t *rkmessage, void *opaque)
{
    printf("---[MSG] %d: %s\n", (int)rkmessage->len, (char *)rkmessage->payload);
}


int main(int argc, char *argv[])
{
    KafkaConsumerClient kc;

    std::vector<std::string> topics;
    topics.push_back("test");

    char brokers[] = "49.7.18.30:9092,49.7.18.31:9092,49.7.18.32:9092";

    char groupId[] = "my_group1";
    consumer_callback consumer_cb = msg_consume; //注册消息回调函数，用户可以自定义此函数
    void * param_cb = NULL; //param_cb=this;
    int ret = 0;

    ret = kc.init(topics, brokers, groupId, consumer_cb, param_cb);
    if (ret != 0) { printf("Error: kc.init(): ret=%d;\n", ret); return 0; }

    ret = kc.getMessage(); //从kafka服务器接收消息
    if (ret != 0) { printf("Error: kc.getMessage(): ret=%d;\n", ret); return 0; }

    return 0;
}