#include<sys/stat.h>
#include<fstream>
#include<cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
using namespace std;
int sock, connected, bytes_recieved , true1 = 1;  
char  a[100],b[100],op[100];
int c;
int bytea,byteb,byteo;  
int main()
{       
       struct sockaddr_in server_addr,client_addr;    
        int sin_size;
        
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }

        if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&true1,sizeof(int)) == -1) {
            perror("Setsockopt");
            exit(1);
        }
       
        server_addr.sin_family = AF_INET;         
        server_addr.sin_port = htons(5000);     
        server_addr.sin_addr.s_addr = INADDR_ANY; 
        bzero(&(server_addr.sin_zero),8); 

        if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))== -1) 
	{
            perror("Unable to bind");
            exit(1);
        }

        if (listen(sock, 5) == -1) 
	{
            perror("Listen");
            exit(1);
        }
		
	cout<<"\nTCPServer Waiting for client on port 5000";
        fflush(stdout);
	
      	sin_size = sizeof(struct sockaddr_in);
 	connected = accept(sock, (struct sockaddr *)&client_addr,(socklen_t*)&sin_size);
  	cout<<"\n I got a connection from "<<inet_ntoa(client_addr.sin_addr)<<":"<<ntohs(client_addr.sin_port);
        
       
           char send_data[]="enter first number::";
           send(connected,send_data,strlen(send_data),0);
           bytea=recv(connected,a,100,0);
           a[bytea]='\0';
           int a1=atoi(a);
          
           char  send_data1[]="enter second number::";
           send(connected,send_data1,strlen(send_data1),0);
           byteb=recv(connected,b,100,0);
           b[byteb]='\0';
           int a2=atoi(b);
          
           char send_data2[]="enter operation::";
           send(connected,send_data2,strlen(send_data2),0);
           byteo=recv(connected,op,100,0);
           op[byteo]='\0';
           cout<<op[0]; 
         
           switch(op[0])
            {
               case '+':c=a1+a2;
                        break;
               case '-':c=a1-a2;
                        break;
               case '*':c=a1*a2;
                        break;
               case '/':c=a1/a2;
                        break;
               default :break;
            }    
       char ch[10];
       ch[0]=c;ch[1]='\0';
       send(connected,ch,strlen(ch),0);
return 0;
}		
