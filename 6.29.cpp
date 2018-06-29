/*************************************************
Copyright (C), 1988-1999, Huawei Tech. Co., Ltd.
File name: // 文件名
Author: Version: Date: // 杨展鹏 6.29
Description: // 用于详细说明此程序文件完成的主要功能，与其他模块
// 或函数的接口，输出值、取值范围、含义及参数间的控
// 制、顺序、独立或依赖等关系
Others: // 其它内容的说明
Function List: // 主要函数列表，每条记录应包括函数名及功能简要说明
1. find()
2.modify()
3.add()
4.del()
5.write()
6.list()
7.read()

History: // 修改历史记录列表，每条修改记录应包括修改日期、修改
// 者及修改内容简述
1. Date:
Author:
Modification:
2. ...
*************************************************/

#include "stdio.h"
#include "conio.h"	
#include "string.h"	
#include "windows.h"
#define TRUE 1


struct zhigong * read();//*读取职工工资数据
void write(struct zhigong *first);	//*写入职工工资数据记录
void find(struct zhigong *first);	//*查询职工工资数据记录
void modify(struct zhigong *first);	//*修改职工工资数据记录
struct zhigong * add(struct zhigong *first);//*增加职工工资数据文件中
struct zhigong * del(struct zhigong *first);	//*删除职工工资数据文件中
float grsds(float m);	//*计算个人所得税
void list(struct zhigong *first);	//*浏览职工记录

struct zhigong		//*声明职工工资数据结构体
{
	struct zhigong *front;	
	struct zhigong *behind;	
	char gonghao[10];	//*职工工号
	char name[10];	//*职工姓名
	float gwgz;		//*岗位工资
	float xjgz;		//*薪级工资
	float zwjt;		//*职务津贴
	float jxgz;		//*绩效工资
	float yfgz;		//*应发工资
	float grsds;	//*个人所得税
	float sfgz;		//*实发工资
};

void main()
{
	char ch;
	struct zhigong *first;	//*声明指向结构体的指针变量
	first=read();  //*从数据文件中读取职工工资数据并初始化职工工资结构体数组
	while(TRUE)
	{
		system("cls");	//*清屏
		printf("\n\n\t### 欢迎使用广西民族大学软件与信息安全学院职工工资管理系统 ###\n\n\n");
		printf("\t请选择(1-7) :\n");
		printf("\t==========================================================\n");
		printf("\t|\t1.查询职工工资记录\t\t\t\t|\n");
		printf("\t|\t2.修改职工工资记录\t\t\t\t|\n");
		printf("\t|\t3.添加职工工资记录\t\t\t\t|\n");
		printf("\t|\t4.删除职工工资记录\t\t\t\t|\n");
		printf("\t|\t5.保存数据到文件\t\t\t\t|\n");
		printf("\t|\t6.浏览职工记录\t\t\t\t\t|\n");
		printf("\t|\t7.退出\t\t\t\t\t\t|\n");
		printf("\t==========================================================\n");
		printf("\n\t你的选择是：");
		ch=getche();

		switch(ch)
		{
			   case '1':find(first);break;	//*查询
			   case '2':modify(first);break;	//*修改
			   case '3':first=add(first);break;	//*添加
			   case '4':first=del(first);break;	//*删除
			   case '5':write(first);break;	//*保存
			   case '6':list(first);break;	//*浏览
			   case '7':return;			//*退出
			   default:printf("\t\t请按任意键返回重新选择（1－7）\n");getch();
		}
	}
	return;
}

//*从数据文件gz.dat中读取职工工资数据到结构数组zggz中
struct zhigong * read()
{
	FILE *file;	//*声明文件指针
	int n=0;		//*声明记录职工记录数的变量
	struct zhigong *first,*readdata;//记录首地址及新分配内存地址
	struct zhigong *p;	//中间变量

	if((file=fopen("gz.dat","rb"))==NULL)//*打开职工工资数据文件并进行判断是否失败
	{
		printf("\n\n\t职工工资数据文件无法打开，或为空! ");
		printf("\n\n\t按任意键进入主菜单……");
		getch();
		return 0;
	}
	else	//*文件打开成功时
	{
		//动态申请分配内存空间，并获得内存分配首地址
		readdata=(struct zhigong *)malloc(sizeof(struct zhigong));
		//循环读取文件数据到新分配的内存空间
		while(fread(readdata,sizeof(struct zhigong),1,file)==1)
		{
			if(n==0)	//说明需要建立链表起始项
			{
				first=readdata;
				first->front=NULL;
				first->behind=NULL;
				p=readdata;
			}
			else	//说明追加链表数据项
			{
				p->behind=readdata;
				readdata->front=p;
				readdata->behind=NULL;
				p=readdata;
			}
			n++;	//职工人数增1
			readdata=(struct zhigong *)malloc(sizeof(struct zhigong));
		}
		fclose(file);	//*关闭文件指针
		printf("\n\n\t职工工资数据读取完毕，共有%d人! \n",n);
		printf("\n\t5秒钟后继续…… \n",n);
		Sleep(5000);	//*延时5秒钟
	}
	printf("\n按任意键进入主菜单……");
	return first;
}


//*向职工工资数据文件中写入记录
void write(struct zhigong * first)
{
	FILE *file;	//*声明文件指针
	int n=0;	//统计存入文件职工人数

	if(first==NULL)	//*内存中无工资记录
	{
		printf("没有数据可存! 按任意键返回主菜单。\n");
		getch();
		return;
	}
	if((file=fopen("gz.dat","wb"))!=NULL)//*以二进制方式打开职工工资数据文件并进行判断是否失败
	{
		do
		{
			fwrite(first,sizeof(struct zhigong),1,file);//*所有记录一次写入文件
			n++;
			first=first->behind;
		}while(first!=NULL);
		fclose(file);	//*关闭文件指针
		printf("\n\n\t\t%d条职工记录保存完毕! \n",n);
	}
	else	//*文件打开不成功时
		printf("\t\t无法打开职工工资数据文件! \n");
	printf("\n\t\t按任意键返回主菜单……");
	getch();
}

//*查询职工工资数据记录(依据工号)
void find(struct zhigong *first)
{
	char gonghao[10];//*接收职工工号字符数组

	if(first==NULL)	//说明内存无工资记录
	{
		printf("\n\n\t\t当前还没有职工工资记录！按任意键返回主菜单……");
		getch();
		return;
	}

	printf("\t请输入职工工号：");//*提示信息
	gets(gonghao);//*从键盘读取字符串

	while(first!=NULL)//*从链表开始向后查找
	{
		if(strcmp(first->gonghao,gonghao)==0)//*比较并找到
		{
			//*显示该职工工资情况
			printf("\n\t\t\t  该职工工资情况如下：");
			printf("\n\t\t\t  ===================\n\n");

			printf("%-6s%-6s%-9s%-9s%-9s","工号","姓名","岗位工资","薪级工资","职务津贴");
			printf("%-9s%-9s%8s%9s\n","绩效工资","应发工资","所得税","实发工资");

			printf("%-6s%-6s%8.2f",first->gonghao,first->name,first->gwgz);
			printf("%9.2f%9.2f",first->xjgz,first->zwjt);
			printf("%9.2f%9.2f",first->jxgz,first->yfgz);
			printf("%9.2f%9.2f\n",first->grsds,first->sfgz);

			printf("\n 按任意键返回主菜单……");
			getch();
			return;
		}
		first=first->behind;
	}
	//循环自动结束意味着未找到
	printf("\n\n\t\t您所输入的职工工号有误或不存在！按任意键返回主菜单……\n");
	getch();
	return;
}

//*浏览职工工资记录
void list(struct zhigong * first)
{
	system("cls");
	printf("\n\n\t\t\t 全体职工工资情况如下\n");
	printf("\t\t\t======================\n\n");
	if(first!=NULL)	//说明内存中链表存在
	{
		do
		{
			printf("%-6s%-6s%-9s%-9s%-9s","工号","姓名","岗位工资","薪级工资","职务津贴");
			printf("%-9s%-9s%8s%9s\n","绩效工资","应发工资","所得税","实发工资");

			printf("%-6s%-6s%8.2f",first->gonghao,first->name,first->gwgz);
			printf("%9.2f%9.2f",first->xjgz,first->zwjt);
			printf("%9.2f%9.2f",first->jxgz,first->yfgz);
			printf("%9.2f%9.2f\n",first->grsds,first->sfgz);

			first=first->behind;	//修正first指向链表中下一项结构数据
		}while(first!=NULL); //不为空说明结构数据存在
	}
	printf("  按任意键返回主菜单……");
	getch();
	return;
}

//*修改职工工资数据记录
void modify(struct zhigong *first)
{
	char gonghao[10];//*接收职工工号字符数组

	if(first==NULL)	//说明内存无工资记录
	{
		printf("\n\n\t\t当前还没有职工工资记录！按任意键返回主菜单……");
		getch();
		return;
	}

	printf("\t请输入职工工号：");
	gets(gonghao);//*从键盘读取字符串

	while(first!=NULL)//*从链表开始向后查找
	{
		if(strcmp(first->gonghao,gonghao)==0)//*比较并找到
		{
			//*显示该职工工资情况
			printf("\n\t\t\t  该职工工资情况如下：");
			printf("\n\t\t\t  ===================\n\n");

			printf("%-6s%-6s%-9s%-9s%-9s","工号","姓名","岗位工资","薪级工资","职务津贴");
			printf("%-9s%-9s%8s%9s\n","绩效工资","应发工资","所得税","实发工资");

			printf("%-6s%-6s%8.2f",first->gonghao,first->name,first->gwgz);
			printf("%9.2f%9.2f",first->xjgz,first->zwjt);
			printf("%9.2f%9.2f",first->jxgz,first->yfgz);
			printf("%9.2f%9.2f\n",first->grsds,first->sfgz);

			//*接收该职工新的工资数据
			printf("\n\t\t请输入该职工新的岗位工资：");
			scanf("%f",&first->gwgz);
			printf("\t\t请输入该职工新的薪级工资：");
			scanf("%f",&first->xjgz);
			printf("\t\t请输入该职工新的职务津贴：");
			scanf("%f",&first->zwjt);
			printf("\t\t请输入该职工新的绩效工资：");
			scanf("%f",&first->jxgz);

			//*计算应发工资、个人所得税、实发工资
			first->yfgz=first->gwgz+first->xjgz+first->zwjt+first->jxgz;
			first->grsds=grsds(first->yfgz);
			first->sfgz=first->yfgz-first->grsds;
			//*同屏显示计算结果
			printf("\n\t\t该职工的应发工资额是：%f",first->yfgz);
			printf("\n\t\t该职工的个人所得税是：%f",first->grsds);
			printf("\n\t\t该职工的实发工资额是：%f",first->sfgz);

			printf("\n\n\t\t该职工工资数据修改成功！按任意键返回主菜单……");
			getch();
			return;
		}
		first=first->behind;
	}
	//循环自动结束意味着未找到
	printf("\n\n\t\t您所输入的职工工号有误或不存在！按任意键返回主菜单……\n");
	getch();
	return;
}

//*向职工工资数据文件中增加记录
struct zhigong * add(struct zhigong *first)
{
	struct zhigong *adddata;//记录首地址及新分配内存地址
	struct zhigong *p;	//中间变量
	adddata=(struct zhigong *)malloc(sizeof(struct zhigong));
	if(first==NULL)//说明需要创建工资数据链表
	{
		first=adddata;
		first->front=NULL;
		first->behind=NULL;
	}
	else	//说明需要找到链表结束位置
	{
		p=first;
		while(p->behind!=NULL)
		{
			p=p->behind;
		}
		//建立链表追加项指针指向关系
		p->behind=adddata;
		adddata->front=p;
		adddata->behind=NULL;
	}
	//无论是创建第一条还是追加工资记录，均只对adddata添加数据
	printf("\t请输入职工工号：");
	fflush(stdin);	//*清除键盘缓冲区
	gets(adddata->gonghao);
	printf("\t\t\t\t请输入职工姓名：");
	fflush(stdin);	//*清除键盘缓冲区
	gets(adddata->name);
	printf("\n\t\t\t\t请输入该职工新的岗位工资：");
	scanf("%f",&adddata->gwgz);
	printf("\t\t\t\t请输入该职工新的薪级工资：");
	scanf("%f",&adddata->xjgz);
	printf("\t\t\t\t请输入该职工新的职务津贴：");
	scanf("%f",&adddata->zwjt);
	printf("\t\t\t\t请输入该职工新的绩效工资：");
	scanf("%f",&adddata->jxgz);

	//*计算应发工资、个人所得税、实发工资
	adddata->yfgz=adddata->gwgz+adddata->xjgz+adddata->zwjt+adddata->jxgz;
	adddata->grsds=grsds(adddata->yfgz);
	adddata->sfgz=adddata->yfgz-adddata->grsds;
	//*输出以上计算内容///
	printf("\n\t\t\t\t该职工的应发工资额是：%f",adddata->yfgz);
	printf("\n\t\t\t\t该职工的个人所得税是：%f",adddata->grsds);
	printf("\n\t\t\t\t该职工的实发工资额是：%f",adddata->sfgz);

	printf("\n\n\t\t\t\t按任意键返回……");
	getch();
	return first;	//返回链表首地址
}

//*从职工工资数据文件中删除记录，用到了双向链表
struct zhigong * del(struct zhigong *first)
{
	char gonghao[10];//*接收职工工号字符数组
	char d='N';		//*接收确认删除字符：y/n
	struct zhigong *p;//中间变量

	p=first;
	if(p==NULL)	//说明内存无工资记录
	{
		printf("\n\n\t\t当前还没有职工工资记录，无法执行删除！");
		printf("\n\n\t\t按任意键返回主菜单……");
		getch();
		return first;
	}

	printf("\t请输入待删除职工工号：");
	gets(gonghao);
	while(p!=NULL)//*从链表开始处进行查找
	{
		if(strcmp(p->gonghao,gonghao)==0)//*比较并找到
		{
			printf("%-6s%-6s%-9s%-9s%-9s","工号","姓名","岗位工资","薪级工资","职务津贴");
			printf("%-9s%-9s%8s%9s\n","绩效工资","应发工资","所得税","实发工资");

			printf("%-6s%-6s%8.2f",p->gonghao,p->name,p->gwgz);
			printf("%9.2f%9.2f",p->xjgz,p->zwjt);
			printf("%9.2f%9.2f",p->jxgz,p->yfgz);
			printf("%9.2f%9.2f\n",p->grsds,p->sfgz);

			printf("\n\t\t你确认要删除%s号职工工资信息吗(y/n)？",p->gonghao);
			d=getche();
			if(d=='y'||d=='Y')//*确认删除
			{
				//以下代码实现重新建立链表关系
				if(p->front==NULL&&p->behind==NULL)//当只有一条记录时
				{
					first=NULL;
				}
				else if(p->front==NULL)//删除的是第一条记录
				{
					first=p->behind;
					first->front=NULL;
				}
				else if(p->behind==NULL)//删除的是最后一条记录
				{
					(p->front)->behind=NULL;
				}
				else	//删除非第一条记录
				{
					(p->front)->behind=p->behind;
					(p->behind)->front=p->front;
				}
				free(p);//释放被删除数据所占内存
				printf("\n\n\t\t该职工记录成功删除，按任意键返回主菜单……");
				getch();
				return first;//返回工资链表起始地址
			}
			else	//*未确认删除记录
			{
				printf("\n\n\t\t你选择了不删除该职工记录，按任意键返回主菜单……");
				getch();
				return first;
			}
		}
		p=p->behind;//指向下一项结构数据
	}
	if(d=='N'||d=='n')//该值反映未删除过记录的状态
	{
		printf("\n\t\t本单位无此工号，按任意键返回主菜单……");
		getch();
		return first;
	}
}

//*计算个人所得税
float grsds(float m)
{
	float x;	//*当月应纳税所得额
	float y=0;	//*当月应纳税额
	int n;

	x=m-2000;

	if(x>0)
		if(x<500)n=1;
		else if(x<2000)n=2;
		else if(x<5000)n=3;
		else if(x<20000)n=4;
		else if(x<40000)n=5;
		else if(x<60000)n=6;
		else if(x<80000)n=7;
		else if(x<100000)n=8;
		else n=9;
		
	switch(n)
	{
		case 9:y=(x-100000)*0.45;x=100000;
		case 8:y+=(x-80000)*0.40;x=80000;
		case 7:y+=(x-60000)*0.35;x=60000;
		case 6:y+=(x-40000)*0.30;x=40000;
		case 5:y+=(x-20000)*0.25;x=20000;
		case 4:y+=(x-5000)*0.20;x=5000;
		case 3:y+=(x-2000)*0.15;x=2000;
		case 2:y+=(x-500)*0.10;x=500;
		case 1:y+=x*0.05;
	}
	return y;
}



