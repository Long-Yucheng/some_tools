#include <string>
#include <iostream>

#include <stdio.h>
#include <string.h>

#include "KafkaProducerClient.h"

int main()
{
    std::string topic = "test2";
    std::string brokers = "14.17.118.245:9092";

    char str_msg[] = "Hello Kafka!";
    int ret = 0;

    // 1 init
    KafkaProducerClient kp;
    ret = kp.init(brokers);
    if (ret != 0) { printf("Error: kp.init(): ret=%d;\n", ret); return 0; }

    // 2 add topic
    kp.addTopic(topic);

    // 3 get partitions count
    int32_t parNum = kp.getPartitonCount(topic);
    std::cout << "parNum = " << parNum << std::endl;

    // 4 send msg
    for (int32_t i = 0; i < parNum; ++i)
    {
        int32_t partitionId = i; //RD_KAFKA_PARTITION_UA
        ret = kp.sendMessage(topic, partitionId, str_msg, strlen(str_msg)); //向kafka服务器发送消息

        if (ret != 0) {
            printf("Error: kp.sendMessage(): ret=%d;\n", ret);
            //return 0; 
        }
    }

    printf("end!!!!!!!\n");
    return 0;
}
