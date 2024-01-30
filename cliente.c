#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define MAX_NAME_LENGTH 50

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char name[MAX_NAME_LENGTH];

    // Criar socket do cliente
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\nErro na criação do socket\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Converter o endereço IPv4 e verificar se é válido
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nEndereço inválido\n");
        return -1;
    }

    // Conectar ao servidor
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nErro na conexão\n");
        return -1;
    }

    // Digitar o nome e enviar para o servidor
    printf("Digite seu nome: ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    send(sock, name, strlen(name), 0);
    printf("Nome enviado para o servidor.\n");

    return 0;
}