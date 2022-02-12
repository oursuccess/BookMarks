#include "semaphore.h"

constexpr int N = 5;				//哲学家数

//i左边邻居的编号
constexpr inline int left(int i)
{
	return (i + N - 1) % N;
}
//i右边邻居的编号
constexpr inline int right(int i)
{
	return (i + 1) % N;
}

//哲学家的状态
enum State{
	Thinking,	//思考
	Hungry,		//饿了
	Eating,		//就餐
};

int state[N];						//记录哲学家当前的状态

semaphore mutex = 1;				//临界区的互斥锁
semaphore signals[N];				//每个哲学家都有一个信号量

//一些声明
void eat();							
void think();

void put_forks(int i)
{
	down(mutex);
	state[i] = Thinking;
	test(left(i));
	test(right(i));
	up(mutex);
}

void take_forks(int i)
{
	down(mutex);
	state[i] = Hungry;
	test(i);
	up(mutex);
	down(signals[i]);
}


void test(int i)
{
	if (state[i] == Hungry && state[left(i)] != Eating && state[right(i)] != Eating){
		state[i] = Eating;
		up(signals[i]);
	}
}

void philosopher(int i)				//哲学家编号，从0到N-1
{
	while (true)
	{
		think();
		take_forks();
		eat();
		put_forks();
	}
}