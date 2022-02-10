mutex_lock:
	TSL REGISTER, mutex_lock	|	将互斥信号量复制到寄存器，并将互斥信号量置为1
	CMP REGISTER, #0			|	测试互斥信号量是否为0
	JZE	OK						|	如果为0，则跳转到ok；否则继续向下
	CALL thread_yield			|	互斥信号量忙，调度其它线程
	JMP mutex_lock				|	稍后再试
ok:	RET							|	返回调用者，进入临界区

mutex_unlock:
	MOVE MUTEX, #0				|	将mutex置为0
	RET							|	返回调用者