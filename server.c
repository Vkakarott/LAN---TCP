#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define MAX_CLIENTS 4

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    
    // Criar socket do servidor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Falha ao criar socket do servidor");
        exit(EXIT_FAILURE);
    }
    
    // Configurar opções do socket
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Falha ao configurar opções do socket");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Vincular o socket à porta e ao endereço
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address))<0) {
        perror("Falha ao vincular o socket");
        exit(EXIT_FAILURE);
    }
    
    // Esperar por conexões
    if (listen(server_fd, 3) < 0) {
        perror("Erro ao esperar por conexões");
        exit(EXIT_FAILURE);
    }
    
    printf("Servidor esperando por conexões...\n");
    
    // Aceitar até 4 clientes
    int client_sockets[MAX_CLIENTS];
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen))<0) {
            perror("Erro ao aceitar conexão");
            exit(EXIT_FAILURE);
        }
        
        client_sockets[i] = new_socket;
        printf("Cliente %d conectado\n", i+1);
    }

    // Receber dados dos clientes e imprimir na tela
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        valread = read(client_sockets[i], buffer, sizeof(buffer));
        printf("Cliente %d: %s\n", i+1, buffer);
    }

    return 0;
}