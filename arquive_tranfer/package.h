int seed = 0;

typedef struct {
    char data[32];
    int16_t originPort;
    int16_t destinationPort;
    int16_t size;
    int16_t checksum;
}Package;

typedef struct {
    int sock;
    struct sockaddr_in name;
}socketType;

unsigned int checkChecksum(char *buffer, size_t len, unsigned int seed){
    unsigned char *buf = (unsigned char *)buffer;
    size_t i;
    for (i = 0; i < len; ++i)
    seed += (unsigned int)(*buf++);
    return seed;
}

Package * createPackage() {
    Package * package = malloc(sizeof(Package));
    return package;
}

void checkPackage(Package *package){
    printf("\nData: %s", package->data);
    printf("\nOrigin Port: %u", package->originPort);
    printf("\nDestination Port: %u", package->destinationPort);
    printf("\nPackage Size: %u", package->size);
    printf("\nChecksum field: %u\n", package->checksum);
}


socketType socketCreate(char selectProtocol){
    int sock;
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

    hp = gethostbyname("localhost");
    if (hp==0){
        perror("Couldn't find host");
        exit(2);
    }

    bcopy ((char*)hp->h_addr, (char *)&name.sin_addr, hp->h_length);

    printf("Port located: %d\n",ntohs(name.sin_port));

    socketType socketUDP;
    socketUDP.sock= sock;
    socketUDP.name = name;
    return socketUDP;
}

void fillPackage(Package *package, char* data, int16_t originPort, int16_t destinationPort){
    memcpy(package->data, data, 32);
    package->originPort = originPort;
    package->destinationPort = destinationPort;
    package->size = strlen(package->data);
}

void sendPackages(Package *packages, socketType socket, int packagesQtd){
    int lenPackage = sizeof(packages)/sizeof(packages[0]), i = 0;

    while(i < packagesQtd) {
        int lenPackage = sizeof(packages[i]);

        int resp = sendto(socket.sock, (char *)&packages[i], lenPackage, 0, (struct sockaddr *)&socket.name, sizeof socket.name);

        if (resp < 0) printf("[ERRO] Envio do pacote %d/%d",i,lenPackage);

        i++;
    }
}


bool checkPackages(Package *packages, int packagesQtd){

    for(int i = 0; i < packagesQtd; i++){
        int lenPackage = strlen(packages[i].data);
        unsigned int check = checkChecksum(packages[i].data, lenPackage, seed);
        if(check != packages[i].checksum){
            return false;
        }
    }
    return true;
}

void deletePackage(Package *packet){
    free(packet);
}


void fragmentArquive(char *file, int fragmentsQtd,int size, char fragments[1024][1024]){
    FILE *arqv;
    int i, n_bytes_read = 0;
    arqv = fopen(file, "rb");

    while ((n_bytes_read = fread(fragments[i], 1, size, arqv)) > 0){
        i++;
	}
    fragmentsQtd=i;   
    fclose(arqv);
}

void fragmentsToPackage(char fragments[1024][1024], int fragmentsQtd, Package * packages, int *packagesQtd)
{
    int fragSize;
    int j=0,aux=0,i=0;


    for(i=0; i<fragmentsQtd; i++){
         fragSize = (strlen(fragments[i]));       
         j=0;

        while(fragSize > 0){
            Package * package = createPackage();
            char * fragAux= fragments[i] + j*32;
            fillPackage(package, fragAux, 1234, 1234);
            packages[aux] = *package;
            *packagesQtd = *packagesQtd + 1;
            if(fragSize >= 31) {
                packages[aux].data[32]='\0';
                packages[aux].checksum = checkChecksum(packages[aux].data, 32, 0);
            } else {
                packages[aux].data[fragSize]='\0';
                packages[aux].checksum = checkChecksum(packages[aux].data, fragSize, 0);
            }
            fragSize-=32;
            j++;
            aux++;
        }
    }
}

void sendInfoPackege(int numPackage, socketType socketData){
    char num[10];
    sprintf(num, "%d", numPackage);
    int resp = sendto(socketData.sock,num, sizeof(num), 0, (struct sockaddr *)&socketData.name, sizeof socketData.name);

    if (resp < 0) printf("Error in number of packages");
}

void sendPackage(Package *packages, char protocol, int packagesQtd){
    socketType socketData = socketCreate(protocol);

    sendInfoPackege(packagesQtd, socketData);

    bool check = checkPackages(packages, packagesQtd);
    if(check){
        sendPackages(packages, socketData, packagesQtd);
    }else{
        perror("Wrong package");
    }
}