#include <pcap.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "packetFunc.c"
#include "client.c"


#define PORT     8080
#define MAXLINE 1024

#define BUFLEN 4
#define DEBUG 1
#define DATASIZE 4
#define SEQNUMSIZE 4
//#define WINDOWSIZE 16
#define WAITLIMIT 2

int main(void)
{
    int fragLenght;

    FILE *fp;

    sentFrame *window;
    //packet *packetFull = create();
    printf("\nEnter the fragments lenght:");
    scanf("%d", &fragLenght);
    window = fragmentFile(fp, fragLenght);
    
    fp = fopen("teste.txt", "rb");
    if (fp == NULL)
    {
        perror("fopen");
        exit(1);
    }

    //read in bytes de size
    fseek(fp, 0, SEEK_END);
    long lenght = ftell(fp);
    rewind(fp);
    fclose(fp);

    
    // Lenght * fragLenght
    int windowSize = lenght * fragLenght;

    //initialize the window structure
    packet *packetFull = malloc(sizeof(packet) * (windowSize));
    

    for (int i = 0; i < sizeof(window); i++)
    {
        if (window[i].armed == 1)
        {
            packetFull[i] = fillPacketWithFrag(window[i], fragLenght);
            //printPacket(packetFull[0]);
        }
    }
    /*printPacket(packetFull[0]);
    printPacket(packetFull[1]);
    printPacket(packetFull[2]);
    printPacket(packetFull[3]);*/

    
    sendPacket(packetFull, windowSize);


    int finished = 0;
    int remainingPackets = 0;

    unsigned int i = 1;

    return 0;
}
