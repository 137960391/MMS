#include <stdio.h>
#include "mmysql.h"


int main()
{
    MYSQL* mysql = connect_mysql("212.64.6.100","root","123456","mydb",3306);
	PTOTAL total = init_judge(mysql);
	PCONT con = (PCONT)malloc(sizeof(CONT));
	printf("last your money is %.2lf\n",total->total);
	printf("income or pay , if you are incoming plese input 1 , paying input 2\n");
	scanf("%d",&con->flag);
	switch(con->flag)
	{
		case 1:
		printf("you are incoming , please input the amount of income\n");
		scanf("%lf",&con->getorlost);
		printf("please input the reason of the income\n");
		scanf("%s",con->remarks);
		break;
		case 2:
		printf("you are paying , please input the amount of pay\n");
		scanf("%lf",&con->getorlost);
		printf("please input the reason of the pay\n");
		scanf("%s",con->remarks);
		break;
		default:
		printf("input error!\n");
	}
	sprintf(con->docnum,"dh%ld",get_unix_time());
	//printf("");
	printf("con->flag:%d\n",con->flag);
	printf("con->getorlost:%.2lf\n",con->getorlost);
	printf("con->remarks:%s\n",con->remarks);
	printf("con->flag:%s\n",con->docnum);
	if(insert_mysql(mysql,con))
	{
		printf("insert success!\n");
		if(con->flag==2)total->total -=con->getorlost;
		if(con->flag==1)total->total +=con->getorlost;
		char sql[256]={0};
		sprintf(sql,"update total set listcount = %d , total = %.2lf where id = 1;",++total->listcount,total->total);
		mysql_query(mysql,sql);
		printf("now , all your money is %.2lf\n",total->total);
		return 0;
	}
	return 1;
}



