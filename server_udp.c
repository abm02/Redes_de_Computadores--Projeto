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
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_LEN];
    socklen_t addr_size;
    int n;
    FILE *fp;

    //Criar o socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0){ erro("Socket Error!"); }

    //Associar o socket a uma porta
    memset(&server_addr,'\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    n = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (n < 0){ erro("Bind Error!"); }

    //Receber a mensagem do cliente
    bzero(buffer, BUFFER_LEN);
    addr_size = sizeof(client_addr);
    recvfrom(sockfd, buffer, BUFFER_LEN, 0, (struct sockaddr*)&client_addr, &addr_size);

    //Abrir o ficheiro de texto para escrita
    fp = fopen("ficheiroParaEscrita.txt", "w");
    if(fp == NULL) { erro("Erro ao abrir o ficheiro!"); }

    //Escrever a mensagem recebida do Cliente num ficheiro de texto
    fprintf(fp, "MENSAGEM RECEBIDA DO CLIENT: \n%s", buffer);

    return 0;
}
