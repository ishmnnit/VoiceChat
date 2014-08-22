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
        char a[20],b[20];
        char op[10];
        int sock, byte,byte1,byte2,byte3;  
        char send_data[1024],recv_data[1024];
        struct hostent *host;
        struct sockaddr_in server_addr;
        host = gethostbyname("127.0.0.1");

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }

        server_addr.sin_family = AF_INET;     
        server_addr.sin_port = htons(5000);   
        server_addr.sin_addr = *((struct in_addr *)host->h_addr);
        bzero(&(server_addr.sin_zero),8); 

        if (connect(sock, (struct sockaddr *)&server_addr,
                    sizeof(struct sockaddr)) == -1) 
        {
            perror("Connect");
            exit(1);
        }
 
        
 
           byte=recv(sock,recv_data,1024,0);
           recv_data[byte]='\0';
           cout<<endl<<recv_data;
           cin>>a;
           send(sock,a,strlen(a),0);
           
           byte1=recv(sock,recv_data,1024,0);
           recv_data[byte1]='\0';
           cout<<endl<<recv_data;
           cin>>b;
           send(sock,b,strlen(b),0);

           byte2=recv(sock,recv_data,1024,0);
           recv_data[byte2]='\0';
           cout<<endl<<recv_data;
           cin>>op[0];
           send(sock,op,strlen(op),0);

           byte3=recv(sock,recv_data,1024,0);
           recv_data[byte3]='\0';
           int result=recv_data[0];
           cout<<endl<<result;
return 0;
}

