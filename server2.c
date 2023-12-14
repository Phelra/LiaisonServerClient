#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h> // Include for read and write functions

int main(){
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    // Créer le socket.
    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    
    // Configurer les paramètres de l'adresse du serveur
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

    // Lier le socket avec l'adresse
    bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    // Écouter sur le socket
    if(listen(serverSocket,5)==0)
        printf("Listening\n");
    else
        printf("Error\n");

    // Accepter l'appel
    addr_size = sizeof serverStorage;
    newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);

    // Boucle pour envoyer des messages continuellement au client
    while(1){
        char buffer[1024];
        printf("<Remote shell> ");
        fgets(buffer, 1024, stdin); // Lire le message de l'utilisateur

        // Envoyer le message au client
        if(send(newSocket, buffer, strlen(buffer), 0) < 0){
            printf("Échec de l'envoi du message.\n");
            break; // Sortir de la boucle si l'envoi échoue
        }
    }

    return 0;
}
