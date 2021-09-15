#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <stdbool.h>
#include "ip.h"
#include "package.h"

#define splitFragment 50

int main() {
    int sock = 0, i=0, fragmentsQtd=0, packagesQtd=0;
    Package * packages =  malloc(1024*sizeof(Package));
    PackageIP *pack = createIPPackage();
    char fragments[1024][1024];
       
    fragmentArquive("teste.txt", splitFragment, **fragments, &fragmentsQtd);

    fragmentsToPackage(fragments, fragmentsQtd, packages, &packagesQtd);

    setIP("123.3123.123", pack);
    printf("\nOrigin: %s\n",pack->sourceIpAddress);
    printf("\nDestiny: %s\n",pack->destinationIp);

    sendPackage(packages, 'U', packagesQtd);


    return 0;
}