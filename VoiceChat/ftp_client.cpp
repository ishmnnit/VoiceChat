#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include<malloc.h>
using namespace std;
int main()

{

        int sock, bytes_recieved;  
        char send_data[1024],recv_data[1024];
        struct hostent *host;
        struct sockaddr_in server_addr;  
	char senddata1[1024];
        host = gethostbyname("172.31.108.225");
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
            perror("Socket");
            exit(1);
        }
        server_addr.sin_family = AF_INET;     
        server_addr.sin_port = htons(21);   
        server_addr.sin_addr = *((struct in_addr *)host->h_addr);
        bzero(&(server_addr.sin_zero),8); 
        if (connect(sock, (struct sockaddr *)&server_addr,
                    sizeof(struct sockaddr)) == -1) 
        {
            perror("Connect");
            exit(1);
        }
        bytes_recieved=recv(sock,recv_data,1024,0);
        recv_data[bytes_recieved]='\0';
	cout<<recv_data;
	char s1[32];
	cout<<"\nEnter User Name::";
	cin>>s1;
	strcpy(send_data,"USER ");
	strcat(send_data,s1);
	char s2[30];
	strcpy(s2,"\r\n");
	strcat(send_data,s2);
	send(sock,send_data,strlen(send_data),0);
        bytes_recieved=recv(sock,recv_data,1024,0);
        recv_data[bytes_recieved]='\0';
        cout<<recv_data;
	if(strcmp(s1,"anonymous"))
	{
	cin>>s1;
	strcpy(send_data,"PASS ");
        strcat(send_data,s1);
	strcat(send_data,s2);
	}
	else
	{
	strcpy(send_data,"PASS\r\n");
	}
	send(sock,send_data,strlen(send_data),0);
	bytes_recieved=recv(sock,recv_data,1024,0);
        recv_data[bytes_recieved]='\0';
        cout<<recv_data;
	do
	{
	cout<<"\n"<<"$";
	cin>>s1;
	if(!strcmp(s1,"pwd"))
	strcpy(send_data,"PWD\r\n");
	else if(!strcmp(s1,"type"))
	strcpy(send_data,"TYPE\r\n");
	else if(!strcmp(s1,"list"))
	{
	strcpy(send_data,"PASV\r\n");
	send(sock,send_data,strlen(send_data),0);
        bytes_recieved=recv(sock,recv_data,1024,0);
        recv_data[bytes_recieved]='\0';
        cout<<recv_data;
	strcpy(send_data,"LIST\r\n");
	}
	else if(!strcmp(s1,"pasv"))
	{
	strcpy(send_data,"PASV\r\n");
	cout<<"Entering into Passive Mode";	
	}
	else if(!strcmp(s1,"cd"))
	{
	cin>>s2;
	strcpy(send_data,"CWD ");
	strcat(send_data,s2);
	strcat(send_data,"\r\n");
	}
	else if(!strcmp(s1,"quit"))
	strcpy(send_data,"QUIT\r\n");	
	send(sock,send_data,strlen(send_data),0);
        bytes_recieved=recv(sock,recv_data,1024,0);
        recv_data[bytes_recieved]='\0';
        cout<<recv_data;
	}while(strcmp(s1,"quit"));
	return 0;
}
