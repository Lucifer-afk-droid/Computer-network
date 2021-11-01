#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>
#include<sys/types.h>
#include<arpa/inet.h>

int main(){
	int i;
	char host[80];
	struct hostent *he;
	struct in_addr addr;
	
	printf("Enter the host-name:");
	gets(host);
	he = gethostbyname(host);
	if(he == NULL){
		printf("The address cannot be resolved at this time");
		exit(1);
	}
	printf("Official name is: %s\n", he->h_name);
	printf("IP address: %s\n", inet_ntoa(*(struct in_addr*)he->h_addr));
	return 0;
	
}