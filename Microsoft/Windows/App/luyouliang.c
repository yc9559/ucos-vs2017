#include <os.h>
#include "luyouliang.h"

BOOLEAN g_FlagEn = 1;		//增加一个全局变量，做为是否时钟调度的标志

OS_EVENT  *MyEventSem;

int a, b, c;
char * buffer;
/*实验使用的代码1*/
int FirstTask(void *pParam)
{
	int i, j = 0;
	int abc = 123;
	OSTimeDly(100);//不影响统计任务初始化时获取最大的空闲计数值
	printf("welcome to embeded system\n");
	printf("welcome to ucos\n");
	printf("This is a simple task for experiment 1!\n");

	for (;;)
	{
		for (i = 0; i<99999999; i++);
		//OSTimeDly(100);
		printf("任务延时，j=%d\n", j++);
	}
	return(0);
}
/*实验使用的代码2*/
void E2_task1(void *pParam)
{
	int i = 0;
	OSTimeDly(100);
	printf("两个任务交替运行，E2task1,优先级%d\n", OSPrioCur);
	for (;;)
	{
		printf("优先级为%d的任务输出%d\n", OSPrioCur, i++);
		OSTimeDly(100);
	}
}

void E2_task2(void *pParam)
{
	int i = 0;
	OSTimeDly(200);
	printf("两个任务交替运行，E2task2,优先级%d\n", OSPrioCur);
	for (;;)
	{
		printf("优先级为%d的任务输出%d\n", OSPrioCur, i++);
		OSTimeDly(200);
	}
}

/*实验使用的代码3*/
void E3_task0(void *pParam)
{
	int i = 0;
	OSTimeDly(100);
	printf("任务0优先级%d,负责挂起和恢复采集任务和数据处理任务\n", OSPrioCur);
	for (;;)
	{
		printf("任务0挂起任务1,恢复任务2，挂起时间1秒\n");
		OSTaskSuspend(6);
		OSTaskResume(7);
		OSTimeDly(100);

		printf("任务0挂起任务2,恢复任务1，挂起时间1秒\n");
		OSTaskSuspend(7);
		OSTaskResume(6);
		OSTimeDly(100);
	}
}

void E3_task1(void *pParam)
{
	int i = 0;
	OSTimeDly(100);
	printf("任务1优先级%d\n", OSPrioCur);
	for (;;)
	{
		printf("任务1输出%d\n", i++);
		OSTimeDly(20);
	}
}
void E3_task2(void *pParam)
{
	int i = 100;
	OSTimeDly(100);
	printf("任务2优先级%d\n", OSPrioCur);
	for (;;)
	{
		printf("任务2输出%d\n", i++);
		OSTimeDly(30);
	}
}
/*end 实验使用的代码3*/


int add1(int *p1, int *p2)
{
	int a, b, c;
	a = *p1;
	b = *p2;
	OSTimeDly(OS_TICKS_PER_SEC);
	c = a + b;
	return(c);
}

int add2(int p1, int p2)
{
	//int a,b;
	a = p1;
	b = p2;
	OSTimeDly(OS_TICKS_PER_SEC);
	c = a + b;
	return(c);
}

void usertask(void *pParam)
{
	//INT8U i=0;
	// for(;;){
	//	printf("%d\n",i);
	//	i++;
	//	OSTimeDly(100);
	//}
	INT8U i = (INT8U)pParam;
	//printf("优先级为%d的任务输出后延时%d秒\n",OSPrioCur,OSPrioCur);

	for (;;)
	{
		printf("优先级为%d的任务输出%d\n", OSPrioCur, i++);
		OSTimeDly(100);
	}
}
void usertask1(void *pParam)
{
	int sum = 1;
	for (;;) {
		//printf("\ntask%d call add2(1,2)\n",1);
		//sum=add2(1,2);
		OSTimeDly(OS_TICKS_PER_SEC);
		printf("task5 after sleep,本任务调度次数%d,g_FlagEn=%d\n", sum++, g_FlagEn);
		//printf("\ntask%d call add2(1,2) solution is %d\n",1,sum);
	}//for(;;)
}
void usertask2(void *pParam)
{

	int sum = 1;
	for (;;) {
		//printf("\n\rtask%d call add2(100,200)\n",2);

		OSTimeDly(OS_TICKS_PER_SEC);
		//c=a+b;//sum=add2(100,200);
		printf("task6 after sleep,本任务调度次数%d,g_FlagEn=%d\n", sum++, g_FlagEn);//printf("\ntask%d call add2(100,200) solution is %d\n",2,sum);
	}//for(;;)
}

void UsrCouPri()
{
	int crt;
	crt = 0;
	for (;;) {
		//	sum=add2(100,200);	

	}
}

//信号量管理的例子
void UserTaskSemA(void *pParam)
{
	/*任务SemA创建信号量，然后周期性访问资源R*/
	/*创建信号量*/
	INT8U     *perr;
	INT8U err;
	//INT8U i;
	OS_SEM_DATA mySemData;
	err = 0;
	perr = &err;
	MyEventSem = OSSemCreate(2);
	if (MyEventSem == (OS_EVENT *)0)
	{
		printf("任务A创建信号量失败！\n");
		OSTaskDel(OS_PRIO_SELF);
		return;
	}
	OSSemQuery(MyEventSem, &mySemData);
	printf("时间:%d, 任务A创建信号量。当前信号量值=%d\n", OSTimeGet(), mySemData.OSCnt);
	while (1)
	{
		OSSemQuery(MyEventSem, &mySemData);
		printf("时间:%d,任务A开始请求信号量！当前信号量值=%d\n", OSTimeGet(), mySemData.OSCnt);
		OSSemPend(MyEventSem, 0, perr);
		if (err != OS_ERR_NONE)
		{
			printf("任务A请求信号量失败\n");
			printf("错误号%d\n", err);
			continue;
		}
		OSSemQuery(MyEventSem, &mySemData);
		printf("时间:%d,任务A获得信号量。当前信号量值=%d，任务A开始对R操作\n", OSTimeGet(), mySemData.OSCnt);
		OSTimeDly(1000); /*模拟操作资源,需要10秒，1000个时钟嘀嗒*/
		printf("时间:%d，任务A结束资源操作，提交信号量！\n", OSTimeGet());
		OSSemPost(MyEventSem);
		OSSemQuery(MyEventSem, &mySemData);
		printf("时间:%d,任务A提交信号量完成，当前信号量值=%d,任务A将延时阻塞1000嘀嗒\n", OSTimeGet(), mySemData.OSCnt);
		OSTimeDly(1000);
	}
}

void UserTaskSemB(void *pParam)
{
	/*任务SemA创建信号量，然后周期性访问资源R*/
	INT8U     *perr;
	INT8U err;
	OS_SEM_DATA mySemData;
	err = 0;
	perr = &err;
	printf("时间:%d,任务B开始延时300个时钟嘀嗒", OSTimeGet());
	OSTimeDly(300);/*任务B先延时3秒*/
	if (MyEventSem == (OS_EVENT *)0)
	{
		printf("任务A创建信号量失败！\n");
		OSTaskDel(OS_PRIO_SELF);
		return;
	}
	while (1)
	{
		OSSemQuery(MyEventSem, &mySemData);
		printf("时间:%d,任务B开始请求信号量！当前信号量值=%d\n", OSTimeGet(), mySemData.OSCnt);
		OSSemPend(MyEventSem, 0, perr);
		if (err != OS_ERR_NONE)
		{
			printf("任务B请求信号量失败\n");
			printf("错误号%d\n", err);
			continue;
		}
		OSSemQuery(MyEventSem, &mySemData);
		printf("时间:%d,任务B获得信号量。当前信号量值=%d，任务B开始对R操作,需1000个时钟嘀嗒\n", OSTimeGet(), mySemData.OSCnt);
		OSTimeDly(1000); /*模拟操作资源,需要10秒，1000个时钟嘀嗒*/
		printf("时间:%d，任务B结束资源操作，提交信号量！\n", OSTimeGet());
		OSSemPost(MyEventSem);
		OSSemQuery(MyEventSem, &mySemData);
		printf("时间:%d,任务B提交信号量完成，当前信号量值=%d,任务B将延时阻塞1000嘀嗒\n", OSTimeGet(), mySemData.OSCnt);
		OSTimeDly(1000);
	}
}


void UserTaskSemC(void *pParam)
{
	/*任务SemA创建信号量，然后周期性访问资源R*/
	INT8U     *perr;
	INT8U err;
	OS_SEM_DATA mySemData;
	err = 0;
	perr = &err;
	printf("时间:%d,任务C开始延时400个时钟嘀嗒", OSTimeGet());
	OSTimeDly(400);/*任务C先延时4秒*/
	if (MyEventSem == (OS_EVENT *)0)
	{
		printf("任务A创建信号量失败！\n");
		OSTaskDel(OS_PRIO_SELF);
		return;
	}
	while (1)
	{
		OSSemQuery(MyEventSem, &mySemData);
		printf("时间:%d,任务C开始请求信号量！当前信号量值=%d\n", OSTimeGet(), mySemData.OSCnt);
		OSSemPend(MyEventSem, 0, perr);
		if (err != OS_ERR_NONE)
		{
			printf("任务C请求信号量失败\n");
			printf("错误号%d\n", err);
			continue;
		}
		OSSemQuery(MyEventSem, &mySemData);
		printf("时间:%d,任务C获得信号量。当前信号量值=%d，任务C开始对R操作,需1000个时钟嘀嗒\n", OSTimeGet(), mySemData.OSCnt);
		OSTimeDly(1000); /*模拟操作资源,需要10秒，1000个时钟嘀嗒*/
		printf("时间:%d，任务C结束资源操作，提交信号量！\n", OSTimeGet());
		OSSemPost(MyEventSem);
		printf("时间:%d,任务C提交信号量完成，当前信号量值=%d,任务C将延时阻塞1000嘀嗒\n", OSTimeGet(), mySemData.OSCnt);
		OSTimeDly(1000);
	}
}

//事件标志组的例子
INT8U IO[4][10];
OS_FLAG_GRP  * pFlagGroupDataProcess;
void TaskDataProcess(void *pParam)
{
	INT8U     *perr;
	INT8U err, i;
	INT16U SUM;
	OS_FLAGS processflag, retflag;
	err = OS_ERR_NONE;
	perr = &err;
	processflag = 0x0F;
	/*创建事件标志组,事件标志初始值0，没有事件发生*/
	pFlagGroupDataProcess = OSFlagCreate(0, perr);
	/*省略了检查是否创建成功*/
	while (1)
	{
		printf("时间:%d，任务TaskDataProcess开始请求事件标志-----------！\n", OSTimeGet());
		retflag = OSFlagPend(pFlagGroupDataProcess,
			processflag,
			OS_FLAG_WAIT_SET_ALL + OS_FLAG_CONSUME,
			0,
			perr);

		if (retflag == processflag)
		{
			SUM = 0;
			printf("时间:%d，任务TaskDataProcess请求事件标志成功，开始处理数据！\n", OSTimeGet());
			for (i = 0; i<10; i++)
			{
				SUM += IO[0][i] + IO[1][i] + IO[2][i] + IO[3][i];
			}
			printf("时间:%d，任务TaskDataProcess处理数据完成，结果为%d:\n", OSTimeGet(), SUM);
		}
	}
}
void TaskIO1(void *pParam)
{
	INT8U     *perr;
	INT8U err, i;

	OS_FLAGS rdyflag;
	//OS_FLAG_GRP  * pFlagGroup;
	err = OS_ERR_NONE;
	perr = &err;
	rdyflag = 0;

	while (1)
	{
		OSTimeDly(100);/*延时1秒*/
		for (i = 0; i<10; i++) /*模拟获取数据的过程*/
		{
			IO[0][i] = 1;
		}
		printf("时间:%d，任务TaskIO1获取IO数据后，准备提交事件，当前事件标志位:%d\n", OSTimeGet(), rdyflag);
		rdyflag = OSFlagPost(pFlagGroupDataProcess,
			0x01,
			OS_FLAG_SET,
			perr);            /*提交事件标志，置位事件标志组中最后一位位0*/
		printf("时间:%d，任务TaskIO1获取IO数据后，提交事件，当前事件标志位:%d\n", OSTimeGet(), rdyflag);
	}
}
void TaskIO2(void *pParam)
{
	INT8U     *perr;
	INT8U err, i;
	OS_FLAGS rdyflag;
	perr = &err;
	err = OS_ERR_NONE;
	rdyflag = 0;
	while (1)
	{
		OSTimeDly(100);/*延时1秒*/
		for (i = 0; i<10; i++) /*模拟获取数据的过程*/
		{
			IO[1][i] = 2;
		}
		printf("时间:%d，任务TaskIO2获取IO数据后，准备提交事件，当前事件标志位:%d\n", OSTimeGet(), rdyflag);
		rdyflag = OSFlagPost(pFlagGroupDataProcess,
			0x02,
			OS_FLAG_SET,
			perr);            /*提交事件标志，置位事件标志组中位1*/
		printf("时间:%d，任务TaskIO2获取IO数据后，提交事件，当前事件标志位:%d\n", OSTimeGet(), rdyflag);
	}
}
void TaskIO3(void *pParam)
{
	INT8U     *perr;
	INT8U err, i;
	OS_FLAGS rdyflag;
	perr = &err;
	err = OS_ERR_NONE;
	rdyflag = 0;
	while (1)
	{
		OSTimeDly(100);/*延时1秒*/
		for (i = 0; i<10; i++) /*模拟获取数据的过程*/
		{
			IO[2][i] = 3;
		}
		printf("时间:%d，任务TaskIO3获取IO数据后，准备提交事件，当前事件标志位：%d\n", OSTimeGet(), rdyflag);
		rdyflag = OSFlagPost(pFlagGroupDataProcess,
			0x04,
			OS_FLAG_SET,
			perr);            /*提交事件标志，置位事件标志组中位2*/
		printf("时间:%d，任务TaskIO3获取IO数据后，提交事件，当前事件标志位：%d\n", OSTimeGet(), rdyflag);
	}
}
void TaskIO4(void *pParam)
{
	INT8U     *perr;
	INT8U err, i;
	OS_FLAGS rdyflag;
	perr = &err;
	err = OS_ERR_NONE;
	rdyflag = 0;
	while (1)
	{
		OSTimeDly(100);/*延时1秒*/
		for (i = 0; i<10; i++) /*模拟获取数据的过程*/
		{
			IO[3][i] = 3;
		}
		printf("时间:%d，任务TaskIO4获取IO数据后，准备提交事件，当前事件标志位：%d\n", OSTimeGet(), rdyflag);
		rdyflag = OSFlagPost(pFlagGroupDataProcess,
			0x08,
			OS_FLAG_SET,
			perr);            /*提交事件标志，置位事件标志组中位3*/
		printf("时间:%d，任务TaskIO4获取IO数据后，提交事件，当前事件标志位：%d\n", OSTimeGet(), rdyflag);
	}
}

/*Mutex例子程序，使用优先级反转*/
OS_EVENT  *myMutex;
void TaskMutex1(void *pParam)
{
	INT8U     *perr;
	INT8U err, i;
	INT32U j;
	perr = &err;
	err = OS_ERR_NONE;


	myMutex = OSMutexCreate(3, perr);/*创建互斥信号量，优先级继承优先级PIP为9*/
	if (myMutex == (OS_EVENT  *)0)   /*检查是否创建成功*/
	{
		printf("时间:%d，高优先级任务TaskMutex1创建互斥信号量失败,失败号%d:\n", OSTimeGet(), *perr);
		OSTaskDel(OS_PRIO_SELF); /*不成功则删除本任务*/
		return;
	}
	printf("时间:%d，高优先级任务TaskMutex1创建互斥信号量成功.\n", OSTimeGet());
	OSTimeDly(100);/*延时1秒*/
	printf("时间:%d，高优先级任务TaskMutex1请求互斥信号量.\n", OSTimeGet());
	OSMutexPend(myMutex, 0, perr);/*等待互斥信号量*/
	printf("时间:%d，高优先级任务TaskMutex1获得互斥信号量.\n", OSTimeGet());
	if (*perr == OS_ERR_NONE)
	{

		for (i = 1; i <= 5; i++)
		{
			printf("时间%d:高优先级任务TaskMutex1向串口输出数据%d\n", OSTimeGet(), i);  /*模拟操作IO*/
			for (j = 1; j <= 9999999; j++);	 /*模拟操作串口*/
		}
	}
	else
	{
		printf("时间:%d，高优先级任务TaskMutex1请求信号量失败,失败号%d:\n", OSTimeGet(), *perr);
	}
	OSMutexPost(myMutex);
	for (i = 1; i <= 5; i++)
	{

		printf("时间%d:高优先级任务TaskMutex1执行提交信号量后执行其他操作%d\n", OSTimeGet(), i);	/*模拟操作IO*/
		for (j = 1; j <= 99999999; j++);	 /*延时,表示在操作串口*/
	}
	printf("高优先级任务TaskMutex1结束运行，删除自己\n");
	OSTaskDel(OS_PRIO_SELF); /*删除本任务*/
	return;

}
void TaskMutex2(void *pParam)
{
	INT8U 	*perr;
	INT8U err, i;
	INT32U j;
	perr = &err;
	err = OS_ERR_NONE;
	if (myMutex == (OS_EVENT  *)0)	 /*检查是否有被创建的互斥信号量*/
	{
		printf("时间:%d，互斥信号量未创建", OSTimeGet());
		OSTaskDel(OS_PRIO_SELF); /*删除本任务*/
		return;
	}
	OSTimeDly(90);/*延时不到1秒*/
	printf("时间:%d，低优先级任务TaskMutex2请求互斥信号量\n", OSTimeGet());
	OSMutexPend(myMutex, 0, perr);/*等待互斥信号量*/
	printf("时间:%d，任务TaskMutex2获得互斥信号量\n", OSTimeGet());
	if (*perr == OS_ERR_NONE)
	{
		printf("时间:%d，低优先级任务TaskMutex2获得互斥信号量\n", OSTimeGet());
		for (i = 1; i <= 5; i++)
		{

			printf("时间%d:低优先级TaskMutex2向串口输出数据%d\n", OSTimeGet(), i);  /*模拟操作IO*/
			for (j = 1; j <= 99999999; j++);   /*模拟操作串口*/
		}
	}
	else
	{
		printf("时间:%d，低优先级任务TaskMutex2请求信号量失败,失败号:%d\n", OSTimeGet(), *perr);
	}
	OSMutexPost(myMutex);
	for (i = 1; i <= 5; i++)
	{
		printf("时间%d:低优先级TaskMutex2执行提交信号量后执行其他操作%d\n", OSTimeGet(), i);  /*模拟操作IO*/
		for (j = 1; j <= 99999999; j++);   /*延时,表示在操作串口*/
	}
	printf("低优先级任务TaskMutex2结束运行，删除自己\n");
	OSTaskDel(OS_PRIO_SELF); /*删除本任务*/
	return;
}

void TaskPrint(void *pParam)
{
	INT8U     *perr;
	INT8U err, i;
	INT32U j;
	perr = &err;
	err = OS_ERR_NONE;
	i = 0;
	OSTimeDly(95);
	for (i = 1; i <= 5; i++)
	{
		printf("时间%d:中优先级任务TaskPrint在运行中，打印数据%d\n", OSTimeGet(), i++);  /*模拟操作IO*/
		for (j = 1; j <= 99999999; j++);   /*模拟进行打印操作*/
	}
	printf("中优先级任务TaskPrint结束运行，删除自己\n");
	OSTaskDel(OS_PRIO_SELF); /*删除本任务*/
}

//消息邮箱的例子
OS_EVENT  *myMBox;
void TaskMessageSen(void *pParam)
{
	INT8U     *perr;
	INT8U err;//,i;  
			  //INT32U j;
	INT32U scount;
	int a[3];
	perr = &err;
	err = OS_ERR_NONE;

	scount = 1;

	a[1] = 5;
	a[3] = 6;
	myMBox = OSMboxCreate(&scount);/*创建邮箱，*/
	if (myMBox == (OS_EVENT  *)0)   /*检查是否创建成功*/
	{
		printf("时间:%d， TaskMessageSen创建邮箱失败\n", OSTimeGet());
		OSTaskDel(OS_PRIO_SELF); /*不成功则删除本任务*/
		return;
	}
	printf("时间:%d， TaskMessageSen创建邮箱成功\n", OSTimeGet());
	while (1)
	{
		OSTimeDly(100);/*延时1秒*/
		scount++;
		printf("时间:%d，任务TTaskMessageSen准备发消息，消息为%d\n", OSTimeGet(), scount);
		OSMboxPost(myMBox, &scount); /*发消息*/
	}
}
void TaskMessageRec(void *pParam)
{
	INT8U     *perr;
	INT8U err;//,i;  
	INT32U * prcount;
	perr = &err;
	err = OS_ERR_NONE;

	if (myMBox == (OS_EVENT  *)0)   /*检查邮箱是否存在*/
	{
		printf("时间:%d，任务TaskMessageRec判定邮箱不存在!\n", OSTimeGet());
		OSTaskDel(OS_PRIO_SELF); /*不成功则删除本任务*/
		return;
	}

	while (1)
	{
		prcount = (INT32U *)OSMboxPend(myMBox, 0, perr); /*请求消息，如果消息不存在就阻塞*/
		if (*perr == OS_ERR_NONE)
			printf("时间:%d，任务TaskMessageRec接收消息为%d\n", OSTimeGet(), *prcount);
		else
			printf("时间:%d，任务TaskMessageRec等待异常结束，错误号:%d\n", OSTimeGet(), *perr);
	}
}

//消息队列的例子
OS_EVENT  *myQ;
void TaskQSen(void *pParam)
{
	INT8U     *perr;
	INT8U err, i;
	INT8U scount;
	OS_Q_DATA myQData; /*消息队列数据*/
	void * myq[6]; /*消息队列*/
	INT8U mymessage[256];
	perr = &err;
	err = OS_ERR_NONE;
	scount = 0;

	myQ = OSQCreate(myq, 6);/*创建消息队列，容积为6*/
	if (myQ == (OS_EVENT  *)0)   /*检查是否创建成功*/
	{
		printf("时间:%d， TaskQSen创建消息队列失败\n", OSTimeGet());
		OSTaskDel(OS_PRIO_SELF); /*不成功则删除本任务*/
		return;
	}
	printf("时间:%d， TaskQSen创建消息队列成功\n", OSTimeGet());
	for (i = 0; i <= 254; i++)
		mymessage[i] = i;
	mymessage[255] = i;
	while (1)
	{
		OSTimeDly(100);

		printf("时间:%d，任务TTaskQSen准备发消息，消息为%d\n", OSTimeGet(), mymessage[scount]);
		err = OSQPost(myQ, &mymessage[scount]); /*发消息*/
		switch (err) {
		case OS_ERR_Q_FULL:
			printf("时间:%d，任务TTaskQSen发消息失败，消息队列已满\n", OSTimeGet());
			break;
		case OS_ERR_NONE:
			printf("时间:%d，任务TTaskQSen发消息成功\n", OSTimeGet());
			break;
		default:
			printf("时间:%d，任务TTaskQSen发消息失败，错误号：%d\n", OSTimeGet(), err);
		}
		OSQQuery(myQ, &myQData);
		printf("时间:%d，当前队列中消息数量：%d\n", OSTimeGet(), myQData.OSNMsgs);
		scount++;
	}
}

void TaskQRec(void *pParam)
{
	INT8U     *perr;
	INT8U err;
	INT8U rcount;
	INT8U rec;
	OS_Q_DATA myQData; /*消息队列数据*/
					   //INT8U mymessage[256];
	perr = &err;
	err = OS_ERR_NONE;
	rcount = 0;


	if (myQ == (OS_EVENT  *)0)   /*检查消息队列是否存在*/
	{
		printf("时间:%d， TaskQRec判定消息队列不存在\n", OSTimeGet());
		OSTaskDel(OS_PRIO_SELF); /*不成功则删除本任务*/
		return;
	}
	while (1)
	{
		OSTimeDly(200);
		printf("时间:%d，任务TaskQRec开始等待消息\n", OSTimeGet());
		rec = *(INT8U *)OSQPend(myQ, 0, perr);
		switch (err) {
		case OS_ERR_NONE:
			printf("时间:%d，任务TaskQRec接收到消息%d\n", OSTimeGet(), rec);
			break;
		default:
			printf("时间:%d，任务TTaskMessageSen发消息失败，错误号：%d\n", OSTimeGet(), err);
		}
		OSQQuery(myQ, &myQData);
		if (rec == 4)
			printf("4\n");
		printf("时间:%d，当前队列中消息数量：%d\n", OSTimeGet(), myQData.OSNMsgs);
	}
}

//内存管理的例子

void TaskM(void *pParam)
{

	INT8U *perr;
	INT8U err, i;
	OS_MEM  *pmyMem;     //MCB块地址
	INT8U myMem[3][20]; //用来做内存分区
	void    *pblk[10];   //内存块地址数组
	BOOLEAN require;
	OS_MEM_DATA mem_data;//用于查询内存块信息
	err = OS_ERR_NONE;
	perr = &err;
	require = 1;
	pmyMem = OSMemCreate(myMem, 3, 20, perr);/*创建内存分区，10个块, 每个块20个字节*/
	if (pmyMem == (OS_MEM  *)0)   /*检查是否创建成功*/
	{
		printf("时间:%d， TaskM创建内存分区失败\n", OSTimeGet());
		OSTaskDel(OS_PRIO_SELF); /*不成功则删除本任务*/
		return;
	}
	printf("时间:%d， TaskM创建内存分区成功，包含10个块, 每个块20个字节\n", OSTimeGet());
	i = 0;
	while (1)
	{
		if (i>5)
		{
			i = 0;
			require = !require;
		}
		//printf("时间:%d，i=%d\n",OSTimeGet(),i);
		OSTimeDly(100);/*延时1秒*/
		if (require)
		{
			printf("时间:%d，任务TaskM准备请求一个块->", OSTimeGet());
			pblk[i++] = OSMemGet(pmyMem, perr); /*请求内存块*/
			switch (err) {
			case OS_ERR_MEM_NO_FREE_BLKS:
				printf("时间:%d，任务TaskM发请求内存块失败，分区中已无可用内存块！\n", OSTimeGet());
				break;
			case OS_ERR_NONE:
				printf("时间:%d，任务TaskM获得内存块\n", OSTimeGet());
				break;
			default:
				printf("时间:%d，任务TaskM发请求内存块失败，错误号：%d\n", OSTimeGet(), err);
			}
		}
		else
		{
			printf("时间:%d，任务TaskM准备释放一个块->", OSTimeGet());
			err = OSMemPut(pmyMem, pblk[i++]); /*请求内存块*/
			switch (err) {
			case OS_ERR_MEM_FULL:
				printf("时间:%d，任务TaskM发请求内存块失败，分区已满！\n", OSTimeGet());
				break;
			case OS_ERR_MEM_INVALID_PBLK:
				printf("时间:%d，任务TaskM发释放内存块失败，释放无效的内存块！\n", OSTimeGet());
				break;
			case OS_ERR_NONE:
				printf("时间:%d，任务TaskM成功释放内存块\n", OSTimeGet());
				break;
			default:
				printf("时间:%d，任务TaskM释放内存块失败，错误号：%d\n", OSTimeGet(), err);
			}

		}
		OSMemQuery(pmyMem, &mem_data);
		printf("时间:%d，当前分区中的已用内存块数量：%d\n", OSTimeGet(), mem_data.OSNUsed);
		printf("时间:%d，当前分区中的空闲内存块数量：%d\n", OSTimeGet(), mem_data.OSNFree);
	}
}

