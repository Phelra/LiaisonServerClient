#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>

int main(){
    WSADATA wsaData;
    int iResult;

    printf("Initialisation de Winsock...\n");
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup a échoué : %d\n", iResult);
        return 1;
    }

    int serverSocket, newSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    int addr_size;

    printf("Création du socket...\n");
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    printf("Configuration des paramètres du serveur...\n");
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    printf("Liaison du socket...\n");
    bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    printf("Démarrage de l'écoute...\n");
    listen(serverSocket, 5);

    printf("En attente de connexions...\n");
    addr_size = sizeof serverStorage;
    newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);
    printf("Nouvelle connexion acceptée.\n");

    printf("En attente de messages...\n");
    char buffer[1024];
    recv(newSocket, buffer, 1024, 0);
    printf("Message reçu : %s\n", buffer);

    printf("Fermeture du socket...\n");
    closesocket(newSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
