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
    int opt = 0;
    printf("\nEnter `1` for UDP connectio or `2` for TCP connectio: ");
    //scanf("%d\n", &opt);
    printf("\nYou selected: %d\n",opt);
    if (opt == 0) {
        char buffer[100];
        packet *packFull;
        char *message = "Hello Client";
        int sockfd, len;
        struct sockaddr_in servaddr, cliaddr;
        
        printf("\nCreating socket UDP\n");

        if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
            perror("\nsocket creation failed\n");
            exit(0);
        }
        
        memset(&servaddr, 0, sizeof(servaddr));
        memset(&cliaddr, 0, sizeof(cliaddr));
        
        // Create a UDP Socket
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(PORT);
        servaddr.sin_family = AF_INET;
       
        printf("\Bind socket UDP\n");

        // Bind the socket with the server address
        if ( bind(sockfd, (const struct sockaddr *)&servaddr,
                sizeof(servaddr)) < 0 )
        {
            perror("bind failed");
            exit(0);
        }
           
        printf("\Ready to receive socket UDP\n");
        packet *pack = malloc(sizeof(packet) * (4));

        //receive the datagram
        len = sizeof(cliaddr);

        
        for (int i=0; i<5; i++) {
            int n = recvfrom(sockfd, &pack[i], sizeof(packet),
                    0, (struct sockaddr*)&cliaddr,&len); //receive message from server
            printf("receive socket UDP number:%d \n", i);
            printPacket(pack[i]);
            rewindFile(pack[i]);
        }
        //puts(buffer);
        //printPacket(packFull);
        printf("\Receive finish \n");


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
