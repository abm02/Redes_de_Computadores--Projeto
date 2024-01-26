#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_LEN 500
#define PORT 9988

void erro(char *s){
    perror(s);
    exit(1);
}

int main(){
    int sockfd;
    struct sockaddr_in addr;
    char buffer[BUFFER_LEN];
    socklen_t addr_size;
    FILE *fp;

    //Criar o socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0){ erro("Socket Error!"); }

    //Associar o socket a uma porta
    memset(&addr,'\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    //Abrir ficheiro de texto para leitura
    fp = fopen("ficheiroParaLeitura.txt", "r");
    if (fp == NULL){ erro("Erro ao abrir o ficheiro!"); }

    //Ler os dados do ficheiro de texto
    bzero(buffer, BUFFER_LEN);
    fgets(buffer, BUFFER_LEN, fp);

    //Enviar os dados lidos do ficheiro de texto para o Server
    sendto(sockfd, buffer, BUFFER_LEN, 0, (struct sockaddr*)&addr, sizeof(addr));

    return 0;
}
