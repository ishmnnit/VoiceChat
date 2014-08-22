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
#include<fstream>
using namespace std;
int sock, connected, bytes_recieved , true1 = 1;  
char recv_data[1024];  
int main()
{
        ifstream fin;
        char line[80],*ch;
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

    fflush(stdout); 
    char send_data[]="enter file to get::";
   send(connected,send_data,strlen(send_data),0); 

   bytes_recieved=recv(connected,recv_data,1024,0);
   recv_data[bytes_recieved]='\0';

    fin.open(recv_data);
     while(fin)
      { fin.get(line[0]);
        strcat(line,"\0");   
        send(connected,line,strlen(line),0);
      } 
    fin.close( );
    close(connected);
      
close(sock);
return 0;
}		
