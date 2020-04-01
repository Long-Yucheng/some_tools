#include <iostream>
#include "KafkaProducer.h"

using namespace std;

int main()
{
    //KafkaProducerClient* KafkaprClient_ = new KafkaProducerClient("localhost:9092", "test", 0);

    KafkaProducerClient* KafkaprClient_ = new KafkaProducerClient("14.17.118.245:9092, 14.17.118.246:9092, 14.17.118.247:9092", "test3", RdKafka::Topic::PARTITION_UA);
    KafkaprClient_->Init();
    KafkaprClient_->Send("hello world!");

    char str_msg[] = "Hello Kafka!";

    while (fgets(str_msg, sizeof(str_msg), stdin))
    {
        size_t len = strlen(str_msg);
        if (str_msg[len - 1] == '\n')
        {
            str_msg[--len] = '\0';
        }

        if (strcmp(str_msg, "end") == 0)
        {
            break;
        }

        KafkaprClient_->Send(str_msg);
    }

    return 0;
}
