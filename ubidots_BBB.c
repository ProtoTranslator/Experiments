/*****************************CURL POST CODE****************************************/
#include<curl/curl.h>
#include<stdio.h>
#include<string.h>
#include<stddef.h>
#include<time.h>
#include<termios.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
char responseData[3];
int file,status;
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	int i;
	strncpy(responseData,&ptr[87],90);
	i=atoi(responseData);
	printf("\nResponse:%d\n",i);
	if(i==1)
	{
		printf("\nON");
		status=write(file,responseData,sizeof(responseData));
		if(status==-1)
		{
			perror("\nError in writing:");
			exit(-1);
		}
	}
}
void main()
{	
	int value,option;
	char data[20];
	struct termios new,old;
	file=open("/dev/ttyO1",O_RDWR | O_NOCTTY);
	if(file==-1)
	{
		perror("TTY not opening:");
		exit(-1);
	}
	tcgetattr(file,&old);
	new.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
	new.c_iflag = IGNPAR | ICRNL;
	new.c_oflag = 0;
	new.c_lflag = 0;
	new.c_cc[VTIME] = 0;
	new.c_cc[VMIN]  = 1;
	tcflush(file,TCIFLUSH);
	tcsetattr(file,TCSANOW,&new);
	struct curl_slist *list=NULL;
	CURL *easyhandle; //Handle for curl library
	/******* CURL ENVIRONMENT INTILIZATION ********/
	curl_global_init(CURL_GLOBAL_ALL);
	easyhandle=curl_easy_init();//Initializing easyhandle to libcurl
	curl_easy_setopt(easyhandle,CURLOPT_URL,"https://things.ubidots.com/api/v1.6/devices/agro/temperature/values?token=0kxvUGcSMMsvfglva6wzFAXMQYemEW");// URL setting
	list=curl_slist_append(list,"content-type: application/x-www-form-urlencoded");
	curl_easy_setopt(easyhandle, CURLOPT_HTTPHEADER, list);//Making header format as above
	curl_easy_setopt(easyhandle, CURLOPT_SSL_VERIFYPEER,0); 
	while(1)
	{
		curl_easy_setopt(easyhandle,CURLOPT_CUSTOMREQUEST,"GET");
		curl_easy_setopt(easyhandle,CURLOPT_WRITEFUNCTION,write_callback);
		curl_easy_perform(easyhandle);//Performing all attributes
	}
} 
