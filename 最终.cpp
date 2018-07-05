/********************************************************
Copyright (C),2018-2020,���������ѧ�������Ϣ��ȫѧԺ
File name:
Author:��չ��	Version:1.0.0	Date:2018.6.29
Description:��ϵͳ�����Ŀ����ʵ��ְ�����ʼ�¼��¼�롢
	��ѯ���޸ġ���ӡ�ɾ�������ݱ��湦�ܡ�ϵͳӦʵ�ֹ��ʼ�¼����
	����ӡ����桢���ݹ��Ž��в�ѯ�������ɾ�������������
	�޸ĵ�ͬʱ�Զ���ɸ�������˰��Ӧ�����ʵļ��㡣
Version:1.0.0
Function List:
	void read();	//�������ļ��ж�ȡ�����Ϣ����
	void write();	//����ְ��������Ϣ����
	void find();	//��ѯְ��������Ϣ����
	void list();	//���ְ��������Ϣ����
	void modify();	//�޸�ְ��������Ϣ����
	void del();		//ɾ��ְ��������Ϣ����
	void add();		//���ְ��������Ϣ����
	float grsd(float v);	//�����������˰		

*********************************************************/

#include<iostream>
#include<string.h>
#include<fstream>
#include<conio.h>
#include<iomanip>
using namespace std;

int n=0;	//��¼ְ������

//�����Զ������غ���
void read();
void write();
void find();
void list();
void modify();
void del();
void add();
float grsd(float v);

struct zhigong		//ְ�����ݽṹ
{   char number[10];
    char name[10];
    float post_wage;		//Ա���ĸ�λ����
    float pay_salary;		//Ա����н������
    float duty_allowance;	//Ա�����������
    float merit_pay;		//��Ч����
    float gross_pay;		//Ӧ������
    float income_tax;		//��������˰
    float payroll;			//ʵ������
    
};
struct zhigong zggz[100];	//����100��ְ��������Ϣ

/*************************************************
Function: //read
Description: // ���ļ��ж�ȡ����
*************************************************/
void read()
{
    FILE*Read=fopen("gx.dat","ab+");
    if(Read)	//�ļ��򿪳ɹ�
    {   
        while(!feof(Read))
        {
            char A=fgetc(Read);
            char a=EOF;
            if(A!=a)
            {
                fscanf(Read,"%s%s%f%f%f%f%f%f%f",
					&zggz[n].number,&zggz[n].name,&zggz[n].post_wage,
					&zggz[n].pay_salary,&zggz[n].duty_allowance,&zggz[n].merit_pay,
					&zggz[n].gross_pay,&zggz[n].income_tax,&zggz[n].payroll);
                n++;
            }
        }
        fclose(Read);
    }
    else
    {
        printf("\n�ļ���ʧ�ܣ�");
    }
    
}
/*************************************************
Function: // write
Description: // ����ְ������
Input: // ��������ְ������
Output: // ��������
*************************************************/
void write()
{
    FILE*DF_05=fopen("gx.dat","wb");
    if(DF_05)
    {   
         for(int i=0;i<n;i++)
        {
            fprintf(DF_05,"\t%-10s%-10s%-10f\t%-10f\t%-10f\t%-10f\t%-10f\t%-10f\t%-10f",
				zggz[i].number,zggz[i].name,zggz[i].post_wage,
                zggz[i].pay_salary,zggz[i].duty_allowance,zggz[i].merit_pay,
				zggz[i].gross_pay,zggz[i].income_tax,zggz[i].payroll);
        }
        fclose(DF_05);
        printf("\n�ļ�����ɹ���");
    }
    else
    {
        printf("\n�ļ���ʧ�ܣ�");
    }
    printf("\n��������������˵�");
    if(getch())
    {   
        system("cls");
        return;
    }
}
/*************************************************
Function: // find
Description: // ����ְ������
Input: // ��������ְ������
Output: // ��ʾ����
*************************************************/
void find()
{
    char gonghao[10];
    printf("�������ѯ�Ĺ���");
    scanf("%s",gonghao);
    for(int i=0;i<n;i++)
    {   
        if(strcmp(gonghao,zggz[i].number)==0)
        {
            printf("-------------------------------��ְ��������Ϣ����------------------------------");
            printf( "حְ������:%-15sحְ������:%-15sح��λ����:%-15f\n"
                    "حн������:%-15fحְ�����:%-15fح��Ч����:%-15f\n"
                    "حӦ������:%-15fح��������˰:%-13fحʵ������:%-15f\n",
                zggz[i].number, zggz[i].name, zggz[i].post_wage, 
                zggz[i].pay_salary, zggz[i].duty_allowance, zggz[i].merit_pay, 
                zggz[i].gross_pay, zggz[i].income_tax, zggz[i].payroll);
         
            break;
            
        }
		if(i=n-1)
    {
    printf("���������ְ����������򲻴��ڣ�");
	break;
    }
    }
    
    printf("\n��������������˵�");
    if(getch())
    {   
        system("cls");
        return;
    }
    
}
/*************************************************
Function: //list
Description: // ���ְ������
Input: // ������������
Output: // ��������
*************************************************/
void list()
{
    ofstream DF_05("gx.dat");
    printf("------------------------------ȫ��ְ��������Ϣ����------------------------------\n");
    for(int i=0;i<n;i++)
    {
        printf( "حְ������:%-15sحְ������:%-15sح��λ����:%-15f\n"
                "حн������:%-15fحְ�����:%-15fح��Ч����:%-15f\n"
                "حӦ������:%-15fح��������˰:%-13fحʵ������:%-15f\n\n",
                zggz[i].number, zggz[i].name, zggz[i].post_wage, 
                zggz[i].pay_salary, zggz[i].duty_allowance, zggz[i].merit_pay, 
                zggz[i].gross_pay, zggz[i].income_tax, zggz[i].payroll);
        }

    printf("\n��������������˵�");
    if(getch())
    {   
        system("cls");
        return;
    }
}
/*************************************************
Function: // modify
Description: // �޸�ְ������
Input: // ��������ְ������
Output: // �޸ĺ������
*************************************************/
void modify()
{
    char gonghao[10];
    printf("�������ѯ�Ĺ���");
    scanf("%s",gonghao);

    for(int i=0;i<n;i++)
    {
        if(strcmp(zggz[i].number,gonghao)==0)
        {
            printf("-------------------------------��ְ��������Ϣ����-------------------------------");
            printf( "حְ������:%-15sحְ������:%-15sح��λ����:%-15f\n"
                    "حн������:%-15fحְ�����:%-15fح��Ч����:%-15f\n"
                    "حӦ������:%-15fح��������˰:%-13fحʵ������:%-15f\n",
                    zggz[i].number, zggz[i].name, zggz[i].post_wage, 
                    zggz[i].pay_salary, zggz[i].duty_allowance, zggz[i].merit_pay, 
                    zggz[i].gross_pay, zggz[i].income_tax, zggz[i].payroll);        

            printf("�������ְ���µĸ�λ���ʣ�");
            scanf("%f",&zggz[i].post_wage);
            printf("\n�������ְ���µ�н�����ʣ�");
            scanf("%f",&zggz[i].pay_salary);
            printf("\n�������ְ���µ����������");
            scanf("%f",&zggz[i].duty_allowance);
            printf("\n�������ְ���µļ�Ч���ʣ�");
            scanf("%f",&zggz[i].merit_pay);
    
            zggz[i].gross_pay=zggz[i].post_wage+zggz[i].pay_salary+zggz[i].duty_allowance+zggz[i].merit_pay;    //����Ӧ������
            zggz[i].income_tax=grsd(zggz[i].gross_pay);    //�����������˰
            zggz[i].payroll=zggz[i].gross_pay=zggz[i].income_tax;    //����Ӧ������

            printf("---------------------------��ְ���޸ĺ�Ĺ�����Ϣ����---------------------------");
            printf( "حְ������:%-15sحְ������:%-15sح��λ����:%-15f\n"
                    "حн������:%-15fحְ�����:%-15fح��Ч����:%-15f\n"
                    "حӦ������:%-15fح��������˰:%-13fحʵ������:%-15f\n",
                    zggz[i].number, zggz[i].name, zggz[i].post_wage, 
                    zggz[i].pay_salary, zggz[i].duty_allowance, zggz[i].merit_pay, 
                    zggz[i].gross_pay, zggz[i].income_tax, zggz[i].payroll);        
        }
    }
    
    printf("\n��������������˵�");
    if(getch())
    {   
        system("cls");
        return;
    }
}
/*************************************************
Function: // del
Description: // ɾ��ְ������
Input: // ����ɾ��ְ������
Output: // ������ɾ��
*************************************************/
void del()
{
    char gonghao[10];
    cout<<"������Ҫɾ����ְ����";
    scanf("%s",gonghao);
   
    for(int i=0;i<n;i++)
    {
        if(strcmp(zggz[i].number,gonghao)==0)
        {
            printf("--------------------------------�鵽��ְ��������Ϣ����--------------------------------\n");;
            printf( "حְ������:%-15sحְ������:%-15sح��λ����:%-15f\n"
                    "حн������:%-15fحְ�����:%-15fح��Ч����:%-15f\n"
                    "حӦ������:%-15fح��������˰:%-13fحʵ������:%-15f\n",
                    zggz[i].number, zggz[i].name, zggz[i].post_wage, 
                    zggz[i].pay_salary, zggz[i].duty_allowance, zggz[i].merit_pay, 
                    zggz[i].gross_pay, zggz[i].income_tax, zggz[i].payroll);
            printf("�����Ҫɾ�����ְ���Ĺ�����Ϣ��\n");
            printf("�ǣ��밴1\t\t���밴2\n");
            int flg;
            scanf("%d",&flg);
            if(flg==1)
            {
                for(int j=i;j<n-1;j++)
                {
                    zggz[j]=zggz[j+1];
                }
                n=n-1;
                printf("������¼�ѳɹ�ɾ��");
            }
            else if(flg==2)
            {
                printf("ȡ��ɾ��������¼");
            }
            else
            {
                printf("��������ȷ������");
            }

        }
    }
    printf("\n��������������˵�");
    if(getch())
    {   
        system("cls");
        return;
    }
    
}
/*************************************************
Function: // add
Description: // ���ְ������
Input: // ���̼���ְ������
Output: // �����ݴ���
*************************************************/
void add()
{
    n=n+1;
    printf("�������ְ����ְ������,ְ������,��λ����,н������,�������,��Ч����\n");
    scanf("%s%s%f%f%f%f",&zggz[n-1].number,&zggz[n-1].name,&zggz[n-1].post_wage,&zggz[n-1].pay_salary,&zggz[n-1].duty_allowance,&zggz[n-1].merit_pay);

    zggz[n-1].gross_pay=zggz[n-1].post_wage + zggz[n-1].pay_salary + zggz[n-1].duty_allowance + zggz[n-1].merit_pay;    //����Ӧ������
    zggz[n-1].income_tax=grsd(zggz[n-1].gross_pay);    //�����������˰
    zggz[n-1].payroll=zggz[n-1].gross_pay - zggz[n-1].income_tax;    //����Ӧ������

    printf( "------------------------��ӳɹ������ְ������ϢΪ��------------------------\n");
    printf( "حְ������:%-15sحְ������:%-15sح��λ����:%-15f\n"
            "حн������:%-15fحְ�����:%-15fح��Ч����:%-15f\n"
            "حӦ������:%-15fح��������˰:%-13fحʵ������:%-15f\n",
            zggz[n-1].number,zggz[n-1].name,zggz[n-1].post_wage,
            zggz[n-1].pay_salary,zggz[n-1].duty_allowance,zggz[n-1].merit_pay,
            zggz[n-1].gross_pay,zggz[n-1].income_tax,zggz[n-1].payroll);

    printf("\n��������������˵�");
    if(getch())
    {   
        system("cls");
        return;
    }
}
/*************************************************
Function: // grsds
Description: // �����������˰
Input: // �����������
Output: // ���Ӧ������
*************************************************/
float grsd(float v)
{
    float x=v;
    float y=0;
    int n;
    
    if(x>0)
    {
        if(x<500)    n=1;
        else if(x<2000)    n=2;
        else if(x<5000)    n=3;
        else if(x<20000)    n=4;
        else if(x<40000)    n=5;
        else if(x<60000)    n=6;
        else if(x<80000)    n=7;
        else if(x<100000)    n=8;
        else n=9;
    }
    
    switch(n)
    {
        case 8:y=y+(x-80000)*0.4;
        case 7:y=y+(x-60000)*0.35;
        case 6:y=y+(x-40000)*0.3;
        case 5:y=y+(x-20000)*0.25;
        case 4:y=y+(x-5000)*0.2;
        case 3:y=y+(x-2000)*0.15;
        case 2:y=y+(x-500)*0.1;
        case 1:y=y+x*0.05;
    }

    return y;
}

int main()
{

    system("cls");
    read();
    int flg;
    while(1)
    {
        printf("        ### ��ӭʹ�ù��������ѧ�������Ϣ��ȫѧԺְ�����ʹ���ϵͳ ###\n\n");
        printf("        ��ѡ������<1-7>                                   \n");
        printf("        ==============================================================\n");
        printf("        :                     1�� ��ѯְ�����ʼ�¼                   :\n");
        printf("        :                     2�� �޸�ְ�����ʼ�¼                   :\n");
        printf("        :                     3�� ���ְ�����ʼ�¼                   :\n");
        printf("        :                     4�� ɾ��ְ�����ʼ�¼                   :\n");
        printf("        :                     5�� ����ְ�����ʼ�¼                   :\n");
        printf("        :                     6�� ���ְ�����ʼ�¼                   :\n");
        printf("        :                     7�� �˳�ϵͳ                           :\n");
        printf("        ==============================================================\n");
        printf("                        \n");
        printf("                        \n");
        printf("		           ������һ������(������)~*[ ]\b\b");
        scanf("%d",&flg);
        if(flg>=1&&flg<=7)
        {
            switch(flg)
            {
                case 1:find();break;
                case 2:modify();break;
                case 3:add();break;
                case 4:del();break;
                case 5:write();break;
                case 6:list();break;
                case 7:return;
            }
        }
        else
        {
            printf("��Чָ�����������");
            getch();
            system("cls");
        }
    }

    return;
    
}
