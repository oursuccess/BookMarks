#define N 2 	//进程数量

int turn; //现在轮到谁
int interested[N]; //所有值初始化为0(false)

void enter_region(int process) //进程是0或者1
{
	int other = 1 - process; //我们假设了只有两个进程，分别为0和1, other为另一进程

	interested[process] = true; //标识感兴趣
	turn = process; //设置标志
	while (turn == process && interested[other] == true) ;	//循环等待
}

void leave_region(int process) //要离开临界区的进程
{
	interested[process] = false;	//离开临界区
}