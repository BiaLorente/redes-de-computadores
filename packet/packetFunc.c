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

#include "structs.h"

#define BUFLEN 4
#define DEBUG 1
#define DATASIZE 4
#define SEQNUMSIZE 4
//#define WINDOWSIZE 16
#define WAITLIMIT 2
/* IP header */

//todo 
void fillPacket(packet *pack)
{
    int16_t temp = 0;
    char data_temp[4];
    char teste[4];

    printf("\nEnter source address:");
    scanf("%hd", &temp);
    pack->sourceAddress = temp;
    temp = 0;

    printf("\nEnter destiny address:");
    scanf("%hd", &temp);
    pack->destAddress = temp;
    temp = 0;

    printf("\nEnter length:");
    scanf("%hd", &temp);
    pack->length = temp;
    temp = 0;

    printf("\nEnter checksum:");
    scanf("%hd", &temp);
    pack->checksum = temp;
    temp = 0;

    fgets(teste, sizeof(teste), stdin);

    //char teste[4];
    printf("\nEnter data:");
    bzero(teste, sizeof(teste));
    fgets(teste, sizeof(teste), stdin);
    printf("\nYour data:");
    puts(teste);
    strcpy(pack->data, teste);

    return; //pack;
}

void printPacket(packet pack)
{
    printf("\nSource Addres: %hd", pack.sourceAddress);
    printf("\nDestiny Addres: %hd", pack.destAddress);
    printf("\nLength: %hd", pack.length);
    printf("\nChecksum: %hd", pack.checksum);
    printf("\nData: ");
    puts(pack.frame.buffer);
    printf("\nNumero da sequencia: %d", pack.frame.seqNum);

}

packet *create()
{
    packet *pack = (packet *)malloc(sizeof(packet));
    return pack;
}

void destroy(packet *pack)
{
    free(pack);
}

//Transfer text file
//TODO function receives: filePath, fragLengh. returns fileFragmented(array or data structure)
int inet_aton(const char *cp, struct in_addr *inp);


sentFrame *fragmentFile(FILE *fp, int fragLenght)
{
    char buf[BUFLEN], ackBuf[BUFLEN];
    int recvlen;
    int finished = 0;
    int remainingPackets = 0;

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

    // Lenght * fragLenght
    int windowSize = lenght * fragLenght;

    //initialize the window structure
    sentFrame *window = (sentFrame *)malloc(sizeof(sentFrame) * (windowSize));

    /* transmit file data */
    int i = 1;

    //if (lenght % WINDOWSIZE == 0)
    //{
    while (finished != 1)
    {
        for (int j = 0; j < windowSize; j++)
        {
            if (window[j].armed == 0)
            {
                fseek(fp, (i - 1) * fragLenght, SEEK_SET);
                //window[j].buffer = malloc(sizeof(char) * (fragLenght));
                memset(window[j].buffer, 0, fragLenght);
                //bzero(window[j].buffer, sizeof(window[j].buffer));
                int nRead = fread(window[j].buffer, 1, fragLenght, fp);
                printf("\nBuffer rigth now:    ");
                puts(window[j].buffer);
                if (nRead == 0)
                {
                    printf("Free final empty packet\n");
                    //free(window[j].buffer);
                    window[j].seqNum = i;
                    window[j].finished = 1;
                    window[j].armed = 0;
                    finished = 1;
                }
                else
                {
                    window[j].seqNum = i;
                    window[j].armed = 1;
                    window[j].finished = 0;
                }
                printf("number of bytes read: %d\n", nRead);
                printf("number of the window: %d\n", i);

                break;
            }
        }
        i++;
    }
    // }
    //close(fp);
    fclose(fp);
    return window;
}

packet fillPacketWithFrag(sentFrame window, int fragLenght)
{
    packet pack;// = create();

    int16_t temp = 0;
    //char **data_temp =  malloc(fragLenght * 2);
    char teste[fragLenght * 2];
    char data_temp[4];

    printf("\nEnter source address:");
    scanf("%hd", &temp);
    pack.sourceAddress = temp;
    temp = 0;

    printf("\nEnter destiny address:");
    scanf("%hd", &temp);
    pack.destAddress = temp;
    temp = 0;

    printf("\nEnter length:");
    scanf("%hd", &temp);
    pack.length = temp;
    temp = 0;

    printf("\nEnter checksum:");
    scanf("%hd", &temp);
    pack.checksum = temp;
    temp = 0;

    //char teste[4];
    bzero(teste, sizeof(teste));
    printf("\nwindow.buffer size %lu:", sizeof(window.buffer));
    printf("\nYour data:");
    puts(window.buffer);
    //data_temp = strdup(window.buffer);
    strcpy(data_temp,window.buffer);
    //pack.frame.buffer = strdup(data_temp);
    strcpy(pack.frame.buffer,data_temp);


    pack.frame.seqNum = window.seqNum;
    printf("\nSequel Number: %d", pack.frame.seqNum);
    printf("\nData: ");
    puts(pack.frame.buffer);
    return pack; //pack;
}

void rewindFile(packet pack)
{
    FILE *fp;

       if ((fp = fopen("output.txt", "a")) == NULL)
       {
           printf("Error opening the file\n");
           exit(1);
       }
    //fseek(fp, 0, SEEK_END);

       //for (int i = 0; i < 5; i++)
       //{
           fwrite(pack.frame.buffer, 3, 1, fp);
           //tam += segmento[i].tam;
       //}
    rewind(fp);

       fclose(fp);
       //return tam;
}
