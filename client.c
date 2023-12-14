#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main(){
    int clientSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    printf("Initialisation du client...\n");

    // Créer le socket
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    printf("Socket client créé.\n");

    // Configurer les paramètres de l'adresse du serveur
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

    // Connecter le socket au serveur
    printf("Tentative de connexion au serveur...\n");
    addr_size = sizeof serverAddr;
    if (connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size) < 0) {
        printf("Échec de la connexion au serveur.\n");
        return -1;
    }
    printf("Connecté au serveur.\n");
    printf("Message à envoyer : ");
    char message[1024];
    fgets(message, 1024, stdin);  // Lire la chaîne de caractères y compris les espaces
    printf("Message envoyé : %s\n", message);

    // Envoyer un message au serveur
    send(clientSocket, message, strlen(message), 0);
    printf("Message envoyé au serveur.\n");

    // Recevoir le message du serveur
    recv(clientSocket, buffer, 1024, 0);
    printf("Réponse reçue du serveur: %s\n", buffer);   

    return 0;
}
