enter_region:
	MOVE REGISTER, #1		|	在寄存器中放一个1
	XCHG REGISTER, LOCK		|	交换寄存器和锁变量的内容
	CMP REGISTER, #0		|	锁是0吗
	JNE enter_region		|	若不是0,则循环等待
	RET						|	返回调用者，进入临界区

leave_region:
	MOVE_LOCK, #0			|	在锁中存入0
	RET						|	返回调用者