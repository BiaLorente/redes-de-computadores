# Transferência de arquivo texto em C

## Descrição do projeto:

1. Implementação do pacote UDP utilizando a seguinte estrutura específica:
```c
typedef struct {
    char data[32];
    int16_t originPort;
    int16_t destinationPort;
    int16_t size;
    int16_t checksum;
}Package;
```
2. Função que preenche e consulta cada um dos campos do pacote.

```c
void fillPackage(Package *package, char* data, int16_t originPort, int16_t destinationPort)

```

3. Função que cria um novo pacote.

```c
Package * createPackage()
```

4. Função que destroe o pacote.

```c
void deletePackage(Package *package)
```

5. Função que recebe, por parâmetro: o caminho para um arquivo (que neste caso será um txt) e também a uma quantidade máxima de bits a qual esse arquivo será fracionado. Essa função retorna um array ou uma estrutura de dados com o arquivo totalmente fragmentado conforme solicitado.

```c
void fragmentArquive(char *file, int fragmentsQtd,int size, char fragments[1024][1024])
```

6. Criação de pacotes a serem transferidos, já com conteúdo completo. Usando os fragmentos gerados pela função anterior.

```c
void fragmentsToPackage(char fragments[1024][1024], int fragmentsQtd, Package * packages, int *packagesQtd)
```

7. Função de envio de pacotes que recebe um pacote e um parâmetro indicando qual protocolo de camada de transporte será usado.
```c
void sendPackages(Package *packages, socketType socket, int packagesQtd)
```

8. Função que valida se o pacote está construido corretamente.
```c
unsigned int checkChecksum(char *buffer, size_t len, unsigned int seed)
```

9. Função que faz a comunicação com um receptor.
```c
typedef struct {
    int sock;
    struct sockaddr_in name;
}socketType;

socketType socketCreate(char selectProtocol)
```

10. Programa que recebe os pacotes transmitidos
```
/server.c
```

11. Biblioteca com funções básicas.
```
/package.h
```

12. Função que recebe os pacotes e os registra um a um em arquivo de texto para que possam ser analisados.
```c
receivePackage(char protocol, Package * packagelist, int *numberOfPackeges)
```

13. Função que faz a análise dos pacotes recebidos.
```c
unsigned int checkChecksum(char *buffer, size_t len, unsigned int seed)
```

14. Função que remonta o arquivo recebido.
```c
void createFILE(Package * packageList, int numberOfPackeges)
```

15. Função para imprimir na tela o conteúdo do arquivo de texto.
```c
void checkPackage(Package *package)
```

16. Biblioteca com funções de pacotes IP.
```
/ip.h
```

17. Implementação do pacote IP utilizando a seguinte estrutura:
```c
typedef struct {
    char version[4];
    char headerLength[4];
    char serviceType[8];
    char totalLength[16];
    char identification[16];
    char flags[4];
    char fragmentOffset[12];
    char timeToLife[8];
    char protocol[8];
    char headerCheckSum[16];
    char sourceIpAddress[32];
    char destinationIp[32];
    char options[32];
    char data[32];
}PackageIP;
```

18. Função para criar um novo pacote.
```c
PackageIP * createIPPackage()
```

19. Função para adicionar os IP's de origem e o de destino.
```c
void setIP(char* destinationIP, PackageIP* package )
```

## Execute localmente com um terminal linux

Clone o projeto

```bash
  git clone https://github.com/BiaLorente/redes-de-computadores.git
```

Vá para o diretório do projeto

```bash
  cd arquive-transfer
```
Compile o server

```bash
  gcc server.c -o ser
```
Compile o cliente

```bash
  gcc client.c -o cli
```

Execute o server
```bash
  ./serv
```

Execute o cliente
```bash
  ./cli
```

Brinque fazendo alterações no arquivo de texto :metal:

### Authors
- [Beatriz Morelatto Lorente](https://github.com/BiaLorente)
- [Rafael Alves de Oliveira Perroni](https://github.com/rafa-perroni00)
