#include <cstdarg>
#include <cstdio>
#include <cstring>

int demo(char msg, ...)
{
	/*定义保存函数参数的结构*/
	va_list argp;
	int argno = 0;
	char para;
	/*argp指向传入的第一个可选参数，msg是最后一个确定的参数*/
	va_start(argp, msg);
	while (1)
	{
		para = va_arg(argp, char);
		if (strcmp(&para, "") == 0)
			break;
		printf("Parameter #%d is: %s\n", argno, para);
		argno++;
	}
	va_end(argp);
}