#include "messagepassing.h"

constexpr static int N = 100;		//缓冲区中的槽数

void producer()
{
	Item item;
	Message m;						//消息缓冲区

	while (true)
	{
		item = produce_item();		
		receive(consumer, m);		//等待消费者发送空缓冲区
		build_message(m, item);		//建立一个待发送的消息
		send(consumer, m);			//将消息发送给消费者
	}
}

void consumer()
{
	Item item;
	Message m;
	
	//仅执行一次
	for (int i = 0; i < N; ++i) send(producer, m);	//发送N个空缓冲区

	while (true)
	{
		receive(producer, m);		//接收消息
		item = extract_message(m);	//解锁消息
		send(producer, m);			//将空缓冲区发送回生产者
		consume_item(item);			//处理消息
	}
}