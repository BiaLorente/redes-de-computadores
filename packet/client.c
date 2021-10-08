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

void func(int sockfd, packet *pack, int numFrag)
{
    char buff[MAX];
    int n;
    for (int i=0; i<5; i++) {
        bzero(buff, sizeof(buff));
        //printf("Enter the string : ");
        n = 0;
        //while ((buff[n++] = getchar()) != '\n')
          //  ;
        printPacket(pack[i]);
        write(sockfd, &pack[i], sizeof(packet));

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
void sendPacket(packet *pack, int numFrag)
    {
        
        char opt;
        printf("Enter `u` for UDP connectio or `t` for TCP connectio\n: ");
        
        scanf("%c\n", &opt);
        printf("You selected: %c",opt);
        /*if (opt == 'u')
        {
            printf("You selected UDP");
            char buffer[100];
            char *message = "Hello Server";
            int sockfd, n;
            struct sockaddr_in servaddr;
          
            // create datagram socket
            if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
            {
                perror("socket creation failed");
                exit(0);
            }
            // clear servaddr
            memset(&servaddr, 0, sizeof(servaddr));
            
            servaddr.sin_family = AF_INET;
            servaddr.sin_port = htons(PORT);
            servaddr.sin_addr.s_addr = INADDR_ANY;
          
            // connect to server
            /*if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
            {
                printf("\n Error : Connect Failed \n");
                exit(0);
            }
            
            sendto(sockfd, pack, sizeof(pack),
                0, (const struct sockaddr *) &servaddr,
                    sizeof(servaddr));
      
            // request to send datagram
            // no need to specify server address in sendto
            // connect stores the peers IP and port
            //sendto(sockfd, pack, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr));
          
            // waiting for response
            //recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL);
            //puts(buffer);
      
            // close the descriptor
            close(sockfd);
        }
        else
        {*/
            //if (opt=='t')
            //{
                int sockfd, connfd;
                struct sockaddr_in servaddr, cli;
               
                // socket create and varification
                sockfd = socket(AF_INET, SOCK_STREAM, 0);
                if (sockfd == -1)
                {
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
                if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0)
                {
                    printf("connection with the server failed...\n");
                    exit(0);
                }
                else
                    printf("connected to the server..\n");
                // function for chat
                func(sockfd, pack, numFrag);
               
                // close the socket
                close(sockfd);
            //}
            
        //}
    
}
