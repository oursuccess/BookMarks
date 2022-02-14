/*
	复制文件程序，有基本的错误检查和错误报告
*/

#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h> 	//这就注定了，只能在UNIX中使用

#define BUF_SIZE 4096
#define OUTPUT_MODE 0700	//文件保护位,7:111,表示拥有者可读可写可执行，其他人没有任何权限

int main(int argc, char **argv)
{
	int in_fd, out_fd, rd_count, wt_count;
	char buffer[BUF_SIZE];

	if (argc != 3) exit(1);	//参数数量不对时，直接退出

	/*打开输入文件并创建输出文件, 带有基础的错误检查*/
	in_fd = open(argv[1], O_RDONLY);
	if (in_fd < 0) exit(2);
	out_fd = creat(argv[2], O_WRONLY);
	if (out_fd < 0) exit(3);

	/* 循环复制 */
	while (true)
	{
		rd_count = read(in_fd, buffer, BUF_SIZE);
		if (rd_count <= 0) break;	//已经读到了文件结束，或者读取出错
		wt_count = write(out_fd, buffer, rd_count);
		if (wt_count <= 0) break;	//wt_count <= 0是错误
	}

	/* 关闭文件 */
	close(in_fd);
	close(out_fd);
	if (rd_count == 0)
		exit(0);	//没有错误发生，正常退出
	else
		exit(5);	//读取错误
}