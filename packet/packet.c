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
    printf("\nEnter the fragments lenght:");
    scanf("%d", &fragLenght);
    window = fragmentFile(fp, fragLenght);

    for (int i = 0; i < sizeof(window); i++)
    {
        if (window[i].armed == 1)
        {
        fillPacketWithFrag(window[i], fragLenght);
        }      
    }

    int finished = 0;
    int remainingPackets = 0;

    unsigned int i = 1;

    return 0;
}