# CONEXÃO TCP
Conexão LAN entre computadores, arquitetura cliente-servidor.

## Motivação
Criar jogo multiplayer

## pre-requisitos
Alterar codigo IP do computador(servidor) tanto no servidor qunto no cliente.

Para obter os endereços IP dos computadores na LAN, você pode usar o comando `ipconfig` no Windows ou `ifconfig` no Linux.

## Precauções
### Compilação:
Certifique-se de compilar os códigos separadamente para o servidor e o cliente.
- `gcc server.c -o servidor`
- `gcc cliente.c -o cliente`

### Execução:
Execute o servidor primeiro em um terminal.
### Firewall:
Certifique se de que o firewall da máquina esteja configurado para permitir a comunicação na porta especificada (no exemplo, a porta 8080).

##

Obs: codigo basico para fins de teste.
