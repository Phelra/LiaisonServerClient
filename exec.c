#include <stdio.h>   // Pour perror
#include <stdlib.h>  // Pour system

int main() {
    // Exécute la commande "ls -l" du shell
    int ret = system("ls -l");
    
    if (ret == -1) {
        // La commande n'a pas pu être exécutée
        perror("Erreur lors de l'exécution de la commande");
        return 1;
    }

    return 0;
}
