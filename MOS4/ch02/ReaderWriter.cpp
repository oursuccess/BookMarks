#include "semaphore.h"

semaphore mutex = 1;
semaphore db = 1;			//控制对数据库的访问

int readerCount = 0;					//正在读或即将读的进程数目

//一些声明
void read_data_base();
void use_data_read();

void think_up_data();
void write_data_base();

void reader()
{
	while (true)
	{
		down(mutex);
		++readerCount;
		if (readerCount == 1) down(db);
		up(mutex);

		read_data_base();

		down(mutex);
		--readerCount;
		if (readerCount == 0) up(db);
		up(mutex);

		use_data_read();
	}
}

void writer()
{
	while (true)
	{
		think_up_data();
		down(db);
		write_data_base();
		up(db);
	}
}