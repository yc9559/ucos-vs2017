#include <os.h>
#include "usercode.h"

void helloworld(void *pParam)
{
	while (1)
	{
		printf("hello world @yc9559\n");
		printf("GitHub: https://github.com/yc9559/ucos-vs2017 \n");
		OSTimeDlyHMSM(1, 0, 0, 0);
	}
}
