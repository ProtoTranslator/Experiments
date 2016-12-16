#include<stdio.h>
#include<string.h>
#include<curl/curl.h>

void main()
{
	int temp;
	char str[10];
	printf("\nEnter a temperature:");
	scanf("%d",&temp);
	sprintf(str, "value=%d",temp);
	CURL *hnd = curl_easy_init();

curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
curl_easy_setopt(hnd, CURLOPT_URL, "http://things.ubidots.com/api/v1.6/devices/agro/temperature/values?token=0kxvUGcSMMsvfglva6wzFAXMQYemEW");

struct curl_slist *headers = NULL;
headers = curl_slist_append(headers, "postman-token: c8d8b1c1-862e-7027-5431-2b4caa6ff769");
headers = curl_slist_append(headers, "cache-control: no-cache");
headers = curl_slist_append(headers, "content-type: application/x-www-form-urlencoded");
curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, str);

CURLcode ret = curl_easy_perform(hnd);
}
