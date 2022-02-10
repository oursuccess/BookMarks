#pragma once

using semaphore = int;	//信号量是一种特殊的整型数据

//down和up的声明
void down(semaphore &sema);
void up(semaphore &sema);