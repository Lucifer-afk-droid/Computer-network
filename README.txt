Assignment - 1 
• Write a simple socket program in c to echo the message from client to server and back to client. 
1 TCP
Description of Steps to be taken- The entire process can be broken down into following steps:
TCP Server – 
1.	using create(), Create TCP socket.
2.	using bind(), Bind the socket to server address.
3.	using listen(), put the server socket in a passive mode, where it waits for the client to approach the server to make a connection
4.	using accept(), At this point, connection is established between client and server, and they are ready to transfer data.
5.	Take the data from socket of client connection and then store it in the buffer.
6.	Echo the message to the server console.
7.	Close the connection.
TCP Client – 
1.	Create TCP socket.
2.	connect newly created client socket to server.
3.	Store the message from stdin to buffer.
4.	Write the buffer message to the server socket.
5.	Close the connection.

Code –
TCP SERVER CODE 
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// Function designed for chat between client and server.
void func(int sockfd)
{
	char buff[MAX];
	// read the message from client and copy it in buffer
	read(sockfd, buff, sizeof(buff));
	//print the message from client buffer to the console
	printf("From client: %s ", buff);
}

// Driver function
int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign Protocol, IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);

	// Accept the data packet from client and verification
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("server accept failed...\n");
		exit(0);
	}
	else
		printf("server accept the client...\n");

	// Function for chatting between client and server
	func(connfd);

	// After chatting close the socket
	close(sockfd);
}

TCP CLIENT CODE-
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr
void func(int sockfd)
{
    char buff[MAX];
    int n;
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
		gets(buff);
        write(sockfd, buff, sizeof(buff));    
}
   
int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
   
    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
   
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
   
    // function for chat
    func(sockfd);
   
    // close the socket
    close(sockfd);
}
Output-
 
2 UDP
Description-
UDP Server :
1.	Create UDP socket.
2.	Bind the socket to server address.
3.	Wait until datagram packet arrives from client.
4.	Process the datagram packet and send a reply to client.
UDP Client :
1.	Create UDP socket.
2.	Send message to server.
3.	Wait until response from server is received.
4.	Process reply.
5.	Close socket descriptor and exit.
UDP Server Code-
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#define MAXLINE 1024
//Driver code
int main(int argc,char **argv)
{
int sockfd;
int n;
socklen_t len;
//message buffer
char msg[1024];
//defining server and client address
struct sockaddr_in servaddr,cliaddr;
//creation of server socket
sockfd=socket(AF_INET,SOCK_DGRAM,0);
bzero(&servaddr,sizeof(servaddr));
//setting server protocol, address, port
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=INADDR_ANY;
servaddr.sin_port=htons(5035);
printf("\n\n Binded");
//binding the socket to the port
bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
//listening to the client
printf("\n\n Listening...");
for(;;)
{
      printf("\n ");
     len=sizeof(cliaddr);
//receiving the message from the client and storing it in msg variable
     n=recvfrom(sockfd,msg,MAXLINE,0,(struct sockaddr*)&cliaddr,&len);
//printing the client message to the console
     printf("\n Client's Message : %s\n",msg);
     if(n<6)
        perror("send error");
//send reply to client
     sendto(sockfd,msg,n,0,(struct sockaddr*)&cliaddr,len);
}
return 0;
}

UDP Client Code – 
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdio.h>
#define MAXLINE 1024
int main(int argc,char* argv[])
{
int sockfd;
int n;
socklen_t len;
char sendline[1024], recvline[1024];
struct sockaddr_in servaddr;
strcpy(sendline,"");
printf("\n Enter the message : ");
gets(sendline);
//creating the socket
sockfd=socket(AF_INET,SOCK_DGRAM,0);
bzero(&servaddr,sizeof(servaddr));
//setting the server protocol, address, port
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_port=htons(5035);
//connecting to the server socket
connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
len=sizeof(servaddr);
//sending the data to server
sendto(sockfd,sendline,MAXLINE,0,(struct sockaddr*)&servaddr,len);
n=recvfrom(sockfd,recvline,MAXLINE,0,NULL,NULL);
recvline[n]=0;
printf("\n Server's Echo : %s\n\n",recvline);
return 0;
}

Output of Client Server Echo through UDP – 

 

Assignment - 2 
• Write a simple socket program in c to create a chat between client and server. 
1.	TCP
Description-
To write a program to implement a chat between the client and the server.
Algorithm chat application client and server:
Server-Side Chat application algorithm:
STEP 1: Start the program.
STEP 2: Declare the variables and structure for the socket.
STEP 3: Create a socket using socket functions
STEP 4: The socket is binded at the specified port.
STEP 5: Using the object the port and address are declared.
STEP 6: If the binding is successful write the message to the client.
STEP 7: Close the socket if the client sends a goodbye message.How Implementation Of Chat    between Client And Server
STEP 8: Execute the client program.
Client-Side Chat application Algorithm
STEP 1: Start the program.
STEP 2: Declare the variables and structure.
STEP 3: Socket is created and connects function is executed.
STEP 4: If the connection is successful then server sends the message.
STEP 5: The message from the server is responded by the client.
STEP 6: Stop the program

Server Side Code-
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// Function designed for chat between client and server.
void func(int sockfd)
{
	char buff[MAX];
	int n;
	// infinite loop for chatting
	for (;;) {
		bzero(buff, MAX);

		// read and store message of client in buffer
		read(sockfd, buff, sizeof(buff));
		// printing client message from buffer
		printf("From client: %sTo client : ", buff);
		bzero(buff, MAX);
		n = 0;
		// copy server message in the buffer
		while ((buff[n++] = getchar()) != '\n')
			;

		// and send that buffer to client
		write(sockfd, buff, sizeof(buff));

		// if msg contains "exit" then server exit and chat ended.
		if (strncmp("exit", buff, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}
	}
}
// Main Driver function
int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	// socket creation
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//checking if socket created successfully
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// setting server's protocol, ip and port no.
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);

	// Accept the data packet from client and verification
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("server accept failed...\n");
		exit(0);
	}
	else
		printf("server accept the client...\n");

	// Function for chatting between client and server
	func(connfd);

	// After chatting close the socket
	close(sockfd);
}
Client Side Code-
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include<arpa/inet.h>
	
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
void func(int sockfd)
{
	char buff[MAX];
	int n;
	for (;;) {
		bzero(buff, sizeof(buff));
		printf("Enter the string : ");
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;
		write(sockfd, buff, sizeof(buff));
		bzero(buff, sizeof(buff));
		read(sockfd, buff, sizeof(buff));
		printf("From Server : %s", buff);
		if ((strncmp(buff, "exit", 4)) == 0) {
			printf("Client Exit...\n");
			break;
		}
	}
}
int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// socket create and varification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	// function for chat
	func(sockfd);

	// close the socket
	close(sockfd);
}
Output-
 

2.	UDP
Description of Server Side-
Include the header file <sys/socket.h> and arpa/inet.h:
#include <sys/socket.h>
#include <arpa/inet.h>
Create a socket that returns a socket descriptor. This is used to refer to the socket later on in the code:
int socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
The server-side code keeps the address information of both the server and the client in the variable server_addr (a struct of type sockaddr_in). Initialize the server address by the port and IP:
struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(2000);
server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
Bind socket descriptor to the server address:
bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr);
Unlike TCP, the server-side does not wait for a client to connect and, therefore, does not receive the client’s address prior to sending and receiving data. Instead, the server receives information about the client when it receives data using the recvfrom() method:
int client_struct_length = sizeof(client_addr);

recvfrom(socket_desc, client_message, sizeof(client_message), 0,
           (struct sockaddr*)&client_addr, &client_struct_length);
The client’s information, stored in the variable client_addr of type sockaddr_in, is then used to send data to the same client:
sendto(socket_desc, server_message, strlen(server_message), 0,
         (struct sockaddr*)&client_addr, client_struct_length);
Close the socket to end the communication:
close(socket_desc);
Description of Client Side-
Include header files, create a socket, and initialize the server’s address information in a variable of type sockaddr_in (similarly to how it was done at the server-side):
#include <sys/socket.h>
#include <arpa/inet.h>

int socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(2000);
server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
Unlike TCP, when the client sends and receives data using sendto() and recvfrom(), the server’s information has to be given every time:
sendto(socket_desc, client_message, strlen(client_message), 0,
         (struct sockaddr*)&server_addr, server_struct_length);

recvfrom(socket_desc, server_message, sizeof(server_message), 0,
         (struct sockaddr*)&server_addr, &server_struct_length);
A deadlock will occur if both the client and the server are waiting for each other’s message at recvfrom().
Server Side UDP Code-
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(void){
    int socket_desc;
    struct sockaddr_in server_addr, client_addr;
    char server_message[2000], client_message[2000];
    int client_struct_length = sizeof(client_addr);
    
    // Clean buffers:
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));
    
    // Create UDP socket:
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    if(socket_desc < 0){
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");
    
    // Set port and IP:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    // Bind to the set port and IP:
    if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("Couldn't bind to the port\n");
        return -1;
    }
    printf("Done with binding\n");
    
    printf("Listening for incoming messages...\n\n");
    while(1){
		memset(&server_message, 0, sizeof(server_message));
		memset(&client_message, 0, sizeof(client_message));
		// Receive client's message:
		if (recvfrom(socket_desc, client_message, sizeof(client_message), 0,
			 (struct sockaddr*)&client_addr, &client_struct_length) < 0){
			printf("Couldn't receive\n");
			return -1;
		}
		printf("Received message from IP: %s and port: %i\n",
			   inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		
		printf("Msg from client: %s\n", client_message);
		
		// Respond to client:
		strcpy(server_message, client_message);
		
		printf("Message to client-");
		gets(client_message);
		if (sendto(socket_desc, client_message, strlen(client_message), 0,
			 (struct sockaddr*)&client_addr, client_struct_length) < 0){
			printf("Can't send\n");
			return -1;
		}
		if(strncmp(server_message, "bye", 3)==0 || strncmp(client_message, "bye", 3)==0){
			break;
		}
	}
    
    
    // Close the socket:
    close(socket_desc);
    
    return 0;
}
Client Side UDP Code-
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>

int main(void){
    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[2000], client_message[2000];
    int server_struct_length = sizeof(server_addr);
    
    // Clean buffers:
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));
    
    // Create socket:
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    if(socket_desc < 0){
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");
    
    // Set port and IP:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
	while(1){
		memset(&server_message, 0, sizeof(server_message));
		memset(&client_message, 0, sizeof(client_message));
		// Get input from the user:
		printf("Enter message: ");
		gets(client_message);
		
		// Send the message to server:
		if(sendto(socket_desc, client_message, strlen(client_message), 0,
			 (struct sockaddr*)&server_addr, server_struct_length) < 0){
			printf("Unable to send message\n");
			return -1;
		}
		
		// Receive the server's response:
		if(recvfrom(socket_desc, server_message, sizeof(server_message), 0,
			 (struct sockaddr*)&server_addr, &server_struct_length) < 0){
			printf("Error while receiving server's msg\n");
			return -1;
		}
    
		printf("Server's response: %s\n", server_message);
		if(strncmp(server_message, "bye", 3)==0 || strncmp(client_message, "bye", 3)==0){
			break;
		}
	}
    
    
    // Close the socket:
    close(socket_desc);
    
    return 0;
}

Output-
 






Assignment-3
Q-Write a simple socket program in c to transfer a file from client to server.
•TCP
Description
Client
The client performs the following functions.
1.	Start the program
2.	Declare the variables and structures required.
3.	A socket is created and the connect function is executed.
4.	The file is opened.
5.	The data from the file is read and sent to the server.
6.	The socket is closed.
7.	The program is stopped.
Server
The client performs the following functions.
1.	Start the program.
2.	Declare the variables and structures required.
3.	The socket is created using the socket function.
4.	The socket is binded to the specific port.
5.	Start listening for the connections.
6.	Accept the connection from the client.
7.	Create a new file.
8.	Receives the data from the client.
9.	Write the data into the file.
10.	The program is stopped.
Client Side Code-
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
Server Side Code-
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#define size 1024

void write_file(int sockfd){
	int n;
	FILE *fp;
	char *filename="recv.txt";
	char buffer[size];
	
	fp=fopen(filename, "w");
	while(1){
		n=recv(sockfd, buffer, size, 0);
		if(n<=0){
			break;
			return;
		}
		fprintf(fp, "%s", buffer);
		bzero(buffer, size);
	}
	return;
}
int main(){
	char *ip="127.0.0.1";
	int port=8080;
	int e;
	
	int sockfd, new_sock;
	struct sockaddr_in server_addr, new_addr;
	socklen_t addr_size;
	char buffer[size];
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0){
		perror("[-]Error in socket.");
		exit(1);
	}
	printf("[+]Server Socket created successfully.\n");
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=port;
	server_addr.sin_addr.s_addr=inet_addr(ip);
	e=bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(e<0){
		perror("[-]Error in bind");
		exit(1);
	}
	printf("[+]Binding successfull.\n");
	if(listen(sockfd, 10)==0){
		printf("[+]Listening..\n");
	}else{
		perror("[-]Error in listening");
		exit(1);
	}
	addr_size=sizeof(new_addr);
	new_sock=accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
	write_file(new_sock);
	printf("[+]Data written in the file successfully.\n");
	return 0;
}
Output-
 
 

•UDP
Description
1.	The server starts and waits for filename.
2.	Client read the given file name, “send.txt”.
3.	The client sends a file data.
4.	The server receives file data.
5.	Server writes the data to a new file named “receive.txt” and save it.
Server Code –
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SIZE 1024

void write_file(int sockfd, struct sockaddr_in addr){
  FILE *fp;
  char *filename = "receive.txt";
  int n;
  char buffer[SIZE];
  socklen_t addr_size;
  // Creating a file.
  fp = fopen(filename, "w");
  // Receiving the data and writing it into the file.
  while(1){
    addr_size = sizeof(addr);
    n = recvfrom(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, &addr_size);
    if (strcmp(buffer, "END") == 0){
      break;
      return;
    }
    printf("[RECEVING] Data: %s", buffer);
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }
  fclose(fp);
  return;
}

int main(){
  // Defining the IP and Port
  char *ip = "127.0.0.1";
  int port = 8080;
  // Defining variables
  int server_sockfd;
  struct sockaddr_in server_addr, client_addr;
  char buffer[SIZE];
  int e;

  // Creating a UDP socket
  server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_sockfd < 0){
    perror("[ERROR] socket error");
    exit(1);
  }
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = bind(server_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (e < 0){
    perror("[ERROR] bind error");
    exit(1);
  }

  printf("[STARTING] UDP File Server started. \n");
  write_file(server_sockfd, client_addr);

  printf("[SUCCESS] Data transfer complete.\n");
  printf("[CLOSING] Closing the server.\n");

  close(server_sockfd);

  return 0;
}
Client Code-
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SIZE 1024

void send_file_data(FILE *fp, int sockfd, struct sockaddr_in addr){
  int n;
  char buffer[SIZE];
  // Sending the data
  while(fgets(buffer, SIZE, fp) != NULL){
    printf("[SENDING] Data: %s", buffer);
    n = sendto(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, sizeof(addr));
    if (n == -1){
      perror("[ERROR] sending data to the server.");
      exit(1);
    }
    bzero(buffer, SIZE);
  }
  // Sending the 'END'
  strcpy(buffer, "END");
  sendto(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, sizeof(addr));
  fclose(fp);
  return;
}

int main(){
  // Defining the IP and Port
  char *ip = "127.0.0.1";
  int port = 8080;
  // Defining variables
  int server_sockfd;
  struct sockaddr_in server_addr;
  FILE *fp;
  char *filename = "send.txt";
  // Creating a UDP socket
  server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_sockfd < 0){
    perror("[ERROR] socket error");
    exit(1);
  }
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);
  // Reading the text file
  fp = fopen(filename, "r");
  if (fp == NULL){
    perror("[ERROR] reading the file");
    exit(1);
  }
  // Sending the file data to the server
  send_file_data(fp, server_sockfd, server_addr);
  printf("[SUCCESS] Data transfer complete.\n");
  printf("[CLOSING] Disconnecting from the server.\n");
  close(server_sockfd);
  return 0;
}
Output-
 

 




Assignment 4
Q- Write a simple socket program in c to handle multiple clients using fork.
•TCP
Description
A simple tcp client server application that describes the communication between the client and a server. The server is a simple echo sever that can handle multiple client using fork.
An echo server is a server that send back the same message that the client has send the server. Like:
Client send - abc
Server recv – abc

Server Code-
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define size 1024
#define port 8080
int main(){
	int sockfd, newsockfd, ret;
	struct sockaddr_in serverAddr;
	int newSocket;
	struct sockaddr_in newAddr;
	socklen_t addr_size;
	char buffer[size];
	pid_t childpid;
	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Server Socket is created.\n");
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons(port);
	serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	ret=bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	if(ret<0){
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", 8080);
	if(listen(sockfd, 10)==0){
		printf("[+]Listening...\n");
	}else{
		printf("[-]Error in binding.\n");
	}
	while(1){
		newSocket = accept(sockfd, (struct sockaddr *)&newAddr, &addr_size);
		if(newSocket<0){
			exit(1);
		}
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
		if((childpid=fork())==0){
			//close(sockfd);
			while(1){
			recv(newSocket, buffer, 1024, 0);
			if(strcmp(buffer,"exit")==0){
				printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
				break;
			}else{
				printf("Client: %s\n", buffer);
				send(newSocket, buffer, strlen(buffer),0);
				bzero(buffer, sizeof(buffer));
				int rv=recv(newsockfd, buffer, 1024, 0);
				buffer[rv]='\0';
				printf("%s", buffer);
			}
		}			
	}
}
close(newSocket);
return 0;
}

Client Code-
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define SIZE 1024
#define PORT 8080

int main(){
	int clientSocket , ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	clientSocket = socket(AF_INET,SOCK_STREAM,0);

	if(clientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");
	memset(&serverAddr , '\0',sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ret = connect(clientSocket,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");
	while(1){
		printf("Client:\t");
		scanf("%s",&buffer);
		send(clientSocket, buffer,strlen(buffer),0);
		if(strcmp(buffer,":exit")==0){
			close(clientSocket);
			printf("[-]Disconnected from server.\n");
			exit(1);
		}
		if(recv(clientSocket, buffer,1024,0) < 0){
			printf("[-]Error in receiving data.\n");
		}else{
			printf("Server:\t%s\n",buffer);
		}
	}
	return 0;
}

Output-

 


Assignment 5:  
1) Write a Reverse DNS lookup(IP Address to Hostname)program in C.
Description:
A dns query lets you to lookup the various dns records for a given hostname or domain name on the internet. The simplest use case is to lookup the ip address of a domain name.
When you open a url in your browser, it first performs a dns query to find out the ip address of the request url domain. Its the dns servers that respond with the correct answer which the browser then uses to connect.
Code-
#include <stdio.h> //for printf()
#include <stdlib.h> //for exit()
#include <arpa/inet.h> //for inet_pton()
#include <netdb.h> // for NI_MAXHOST, getnameinfo() and gai_strerror()
#include <errno.h> // for errno
#include <string.h> // for strerror()

//taking the ip using the command line arguments
int main(int argc, char** argv) {
  if(argc<2) {
    printf("\n%s [IP]\n",argv[0]);
    printf("For e.g. %s 10.32.129.77\n",argv[0]);
    exit(-1);
  }
//creation of the socket
  struct sockaddr_in sa;
  int res = inet_pton(AF_INET, argv[1] , &sa.sin_addr);
  switch(res) {
//input case for entering ip
    case 0: printf("\nInput address is not a valid IPv4 address.\n");
    case -1: if(res == -1)
               printf("\nError(%s)\n",strerror(errno));
             int n_res = inet_pton(AF_INET6, argv[1] , &sa.sin_addr);
             switch(n_res) {
               case 0: printf("\nInput address is not a valid IPv6 address.\n");
               case -1: if(n_res == -1)
                          printf("\nError(%s)\n",strerror(errno));
                        exit(-1);
               case 1: sa.sin_family = AF_INET6;
             }
    case 1: sa.sin_family = AF_INET;
  }
  printf("\nsa.sin_addr.s_addr[%d]\n",sa.sin_addr.s_addr);
  char node[NI_MAXHOST];
  memset(node,0,NI_MAXHOST);
  res = getnameinfo((struct sockaddr*)&sa, sizeof(sa), node, sizeof(node), NULL, 0, 0);
  if (res) {
    printf("%s\n", gai_strerror(res));
    exit(1);
  }
//printing ip // example: ./filename 157.240.1.35 (run along with IP address)
  printf("\nIP[%s]\n",argv[1]);
//printing hostname
  printf("HOSTNAME[%s]\n", node);
  return 0;
}	
Output-
 
2) Write a DNS program in C to determine IP address from a given host name.
Description-
DNS is a client/server network communication protocol. DNS clients send requests to the. server while DNS servers send responses to the client.
Client requests contain a name which is converted into an IP address known as a forward DNS lookups while requests containing an IP address which is converted into a name known as reverse DNS lookups.
DNS implements a distributed database to store the name of all the hosts available on the internet.
If a client like a web browser sends a request containing a hostname, then a piece of software such as DNS resolver sends a request to the DNS server to obtain the IP address of a hostname. If DNS server does not contain the IP address associated with a hostname, then it forwards the request to another DNS server. If IP address has arrived at the resolver, which in turn completes the request over the internet protocol.
Code-
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
	//host name stored in host variable
	gets(host);
	//getting structure of host-name of type hostent
	he = gethostbyname(host);
	if(he == NULL){
		printf("The address cannot be resolved at this time");
		exit(1);
	}
	printf("Official name is: %s\n", he->h_name);
	printf("IP address: %s\n", inet_ntoa(*(struct in_addr*)he->h_addr));
	return 0;
}

Output-
 

Assignment 6
Q-Write a simple socket programming in C to provide current time and Date to the client.
•TCP
Description-
At Server Side-
1.	The call to the function ‘socket()’ creates an UN-named socket inside the kernel and returns an integer known as socket descriptor.
2.	This function takes domain/family as its first argument. For Internet family of IPv4 addresses we use AF_INET.
3.	The second argument ‘SOCK_STREAM’ specifies that the transport layer protocol that we want should be reliable ie it should have acknowledgement techniques. For example : TCP
4.	The third argument is generally left zero to let the kernel decide the default protocol to use for this connection. For connection oriented reliable connections, the default protocol used is TCP.
5.	The call to the function ‘bind()’ assigns the details specified in the structure ‘serv_addr’ to the socket created in the step above. The details include, the family/domain, the interface to listen on(in case the system has multiple interfaces to network) and the port on which the server will wait for the client requests to come.
6.	The call to the function ‘listen()’ with second argument as ’10’ specifies maximum number of client connections that server will queue for this listening socket.
7.	After the call to listen(), this socket becomes a fully functional listening socket.
8.	In the call to accept(), the server is put to sleep and when for an incoming client request, the three way TCP handshake* is complete, the function accept () wakes up and returns the socket descriptor representing the client socket.
9.	The call to accept() is run in an infinite loop so that the server is always running and the delay or sleep of 1 sec ensures that this server does not eat up all of your CPU processing.
10.	As soon as server gets a request from client, it prepares the date and time and writes on the client socket through the descriptor returned by accept().
At Client Side-
1.	A socket is created through call to socket() function.
2.	Information like IP address of the remote host and its port is bundled up in a structure and a call to function connect() is made which tries to connect this socket with the socket (IP address and port) of the remote host.
3.	Note that here we have not bind our client socket on a particular port as client generally use port assigned by kernel as client can have its socket associated with any port but In case of server it has to be a well known socket, so known servers bind to a specific port like HTTP server runs on port 80 etc while there is no such restrictions on clients.
4.	Once the sockets are connected, the server sends the data (date+time) on clients socket through clients socket descriptor and client can read it through normal read call on the its socket descriptor.
Server Code-
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<time.h>
#define backlog 10

int main(int argc, char **argv){
	if(argc!=2){
		printf("Usage: %s <port>\n", argv[0]);
		exit(0);
	}
	int port = atoi(argv[1]);
	printf("Post: %d\n", port);
	int n_client = 0;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(port);
	bind(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	printf("[+]Bind\n");
	listen(sockfd, backlog);
	printf("[+]Listening for the client\n");
	int i=1;
	while(i){
		int client_socket = accept(sockfd, NULL, NULL);
		n_client++;
		time_t currentTime;
		time(&currentTime);
		printf("Client %d requested for time at %s", n_client, ctime(&currentTime));
		send(client_socket, ctime(&currentTime), 30, 0);
	}
	return 0;
}
Client Code-
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<time.h>

int main(int argc, char **argv){
	if(argc!=2){
		printf("Usage: %s <port>\n", argv[0]);
		exit(0);
	}
	int port = atoi(argv[1]);
	printf("Port: %d\n", port);
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	char response[30];
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(port);
	connect(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	printf("[+]Connected to the server\n");
	recv(sockfd, response, 29, 0);
	printf("Time from server: %s", response);
	return 0;
}
Output-

 

•UDP
Description-
UDP stands for User Datagram Protocol. The client sends a datagram to the server, which then processes the information and returns a response.
The server program is a simple UDP server that waits for the datagram from clients. When it receives a datagram , it returns the current server's time to the client.
The client program is a simple UDP client that sends a request to the server to get the current time and receives the time back. First, the Windows connection is opened. Then a socket is opened. Next the address of the server is copied into the server struct.
Server Code-
#include <sys/socket.h>//for making the socket
#include <netinet/in.h>
#include <arpa/inet.h>//for inet_addr
#include <netdb.h>
#include <string.h>//for using strlen and manipulating char array
#include <stdlib.h>
#include <unistd.h>// for write, exit , close.
#include <stdio.h>// for standard input and output
#include <time.h>

#define S_PORT 43454
#define C_PORT 43455
#define ERROR -1
#define IP_STR "127.0.0.1"

int main(int argc, char const *argv[]) {
	int sfd, num;
	time_t current_time;
	struct sockaddr_in servaddr, clientaddr;
	//Create the socket by UDP protocol
	sfd = socket(AF_INET, SOCK_DGRAM,IPPROTO_UDP);
	if (sfd == ERROR) {
		perror("Could not open a socket");
		return 1;
	}
	memset((char *) &servaddr, 0, sizeof(servaddr));
	// Set port and IP:
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(S_PORT);
	memset((char *) &clientaddr, 0, sizeof(clientaddr));
	clientaddr.sin_family=AF_INET;
	clientaddr.sin_addr.s_addr=inet_addr(IP_STR);
	clientaddr.sin_port=htons(C_PORT);
	//Binding the socket
	if((bind(sfd,(struct sockaddr *)&servaddr,sizeof(servaddr)))!=0) {
		perror("Could not bind socket");
		return 2;
	}

	printf("Server is running on %s:%d\n", IP_STR, S_PORT);
	while(1) {
		recvfrom(sfd, &num, sizeof(num), 0, (struct sockaddr *)&clientaddr, (socklen_t *)&clientaddr);
		current_time = time(NULL);
		printf("Client at %s:%d asked for time: %s\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), ctime(&current_time));
		sendto(sfd, &current_time, sizeof(current_time), 0, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
	}
	return 0;
}
Client Code-
#include <sys/socket.h>//for making the socket
#include <netdb.h>
#include <string.h>//for using strlen and manipulating char array
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>//for inet_addr
#include <stdio.h>// for standard input and output
#include <string.h>
#include <time.h>

#define S_PORT 43454
#define C_PORT 43455
#define ERROR -1
#define IP_STR "127.0.0.1"

int main(int argc, char const *argv[]) {
	int sfd;
	int num = 1;
	time_t start_time, rtt, current_time;
	struct sockaddr_in servaddr, clientaddr;
	socklen_t addrlen;
	//Create the socket by UDP protocol
	sfd = socket(AF_INET, SOCK_DGRAM,IPPROTO_UDP);
	if (sfd == ERROR) {
		perror("Could not open a socket");
		return 1; }
	memset((char *) &servaddr, 0, sizeof(servaddr));
	// Set port and IP:
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(IP_STR);
	servaddr.sin_port=htons(S_PORT);
	memset((char *) &clientaddr, 0, sizeof(clientaddr));
	clientaddr.sin_family=AF_INET;
	clientaddr.sin_addr.s_addr=inet_addr(IP_STR);
	clientaddr.sin_port=htons(C_PORT);
	//Binding the socket
	if((bind(sfd,(struct sockaddr *)&clientaddr,sizeof(clientaddr)))!=0) {
		perror("Could not bind socket");
		return 2;
	}
	printf("Client is running on %s:%d\n", IP_STR, C_PORT);
	start_time = time(NULL);
	sendto(sfd, &num, sizeof(num), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
	addrlen = sizeof(clientaddr);
	recvfrom(sfd, &current_time, sizeof(current_time), 0, (struct sockaddr *)&clientaddr, &addrlen);
	rtt = time(NULL) - start_time;
	current_time += rtt / 2;
	printf("Server's Time: %s\n", ctime(&current_time));

	return 0; }
Output-
 
