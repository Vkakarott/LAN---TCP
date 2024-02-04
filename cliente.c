#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define HOST_IP "127.0.0.1" // IP que remete ao localhost
#define PORT 8080
#define MAX_BUFFER_SIZE 5024

int client_socket;
struct sockaddr_in server_addr;

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

// Funcao para receber mensagem do servidor
char* receiveFromServer() {
    char buffer[MAX_BUFFER_SIZE] = {0};
    read(client_socket, buffer, MAX_BUFFER_SIZE);
    return strdup(buffer);
}

// Funcao para enviar mensagem para o servidor
void sendToServer(const char *message) {
    send(client_socket, message, strlen(message), 0);
}

int main() {
    // Obter o IP do servidor
    printf("Digite o IP do servidor: ");
    char SERVER_IP[20];
    scanf("%s", SERVER_IP);
    if(strcmp(SERVER_IP, "localhost") == 0)
        strcpy(SERVER_IP, HOST_IP);
    
    // Criação do socket do cliente
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
        error("Erro ao criar o socket do cliente");

    // Configuração do endereço do servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    // Conexão ao servidor
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
        error("Erro ao conectar ao servidor");

    printf("Conectado ao servidor\n");

    // Loop principal para a lógica do jogo
    while (1) {
        char mensage[MAX_BUFFER_SIZE];
        char response[MAX_BUFFER_SIZE];

        // Receber mensagem do servidor
        strcpy(mensage, receiveFromServer());
        if (strcmp(mensage, "exit") == 0) {
            printf("Servidor fechado...\n");
            break;
        }
        printf("%s\n", mensage);

        // resposta do usuário
        scanf(" %[^\n]", response);
        sendToServer(response);

        // Condicao de parada
        if (strcmp(response, "exit") == 0) {
            printf("Desconectando do servidor...\n");
            break;
        }
    }
    close(client_socket);

    return 0;
}