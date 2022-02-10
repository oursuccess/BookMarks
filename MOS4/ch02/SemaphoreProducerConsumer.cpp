#include "semaphore.h"
#include "producer_consumer.h"

constexpr static int N = 100;	//槽数

semaphore mutex = 1;			//控制对临界区的访问
semaphore empty = N;			//初始时的空槽位数
semaphore full = 0;				//初始时被填充的槽数

void producer()
{
	Item item;

	while (true)
	{
		item = produce_item();	//产生放置在缓冲区的一些数据
		down(empty);			//将空槽数目减去1
		down(mutex);			//进入临界区
		insert_item(item);		//将新数据项放到缓冲区中
		up(mutex);				//离开临界区
		up(full);				//将满槽的数目+1
	}
}

void cosumer()
{
	Item item;

	while (true)
	{
		down(full);				//将满槽数目-1
		down(mutex);			//进入临界区
		item = remove_item();	//从缓冲区中取出数据项
		up(mutex);				//离开临界区
		up(empty);				//将空槽数目+1
		consume_item(item);		//处理数据项
	}
}