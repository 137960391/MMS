#ifndef MMYSQL_H_INCLUDE
#define MMYSQL_H_INCLUDE
#include <stdio.h>
#include <mysql.h>
#include <sys/time.h>
typedef char* IP; 
typedef int PORT;
typedef char* UNAME;
typedef char* DBNAME;
typedef char* SQL;
MYSQL* connect_mysql(IP ip,UNAME uname,char* passwd,DBNAME dbname,PORT port);
MYSQL_RES* find_mysql(MYSQL*,SQL);
long get_unix_time();
typedef struct content
{
	int flag;
	double getorlost;
	char remarks[64];
	char docnum[64]; //document num
}CONT,*PCONT;
typedef struct total
{
	int listcount;
	double total;
}TOTAL,*PTOTAL;
int insert_mysql(MYSQL*,PCONT);
PTOTAL init_judge(MYSQL *);
#endif
