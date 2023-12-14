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
    if (serverSocket == INVALID_SOCKET) {
        printf("Échec de la création du socket : %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    printf("Configuration des paramètres du serveur...\n");
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    printf("Liaison du socket...\n");
    if (bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Échec de la liaison : %ld\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("Démarrage de l'écoute...\n");
    if (listen(serverSocket, 5) == SOCKET_ERROR) {
        printf("Écoute échouée : %ld\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("En attente de connexions...\n");
    addr_size = sizeof serverStorage;
    newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);
    if (newSocket == INVALID_SOCKET) {
        printf("Échec de l'acceptation : %ld\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("Connexion acceptée. En attente de messages...\n");
    char buffer[1024];
    int bytesReceived = recv(newSocket, buffer, 1024, 0);
    if (bytesReceived == SOCKET_ERROR) {
        printf("Échec de la réception : %ld\n", WSAGetLastError());
    } else if (bytesReceived == 0) {
        printf("La connexion a été fermée par le client.\n");
    } else {
        printf("Réponse reçue du client : %s\n", buffer);
    }

    printf("Envoi d'un message au client...\n");
    char *message = "Hello Client!\n";
    int bytesSent = send(newSocket, message, strlen(message), 0);
    if (bytesSent == SOCKET_ERROR) {
        printf("Échec de l'envoi : %ld\n", WSAGetLastError());
    }

    printf("Fermeture du socket...\n");
    closesocket(newSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
