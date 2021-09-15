#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <strings.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdbool.h>
#include "package.h"

socketType socketCreateServ(char selectProtocol){
    int sock, len;
    struct sockaddr_in name;
    struct hostent *hp, *gethostbyname();

    sock = socket (AF_INET, selectProtocol == 'U' ? SOCK_DGRAM : SOCK_STREAM, 0);
    if (sock<0){
        perror ("Error opening socket");
        exit (1);
    }
   
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = INADDR_ANY;
    name.sin_port= htons (1234);

    if(bind (sock, (struct sockaddr *)&name, sizeof name) < 0){
        perror ("binding datagrama");
        exit(1);
    }

    len = sizeof(name);
    if(getsockname(sock, (struct sockaddr *)&name, &len) < 0){
        perror("Error getsockname");
        exit(1);
    }

    printf("Port located: %d\n",ntohs(name.sin_port));

    socketType socketUDP;
    socketUDP.sock= sock;
    socketUDP.name = name;

    return socketUDP;
}

void receivePackage(char protocol, Package * packages, int *packagesQtd) {
    socketType socketData = socketCreateServ(protocol);
    Package * package = createPackage();
    int i=0, len=0;
    char number[10];
    
    recvfrom(socketData.sock, number, sizeof(number), 0, (struct sockaddr *)&socketData.name, &len);
    
    len = sizeof(socketData.name);
    *packagesQtd = atoi(number);
    
    while(i < *packagesQtd) {
        recvfrom(socketData.sock, (char *)&packages[i], sizeof(packages[i]), 0, (struct sockaddr *)&socketData.name, &len);
        unsigned int check = checkChecksum(packages[i].data,(strlen(packages[i].data)),seed);
        if(check != packages[i].checksum){
           printf("\n\n Error Package %d\n checksum recebido %d\n check %d \n", i+1, packages[i].checksum, check);
        }
        i++;
    }
}

void createFILE(Package * packages, int packagesQtd) {
  FILE *output_file;
  int i = 0;
  output_file = fopen("newFile.txt", "w");

  if (output_file == NULL)
    printf("\nError in file read!\n");

  while(i < packagesQtd) {
    fwrite(packages[i].data, sizeof(char), strlen(packages[i].data), output_file);
    i++;
  }
}

void printPackage(Package * packages, int packagesQtd){
    for(int i=0;i<packagesQtd;i++){
        checkPackage(&packages[i]);
    }
}

int main() {
    int packagesQtd;
    Package * packages =  malloc(1024*sizeof(Package));
    receivePackage('U', packages, &packagesQtd);
    createFILE(packages, packagesQtd);
    printPackage(packages, packagesQtd);
    exit(0);
}