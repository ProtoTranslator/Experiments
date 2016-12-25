/*****************************CURL POST CODE****************************************/
#include<stdio.h>
#include<unistd.h>
#include<curl/curl.h>
#include<string.h>
#include<stdlib.h>
char responseData[3];
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	int i;
	strncpy(responseData,&ptr[87],90);
	i=atoi(responseData);
	printf("\nResponse:%d\n",i);
}
void main()
{	
	int value,option;
	char data[20];
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
	printf("Menu\n1:POST DATA\n2:GET DATA\n3:EXIT\nEnter option (1/2/3):");
	scanf("%d",&option);
	switch(option)
	{
		case 1:printf("Enter the temperature:");
			scanf("%d",&value);
			sprintf(data,"value=%d",value);
			curl_easy_setopt(easyhandle,CURLOPT_CUSTOMREQUEST,"POST");//Command to do 
			curl_easy_setopt(easyhandle, CURLOPT_POSTFIELDS, data);//Sending values
			//curl_easy_setopt(easyhandle,CURLOPT_WRITEFUNCTION,write_callback);
			curl_easy_perform(easyhandle);//Performing all attributes
			break;
		case 2: curl_easy_setopt(easyhandle,CURLOPT_CUSTOMREQUEST,"GET");
			curl_easy_setopt(easyhandle,CURLOPT_WRITEFUNCTION,write_callback);
			curl_easy_perform(easyhandle);//Performing all attributes
			break;
		case 3:	curl_easy_cleanup(easyhandle);// Cleaning up fuction for curl
			exit(-1);
	}}
}	
	
	
