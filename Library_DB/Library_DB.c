#include "Library_DB.h"

int Library_DB_t_init(library_db_t* DB_CONN){
	memset(DB_CONN,0,sizeof(library_db_t));
	return 0;

}
int Library_DB_close_connection(library_db_t* DB_CONN){
	mysql_close(&(DB_CONN->mysql));
	return 0;
}
int Library_DB_connect(library_db_t* DB_CONN){
	if(!mysql_real_connect(&(DB_CONN->mysql),NULL,GUEST_ID,GUEST_PW,DB_NAME,PORT,(char*)NULL,0)){
		fprintf(stderr, "%s\n", mysql_error(&(DB_CONN->mysql)) );
		return -1;
	}
	printf("connected\n");
	return 0;
}
int Library_DB_send_query(library_db_t* DB_CONN){
	if(mysql_query(&(DB_CONN->mysql),DB_CONN->query)){
		fprintf(stderr, "%s\n", mysql_error(&(DB_CONN->mysql)) );
		mysql_close(&(DB_CONN->mysql));
		return -2;		
	}
	printf("Query successfully sent...\nWaiting for result...\n");
	return 0;
}
int Library_DB_recv_result(library_db_t* DB_CONN){
	DB_CONN->result = mysql_store_result(&(DB_CONN->mysql));
	if(DB_CONN->result == NULL){
		fprintf(stderr, "%s\n", mysql_error(&(DB_CONN->mysql)) );
		mysql_close(&(DB_CONN->mysql));
		return -3;
	}
	printf("Result succesfully stored...\n");
	return 0;
}
int Library_DB_print_result(library_db_t* DB_CONN){
	DB_CONN->num_fields = mysql_num_fields(DB_CONN->result);
	if(DB_CONN->num_fields<=0){
		printf("Number of field is less than 1...\n");
		mysql_free_result(DB_CONN->result);
		mysql_close(&(DB_CONN->mysql));
		return -4;
	}
	int i=0;
	printf("Printing result...\n\n");
	while(DB_CONN -> num_row = mysql_fetch_row(DB_CONN->result)){
		for(i=0;i<DB_CONN -> num_fields;i++){
			printf("%s	",DB_CONN->num_row[i] ? DB_CONN->num_row[i] : "NULL");
		}
		printf("\n");
		
	}
	printf("\n\n Result Printed\n");
	mysql_free_result(DB_CONN->result);
	return 0;
}






