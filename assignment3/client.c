#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#define size 1024

void sendfile(FILE *fp, int sockfd){
	int n;
	char data[size]={0};
	while(fgets(data, size, fp)!=NULL){
		if(send(sockfd, data, sizeof(data), 0)==-1){
			perror("[-]Error in sending file.");
			exit(1);
		}
		bzero(data, size);
	}
}
int main(){
	char *ip="127.0.0.1";
	int port=8080;
	int e;

	int sockfd;
	struct sockaddr_in server_addr;
	FILE *fp;
	char *filename="send.txt";
	
	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0){
		perror("[-]Error in socket.");
		exit(1);
	}
	printf("[+]Server Socket created successfully.");
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=port;
	server_addr.sin_addr.s_addr=inet_addr(ip);
	
	e=connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(e==-1){
		perror("[-]Error in Socket.");
		exit(1);
	}
		printf("[+]Connect to Server.\n");
	
	fp=fopen(filename, "r");
	if(fp==NULL){
		perror("[-]Error in reading file.");
		exit(1);
	}		
	sendfile(fp, sockfd);
	printf("[+]File data sent successfully.\n");
		printf("[+]Closing the connection.");
	close(sockfd);
	return 0;
}
