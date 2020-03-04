#include "mmysql.h"

long get_unix_time()
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return tv.tv_sec;
}

//common
MYSQL* connect_mysql(IP ip,UNAME uname,char* passwd,DBNAME dbname,PORT port)
{
	MYSQL* mysql = (MYSQL*)malloc(sizeof(MYSQL));
	//1.init mysql->mysql_init(), return handle;
	if(mysql_init(mysql)==NULL)
	{
		printf("mysql init erro!\n");
		return NULL;
	}
	//2.link mysql->mysql_real_connect,if link success return mysql handle
	if(mysql_real_connect(mysql,ip,uname,passwd,dbname,port,NULL,0)==NULL)
	{
	printf("mysql link failed!\n");
	return NULL;
	}
	return mysql;
}

//common
MYSQL_RES* find_mysql(MYSQL* mysql,SQL sql)
{
	//3.find something in mysql->mysql_query.if success return 0;
	mysql_query(mysql,"set names utf8");
	if(mysql_query(mysql,sql)!=0)printf("find failed!\n");
	return mysql_store_result(mysql);
}

//private
PTOTAL init_judge(MYSQL * mysql)
{
	double total;
	PTOTAL ptotal = (PTOTAL)malloc(sizeof(TOTAL));
	SQL sql = "select * from total;";
	MYSQL_RES* res = find_mysql(mysql,sql);
	MYSQL_ROW row = mysql_fetch_row(res);
	/*before use mysql_fetch_lengths->must use mysql_fetch_row*/
	unsigned long * ul = mysql_fetch_lengths(res);
	if(ul[2] == 0)
	{	
		printf("this is the fisrt you use, plese input the init money:\n");
		scanf("%lf",&total);
		char msql[256]={0};
		sprintf(msql,"update total set total = %2f , listcount = 0 where id = 1;",total); //you must set mysql table id = 1;
		mysql_query(mysql,msql);	
		printf("init success , welcome!\n");
	}
	ptotal->listcount = atoi(row[1]);
	ptotal->total = total;
	return ptotal;
}

int insert_mysql(MYSQL *mysql,PCONT con)
{
	char sql[256] ={0};
	sprintf(sql,"insert into content(flag,getorlost,remarks,docnum) values(%d,%.2lf,'%s','%s');\n",con->flag,con->getorlost,con->remarks,con->docnum);
    if(mysql_query(mysql,sql)!=0)return 0;
	return 1;
}


