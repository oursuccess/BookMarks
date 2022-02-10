enter_region:
	TSL REGISTER, LOCK	|	复制锁到寄存器并将锁设为1
	CMP REGISTER, #0	|	锁是0吗?
	JNE enter_region	|	若不是0,说明锁已经被设置，则循环
	RET					|	返回调用者，进入了临界区

leave_region:
	MOVE LOCK, #0		|	在锁中存入0
	RET					|	返回调用者