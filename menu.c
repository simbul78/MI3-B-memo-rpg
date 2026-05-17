#include "fichier.h"
#include "donnees.h"

int main() {
    int choix_menu;
    int continuer_programme = 1;

    // Initialisations globales (données joueurs, etc.)
    srand(time(NULL));

    while (continuer_programme) {
        printf("\n=== LE-RPG : MENU PRINCIPAL ===\n");
        printf("1. Lancer une nouvelle partie\n");
        printf("2. Voir les stats (Hall of Fame)\n");
        printf("3. Quitter\n");
        printf("Votre choix : ");

        int res = scanf("%d", &choix_menu);
        
        // "La chasse d'eau" pour vider le buffer (Essentiel selon tes consignes !)
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }

        if (res != 1) {
            printf("Entrée invalide. Veuillez saisir un nombre.\n");
            continue;
        }

        switch (choix_menu) {
            case 1:
                lancerPartie(); // Tu déplaceras ton code de création de partie ici
                break;
            case 2:
                afficherScores(); // Pour la mémorisation à long terme [cite: 97]
                break;
            case 3:
                printf("Merci d'avoir joué ! À bientôt.\n");
                continuer_programme = 0;
                break;
            default:
                printf("Option invalide.\n");
        }
    }
    return 0;
}

