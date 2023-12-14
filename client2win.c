#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
    int clientSocket;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    printf("Initialisation du client...\n");

    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr("Adresse IP du serveur");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    printf("Tentative de connexion au serveur...\n");
    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

    printf("Connecté au serveur. Envoi d'un message...\n");
    const char *initialMessage = "Hello Server!";
    send(clientSocket, initialMessage, strlen(initialMessage), 0);

    printf("Fermeture du client.\n");
    close(clientSocket);

    return 0;
}
