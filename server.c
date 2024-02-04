#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define NUMERO_CLIENTS 1
#define MAX_BUFFER_SIZE 7000
#define CHAR_SIZE 20
#define PORT 8080

int server_fd, new_socket, valread;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);

void sendToClient(int client_socket, const char *message) {
    send(client_socket, message, strlen(message), 0);
    sleep(1);
}

char* receiveFromClient(int client_socket) {
    char buffer[MAX_BUFFER_SIZE] = {0};
    valread = read(client_socket, buffer, sizeof(buffer));
    return strdup(buffer);
}

int main() { 
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

    // Mostrar o IP do servidor
    system("hostname -I");
    
    // Esperar por conexões
    if (listen(server_fd, 3) < 0) {
        perror("Erro ao esperar por conexões");
        exit(EXIT_FAILURE);
    }
    
    printf("\033[3;90mServidor esperando cliente...\033[0;37m\n\n");
    
    // Aceitar conexão
    int client_sockets;
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen))<0) {
        perror("Erro ao aceitar conexão");
        exit(EXIT_FAILURE);
    }
        
    client_sockets = new_socket;
    printf("Cliente conectado\n");

    while (1){
        char mensage[MAX_BUFFER_SIZE];
        char response[MAX_BUFFER_SIZE];

        // Enviar e receber mensagens
        printf("Digite sua mensagem ao cliente: ");
        scanf("%s", mensage);
        sendToClient(client_sockets, mensage);
        if (strcmp(mensage, "exit") == 0) {
            printf("\033[3;90mCliente fechado...\033[0;37m\n");
            break;
        }
        printf("\033[3;90mMensagem enviada com sucesso\033[0;37m\n");
        sleep(1);
        strcpy(response, receiveFromClient(client_sockets));
        printf("%s\n", response);
        if (strcmp(response, "exit") == 0) {
            printf("Cliente fechado...\n");
            break;
        }
    }
    
    return 0;
}