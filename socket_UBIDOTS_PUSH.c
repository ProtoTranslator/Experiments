#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#include<stdlib.h>

void main()
{
	int temp;
	char get[1024],buff[1024],post[1024];
	int s,status;
	/*Structures to specify and collect details about socket */
	struct addrinfo *res;
	struct addrinfo hints;
	/*			LOGIC				 */
	memset(&hints,0,sizeof(hints));
	printf("\nEnter the temperature:");
	scanf("%d",&temp);
	hints.ai_family=PF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;
	
	getaddrinfo("www.things.ubidots.com","80",&hints,&res);
	s=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
	if(s<0)
	{
		perror("Error in creating socket:");
		exit(-1);
	}
	
	status=connect(s,res->ai_addr,res->ai_addrlen);
	if(status==-1)
	{
		perror("Error in connecting:");
		exit(-1);
	}
	freeaddrinfo(res);
	/*Joining all HTTP request into one string*/
	snprintf(get,1024,"GET https://things.ubidots.com/api/v1.6/devices/agro/temperature/values?token=0kxvUGcSMMsvfglva6wzFAXMQYemEW\r\n""Host: things.ubidots.com\r\n");
	
	snprintf(post,1024,"POST https://things.ubidots.com/api/v1.6/devices/agro/temperature/values?token=0kxvUGcSMMsvfglva6wzFAXMQYemEW\r\n""Host:things.ubidots.com\r\n""Content-Type:application/json\r\n""Content-Length:76\r\n""\r\n""{\"value\":%d}\r\n",temp);	
	status=send(s,post,sizeof(post),MSG_CONFIRM);
	if(status==-1)
	{
		perror("\nError in sending GET:");
		exit(-1);
	}
	recv(s,buff,1024,0);
	printf("GET:%s",buff);
	memset(buff,0,1024);	
	status=send(s,get,sizeof(get),MSG_CONFIRM);
	
	if(status==-1)
	{
		perror("\nError in sending POST:");
		exit(-1);
	}
	recv(s,buff,1024,0);
	printf("POST:%s",buff);		
}
