#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>

int main(){
    WSADATA wsaData;
    int iResult;

    // Initialiser Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    int serverSocket, newSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    int addr_size;

    // Créer le socket.
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    // Configurer les paramètres de l'adresse du serveur
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

    // Lier le socket avec l'adresse
    bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    // Écouter sur le socket
    if(listen(serverSocket, 5) == 0)
        printf("Listening\n");
    else
        printf("Error\n");

    // Accepter l'appel
    addr_size = sizeof serverStorage;
    newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);

    // Recevoir des messages
    char buffer[1024];
    recv(newSocket, buffer, 1024, 0);
    printf("Réponse reçue du client: %s\n", buffer); 

    // Envoyer un message au client
    char *message = "Hello Client!\n";
    send(newSocket, message, strlen(message), 0);

    // Fermer le socket
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
