#include "producer_consumer.h"

constexpr static int N = 100;	//缓冲区中的槽数
int count = 0;					//缓冲区中目前的数据项数

using function = void (*)();

//一个sleep和wakeup的声明
void sleep();
void wakeup(function consumer);

void producer()
{
	int item;

	while (true)
	{
		item = produce_item();		//生产数据项
		if (count == N) sleep();	//如果缓冲区满了，则进入休眠状态	
		insert_item(item);			//将数据项插入缓冲区中
		++count;					//增加缓冲区项的计数
		if (count == 1) wakeup(consumer);	//若缓冲区之前为空，则说明消费者休眠中，将消费者唤醒
	}
}

void consumer()
{
	int item;

	while (true)
	{
		if (count == 0) sleep();	//若缓冲区为空，则休眠
		item = remove_item();		//取出一个数据项
		count--;					//缓冲区数据项计数减1
		if (count == N-1) wakeup(producer);	//若缓冲区之前是满的，则说明生产者休眠了，将生产者唤醒
		consume_item();
	}
}