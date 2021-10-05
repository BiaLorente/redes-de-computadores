// udp client driver program
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>


  
#define PORT 8080
#define MAXLINE 1000
#define MAX 80
#define SA struct sockaddr

void func(int sockfd, packet *pack)
{
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        //printf("Enter the string : ");
        n = 0;
        //while ((buff[n++] = getchar()) != '\n')
          //  ;
        printf("going to write\n");
        printPacket(pack);
        write(sockfd, pack, sizeof(pack));
        printf("passed the write\n");
        bzero(buff, sizeof(buff));
        //read(sockfd, buff, sizeof(buff));
        //printf("From Server : %s", buff);
        //if ((strncmp(buff, "exit", 4)) == 0) {
          //  printf("Client Exit...\n");
            //break;
        //}
    }
}
  
// Driver code
void sendPacket(packet *pack)
{
    
    char opt;
    printf("Enter `u` for UDP connectio or `t` for TCP connectio\n: ");
    opt = getchar();
    if (opt == 'u')
    {
        char buffer[100];
        char *message = "Hello Server";
        int sockfd, n;
        struct sockaddr_in servaddr;
      
        // clear servaddr
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        servaddr.sin_port = htons(PORT);
        servaddr.sin_family = AF_INET;
      
        // create datagram socket
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
      
        // connect to server
        if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        {
            printf("\n Error : Connect Failed \n");
            exit(0);
        }
  
        // request to send datagram
        // no need to specify server address in sendto
        // connect stores the peers IP and port
        sendto(sockfd, pack, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr));
      
        // waiting for response
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL);
        puts(buffer);
  
        // close the descriptor
        close(sockfd);
    }
    else{
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
        printf("going to the func\n");
        func(sockfd, pack);
       
        // close the socket
        close(sockfd);
    }
    
}
