# File Transfer

## Descrição do projeto:

* Pacote UDP.             
* Função para preencher e consultar o pacote.
* Função que cria um novo pacote.
* Função que destroe o pacote.
* Função que recebe o arquivo e fraciona.
* Criação de pacotes com os fragmentos do arquivo
* Função que recebe o protocolo e o pacote para envio
* Função que valida se o pacote está construido corretamente, inclusive valida o checksum.
* Função para comunicação com um receptor.
* Programa receptor.
* Biblioteca com funções e estruturas compartilhadas entre os dois programas.
* Função que recebe os pacotes e registra-os.
* Função que analisa os pacotes recebidos.
* Função que reconstitui o arquivo texto em HD.
* Função para imprimir o arquivo texto na tela.

## Para clonar e executar o projeto

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

### Authors
- [Beatriz Morelatto Lorente](https://github.com/BiaLorente)
- [Rafael Alves de Oliveira Perroni](https://github.com/rafa-perroni00)
