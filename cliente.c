#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345
#define MAX_BUFFER_SIZE 1024

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    int client_socket;
    struct sockaddr_in server_addr;

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

    // Receber o nome do jogador do servidor
    char player_name[MAX_BUFFER_SIZE];
    if (recv(client_socket, player_name, sizeof(player_name), 0) == -1)
        error("Erro ao receber dados do servidor");

    printf("Bem-vindo, %s!\n", player_name);

    // Loop principal para a lógica do jogo
    while (1) {
        // Exemplo: Receber informações do servidor sobre o estado atual do jogo
        char game_info[MAX_BUFFER_SIZE];
        if (recv(client_socket, game_info, sizeof(game_info), 0) == -1)
            error("Erro ao receber dados do servidor");

        printf("%s\n", game_info);

        // Verificar se é a vez do jogador fazer uma jogada
        int is_player_turn;
        if (recv(client_socket, &is_player_turn, sizeof(is_player_turn), 0) == -1)
            error("Erro ao receber dados do servidor");

        if (is_player_turn) {
            // Exemplo: Enviar opções de jogada para o servidor (cartas disponíveis, etc.)
            // Aguardar a resposta do jogador
            int player_choice;
            printf("Sua vez! Escolha uma opção: ");
            scanf("%d", &player_choice);
            send(client_socket, &player_choice, sizeof(player_choice), 0);
        }
    }

    // Fechar o socket do cliente
    close(client_socket);

    return 0;
}
