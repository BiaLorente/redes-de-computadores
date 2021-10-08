// server program for udp connection
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>

//#include "packetFunc.c"
#include "structs.h"


#define PORT 8080
#define MAXLINE 1000
#define SA struct sockaddr
#define MAX 80


// Function designed for chat between client and server.
void func(int sockfd)
{
    packet *pack = malloc(sizeof(packet) * (4));
    //pack->frame.buffer= malloc(sizeof(char) * (4));
    //printf("Sizeof pack[i]->frame.buffer: %lu\n ", sizeof(pack->frame.buffer));

    char buff[MAX];
    //buff = 'Hey\n';
    strcpy(buff, "Server received");
    //int i;
    puts(buff);
    // infinite loop for chat
    for (int i=0; i<5; i++) {
        bzero(buff, MAX);
   
        // read the message from client and copy it in buffer
        read(sockfd, &pack[i], sizeof(packet));
        
        //printf("o seq number: %d\n", pack[i].frame.seqNum);
        //printf("Sizeof pack[i].frame.buffer: %lu\n ", sizeof(pack[i].frame.buffer));
        //printf("Data\n");
        //puts(pack[i].frame.buffer);

        // print buffer which contains the client contents
        //printf("From client: %s\t To client : ", buff);
        printPacket(pack[i]);
        rewindFile(pack[i]);

        //printf("pass the printPacket\n");
        bzero(buff, MAX);
        //i = 0;
        // copy server message in the buffer
        //while ((buff[i++] = getchar()) != '\n')
            ;
   
        // and send that buffer to client
        //write(sockfd, buff, sizeof(buff));
   
        // if msg contains "Exit" then server exit and chat ended.
        //if (strncmp("exit", buff, 4) == 0) {
          //  printf("Server Exit...\n");
            //break;
        //}
    }
}

// Driver code
int main()
{
    char opt;
    printf("Enter `u` for UDP connectio or `t` for TCP connectio\n: ");
    opt = getchar();
    if (opt == 'u') {
        char buffer[100];
        packet *packFull;
        char *message = "Hello Client";
        int listenfd, len;
        struct sockaddr_in servaddr, cliaddr;
        bzero(&servaddr, sizeof(servaddr));
      
        // Create a UDP Socket
        listenfd = socket(AF_INET, SOCK_DGRAM, 0);
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(PORT);
        servaddr.sin_family = AF_INET;
       
        // bind server address to socket descriptor
        bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
           
        //receive the datagram
        len = sizeof(cliaddr);
        int n = recvfrom(listenfd, packFull, sizeof(buffer),
                0, (struct sockaddr*)&cliaddr,&len); //receive message from server
        buffer[n] = '\0';
        //puts(buffer);
        //printPacket(packFull);

        // send the response
        sendto(listenfd, message, MAXLINE, 0,
              (struct sockaddr*)&cliaddr, sizeof(cliaddr));
    }
    else{
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
       
        // assign IP, PORT
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
    
}
