/*************************************************
Copyright (C), 1988-1999, Huawei Tech. Co., Ltd.
File name: // �ļ���
Author: Version: Date: // ��չ�� 6.29
Description: // ������ϸ˵���˳����ļ���ɵ���Ҫ���ܣ�������ģ��
// �����Ľӿڣ����ֵ��ȡֵ��Χ�����弰������Ŀ�
// �ơ�˳�򡢶����������ȹ�ϵ
Others: // �������ݵ�˵��
Function List: // ��Ҫ�����б�ÿ����¼Ӧ���������������ܼ�Ҫ˵��
1. find()
2.modify()
3.add()
4.del()
5.write()
6.list()
7.read()

History: // �޸���ʷ��¼�б�ÿ���޸ļ�¼Ӧ�����޸����ڡ��޸�
// �߼��޸����ݼ���
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


struct zhigong * read();//*��ȡְ����������
void write(struct zhigong *first);	//*д��ְ���������ݼ�¼
void find(struct zhigong *first);	//*��ѯְ���������ݼ�¼
void modify(struct zhigong *first);	//*�޸�ְ���������ݼ�¼
struct zhigong * add(struct zhigong *first);//*����ְ�����������ļ���
struct zhigong * del(struct zhigong *first);	//*ɾ��ְ�����������ļ���
float grsds(float m);	//*�����������˰
void list(struct zhigong *first);	//*���ְ����¼

struct zhigong		//*����ְ���������ݽṹ��
{
	struct zhigong *front;	
	struct zhigong *behind;	
	char gonghao[10];	//*ְ������
	char name[10];	//*ְ������
	float gwgz;		//*��λ����
	float xjgz;		//*н������
	float zwjt;		//*ְ�����
	float jxgz;		//*��Ч����
	float yfgz;		//*Ӧ������
	float grsds;	//*��������˰
	float sfgz;		//*ʵ������
};

void main()
{
	char ch;
	struct zhigong *first;	//*����ָ��ṹ���ָ�����
	first=read();  //*�������ļ��ж�ȡְ���������ݲ���ʼ��ְ�����ʽṹ������
	while(TRUE)
	{
		system("cls");	//*����
		printf("\n\n\t### ��ӭʹ�ù��������ѧ�������Ϣ��ȫѧԺְ�����ʹ���ϵͳ ###\n\n\n");
		printf("\t��ѡ��(1-7) :\n");
		printf("\t==========================================================\n");
		printf("\t|\t1.��ѯְ�����ʼ�¼\t\t\t\t|\n");
		printf("\t|\t2.�޸�ְ�����ʼ�¼\t\t\t\t|\n");
		printf("\t|\t3.���ְ�����ʼ�¼\t\t\t\t|\n");
		printf("\t|\t4.ɾ��ְ�����ʼ�¼\t\t\t\t|\n");
		printf("\t|\t5.�������ݵ��ļ�\t\t\t\t|\n");
		printf("\t|\t6.���ְ����¼\t\t\t\t\t|\n");
		printf("\t|\t7.�˳�\t\t\t\t\t\t|\n");
		printf("\t==========================================================\n");
		printf("\n\t���ѡ���ǣ�");
		ch=getche();

		switch(ch)
		{
			   case '1':find(first);break;	//*��ѯ
			   case '2':modify(first);break;	//*�޸�
			   case '3':first=add(first);break;	//*���
			   case '4':first=del(first);break;	//*ɾ��
			   case '5':write(first);break;	//*����
			   case '6':list(first);break;	//*���
			   case '7':return;			//*�˳�
			   default:printf("\t\t�밴�������������ѡ��1��7��\n");getch();
		}
	}
	return;
}

//*�������ļ�gz.dat�ж�ȡְ���������ݵ��ṹ����zggz��
struct zhigong * read()
{
	FILE *file;	//*�����ļ�ָ��
	int n=0;		//*������¼ְ����¼���ı���
	struct zhigong *first,*readdata;//��¼�׵�ַ���·����ڴ��ַ
	struct zhigong *p;	//�м����

	if((file=fopen("gz.dat","rb"))==NULL)//*��ְ�����������ļ��������ж��Ƿ�ʧ��
	{
		printf("\n\n\tְ�����������ļ��޷��򿪣���Ϊ��! ");
		printf("\n\n\t��������������˵�����");
		getch();
		return 0;
	}
	else	//*�ļ��򿪳ɹ�ʱ
	{
		//��̬��������ڴ�ռ䣬������ڴ�����׵�ַ
		readdata=(struct zhigong *)malloc(sizeof(struct zhigong));
		//ѭ����ȡ�ļ����ݵ��·�����ڴ�ռ�
		while(fread(readdata,sizeof(struct zhigong),1,file)==1)
		{
			if(n==0)	//˵����Ҫ����������ʼ��
			{
				first=readdata;
				first->front=NULL;
				first->behind=NULL;
				p=readdata;
			}
			else	//˵��׷������������
			{
				p->behind=readdata;
				readdata->front=p;
				readdata->behind=NULL;
				p=readdata;
			}
			n++;	//ְ��������1
			readdata=(struct zhigong *)malloc(sizeof(struct zhigong));
		}
		fclose(file);	//*�ر��ļ�ָ��
		printf("\n\n\tְ���������ݶ�ȡ��ϣ�����%d��! \n",n);
		printf("\n\t5���Ӻ�������� \n",n);
		Sleep(5000);	//*��ʱ5����
	}
	printf("\n��������������˵�����");
	return first;
}


//*��ְ�����������ļ���д���¼
void write(struct zhigong * first)
{
	FILE *file;	//*�����ļ�ָ��
	int n=0;	//ͳ�ƴ����ļ�ְ������

	if(first==NULL)	//*�ڴ����޹��ʼ�¼
	{
		printf("û�����ݿɴ�! ��������������˵���\n");
		getch();
		return;
	}
	if((file=fopen("gz.dat","wb"))!=NULL)//*�Զ����Ʒ�ʽ��ְ�����������ļ��������ж��Ƿ�ʧ��
	{
		do
		{
			fwrite(first,sizeof(struct zhigong),1,file);//*���м�¼һ��д���ļ�
			n++;
			first=first->behind;
		}while(first!=NULL);
		fclose(file);	//*�ر��ļ�ָ��
		printf("\n\n\t\t%d��ְ����¼�������! \n",n);
	}
	else	//*�ļ��򿪲��ɹ�ʱ
		printf("\t\t�޷���ְ�����������ļ�! \n");
	printf("\n\t\t��������������˵�����");
	getch();
}

//*��ѯְ���������ݼ�¼(���ݹ���)
void find(struct zhigong *first)
{
	char gonghao[10];//*����ְ�������ַ�����

	if(first==NULL)	//˵���ڴ��޹��ʼ�¼
	{
		printf("\n\n\t\t��ǰ��û��ְ�����ʼ�¼����������������˵�����");
		getch();
		return;
	}

	printf("\t������ְ�����ţ�");//*��ʾ��Ϣ
	gets(gonghao);//*�Ӽ��̶�ȡ�ַ���

	while(first!=NULL)//*������ʼ������
	{
		if(strcmp(first->gonghao,gonghao)==0)//*�Ƚϲ��ҵ�
		{
			//*��ʾ��ְ���������
			printf("\n\t\t\t  ��ְ������������£�");
			printf("\n\t\t\t  ===================\n\n");

			printf("%-6s%-6s%-9s%-9s%-9s","����","����","��λ����","н������","ְ�����");
			printf("%-9s%-9s%8s%9s\n","��Ч����","Ӧ������","����˰","ʵ������");

			printf("%-6s%-6s%8.2f",first->gonghao,first->name,first->gwgz);
			printf("%9.2f%9.2f",first->xjgz,first->zwjt);
			printf("%9.2f%9.2f",first->jxgz,first->yfgz);
			printf("%9.2f%9.2f\n",first->grsds,first->sfgz);

			printf("\n ��������������˵�����");
			getch();
			return;
		}
		first=first->behind;
	}
	//ѭ���Զ�������ζ��δ�ҵ�
	printf("\n\n\t\t���������ְ����������򲻴��ڣ���������������˵�����\n");
	getch();
	return;
}

//*���ְ�����ʼ�¼
void list(struct zhigong * first)
{
	system("cls");
	printf("\n\n\t\t\t ȫ��ְ�������������\n");
	printf("\t\t\t======================\n\n");
	if(first!=NULL)	//˵���ڴ����������
	{
		do
		{
			printf("%-6s%-6s%-9s%-9s%-9s","����","����","��λ����","н������","ְ�����");
			printf("%-9s%-9s%8s%9s\n","��Ч����","Ӧ������","����˰","ʵ������");

			printf("%-6s%-6s%8.2f",first->gonghao,first->name,first->gwgz);
			printf("%9.2f%9.2f",first->xjgz,first->zwjt);
			printf("%9.2f%9.2f",first->jxgz,first->yfgz);
			printf("%9.2f%9.2f\n",first->grsds,first->sfgz);

			first=first->behind;	//����firstָ����������һ��ṹ����
		}while(first!=NULL); //��Ϊ��˵���ṹ���ݴ���
	}
	printf("  ��������������˵�����");
	getch();
	return;
}

//*�޸�ְ���������ݼ�¼
void modify(struct zhigong *first)
{
	char gonghao[10];//*����ְ�������ַ�����

	if(first==NULL)	//˵���ڴ��޹��ʼ�¼
	{
		printf("\n\n\t\t��ǰ��û��ְ�����ʼ�¼����������������˵�����");
		getch();
		return;
	}

	printf("\t������ְ�����ţ�");
	gets(gonghao);//*�Ӽ��̶�ȡ�ַ���

	while(first!=NULL)//*������ʼ������
	{
		if(strcmp(first->gonghao,gonghao)==0)//*�Ƚϲ��ҵ�
		{
			//*��ʾ��ְ���������
			printf("\n\t\t\t  ��ְ������������£�");
			printf("\n\t\t\t  ===================\n\n");

			printf("%-6s%-6s%-9s%-9s%-9s","����","����","��λ����","н������","ְ�����");
			printf("%-9s%-9s%8s%9s\n","��Ч����","Ӧ������","����˰","ʵ������");

			printf("%-6s%-6s%8.2f",first->gonghao,first->name,first->gwgz);
			printf("%9.2f%9.2f",first->xjgz,first->zwjt);
			printf("%9.2f%9.2f",first->jxgz,first->yfgz);
			printf("%9.2f%9.2f\n",first->grsds,first->sfgz);

			//*���ո�ְ���µĹ�������
			printf("\n\t\t�������ְ���µĸ�λ���ʣ�");
			scanf("%f",&first->gwgz);
			printf("\t\t�������ְ���µ�н�����ʣ�");
			scanf("%f",&first->xjgz);
			printf("\t\t�������ְ���µ�ְ�������");
			scanf("%f",&first->zwjt);
			printf("\t\t�������ְ���µļ�Ч���ʣ�");
			scanf("%f",&first->jxgz);

			//*����Ӧ�����ʡ���������˰��ʵ������
			first->yfgz=first->gwgz+first->xjgz+first->zwjt+first->jxgz;
			first->grsds=grsds(first->yfgz);
			first->sfgz=first->yfgz-first->grsds;
			//*ͬ����ʾ������
			printf("\n\t\t��ְ����Ӧ�����ʶ��ǣ�%f",first->yfgz);
			printf("\n\t\t��ְ���ĸ�������˰�ǣ�%f",first->grsds);
			printf("\n\t\t��ְ����ʵ�����ʶ��ǣ�%f",first->sfgz);

			printf("\n\n\t\t��ְ�����������޸ĳɹ�����������������˵�����");
			getch();
			return;
		}
		first=first->behind;
	}
	//ѭ���Զ�������ζ��δ�ҵ�
	printf("\n\n\t\t���������ְ����������򲻴��ڣ���������������˵�����\n");
	getch();
	return;
}

//*��ְ�����������ļ������Ӽ�¼
struct zhigong * add(struct zhigong *first)
{
	struct zhigong *adddata;//��¼�׵�ַ���·����ڴ��ַ
	struct zhigong *p;	//�м����
	adddata=(struct zhigong *)malloc(sizeof(struct zhigong));
	if(first==NULL)//˵����Ҫ����������������
	{
		first=adddata;
		first->front=NULL;
		first->behind=NULL;
	}
	else	//˵����Ҫ�ҵ��������λ��
	{
		p=first;
		while(p->behind!=NULL)
		{
			p=p->behind;
		}
		//��������׷����ָ��ָ���ϵ
		p->behind=adddata;
		adddata->front=p;
		adddata->behind=NULL;
	}
	//�����Ǵ�����һ������׷�ӹ��ʼ�¼����ֻ��adddata�������
	printf("\t������ְ�����ţ�");
	fflush(stdin);	//*������̻�����
	gets(adddata->gonghao);
	printf("\t\t\t\t������ְ��������");
	fflush(stdin);	//*������̻�����
	gets(adddata->name);
	printf("\n\t\t\t\t�������ְ���µĸ�λ���ʣ�");
	scanf("%f",&adddata->gwgz);
	printf("\t\t\t\t�������ְ���µ�н�����ʣ�");
	scanf("%f",&adddata->xjgz);
	printf("\t\t\t\t�������ְ���µ�ְ�������");
	scanf("%f",&adddata->zwjt);
	printf("\t\t\t\t�������ְ���µļ�Ч���ʣ�");
	scanf("%f",&adddata->jxgz);

	//*����Ӧ�����ʡ���������˰��ʵ������
	adddata->yfgz=adddata->gwgz+adddata->xjgz+adddata->zwjt+adddata->jxgz;
	adddata->grsds=grsds(adddata->yfgz);
	adddata->sfgz=adddata->yfgz-adddata->grsds;
	//*������ϼ�������///
	printf("\n\t\t\t\t��ְ����Ӧ�����ʶ��ǣ�%f",adddata->yfgz);
	printf("\n\t\t\t\t��ְ���ĸ�������˰�ǣ�%f",adddata->grsds);
	printf("\n\t\t\t\t��ְ����ʵ�����ʶ��ǣ�%f",adddata->sfgz);

	printf("\n\n\t\t\t\t����������ء���");
	getch();
	return first;	//���������׵�ַ
}

//*��ְ�����������ļ���ɾ����¼���õ���˫������
struct zhigong * del(struct zhigong *first)
{
	char gonghao[10];//*����ְ�������ַ�����
	char d='N';		//*����ȷ��ɾ���ַ���y/n
	struct zhigong *p;//�м����

	p=first;
	if(p==NULL)	//˵���ڴ��޹��ʼ�¼
	{
		printf("\n\n\t\t��ǰ��û��ְ�����ʼ�¼���޷�ִ��ɾ����");
		printf("\n\n\t\t��������������˵�����");
		getch();
		return first;
	}

	printf("\t�������ɾ��ְ�����ţ�");
	gets(gonghao);
	while(p!=NULL)//*������ʼ�����в���
	{
		if(strcmp(p->gonghao,gonghao)==0)//*�Ƚϲ��ҵ�
		{
			printf("%-6s%-6s%-9s%-9s%-9s","����","����","��λ����","н������","ְ�����");
			printf("%-9s%-9s%8s%9s\n","��Ч����","Ӧ������","����˰","ʵ������");

			printf("%-6s%-6s%8.2f",p->gonghao,p->name,p->gwgz);
			printf("%9.2f%9.2f",p->xjgz,p->zwjt);
			printf("%9.2f%9.2f",p->jxgz,p->yfgz);
			printf("%9.2f%9.2f\n",p->grsds,p->sfgz);

			printf("\n\t\t��ȷ��Ҫɾ��%s��ְ��������Ϣ��(y/n)��",p->gonghao);
			d=getche();
			if(d=='y'||d=='Y')//*ȷ��ɾ��
			{
				//���´���ʵ�����½��������ϵ
				if(p->front==NULL&&p->behind==NULL)//��ֻ��һ����¼ʱ
				{
					first=NULL;
				}
				else if(p->front==NULL)//ɾ�����ǵ�һ����¼
				{
					first=p->behind;
					first->front=NULL;
				}
				else if(p->behind==NULL)//ɾ���������һ����¼
				{
					(p->front)->behind=NULL;
				}
				else	//ɾ���ǵ�һ����¼
				{
					(p->front)->behind=p->behind;
					(p->behind)->front=p->front;
				}
				free(p);//�ͷű�ɾ��������ռ�ڴ�
				printf("\n\n\t\t��ְ����¼�ɹ�ɾ������������������˵�����");
				getch();
				return first;//���ع���������ʼ��ַ
			}
			else	//*δȷ��ɾ����¼
			{
				printf("\n\n\t\t��ѡ���˲�ɾ����ְ����¼����������������˵�����");
				getch();
				return first;
			}
		}
		p=p->behind;//ָ����һ��ṹ����
	}
	if(d=='N'||d=='n')//��ֵ��ӳδɾ������¼��״̬
	{
		printf("\n\t\t����λ�޴˹��ţ���������������˵�����");
		getch();
		return first;
	}
}

//*�����������˰
float grsds(float m)
{
	float x;	//*����Ӧ��˰���ö�
	float y=0;	//*����Ӧ��˰��
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



