#include <iostream>
#include <string>
#include <my_global.h>
#include <mysql.h>
#pragma comment(lib,"libmySQL.lib")

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "111111"
#define DB_NAME "dingdongdang"
#define CHOP(x) x[strlen(x)-1]=' '

using namespace std;

int main(void) {
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
	int fields;
	int i;


	mysql_init(&mysql); //mysql 초기화
	mysql_set_character_set(&mysql, "euckr");
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "euckr");
	mysql_options(&mysql, MYSQL_INIT_COMMAND, "SET NAMES euckr");
	mysql_real_connect(&mysql, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, NULL, 0);

	mysql_query(&mysql, "select id,singer,title from period_3 order by rand() limit 10");
	res = mysql_store_result(&mysql);
	fields = mysql_num_fields(res); //필드 갯수 구하기
	while (row = mysql_fetch_row(res)) {
		for (i = 0; i < fields; i++) {
			cout << " " << row[i];
		}cout << endl;
	}
	mysql_free_result(res);
	mysql_close(&mysql);
}
