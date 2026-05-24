#include "fichier.h"
#include "projet.h"
#include "fichier_sauvg.h"
#include <windows.h>

int p = 0;
int main() {
    SetConsoleOutputCP(CP_UTF8);
    // Initialisation du générateur d'aléatoire 
    srand(time(NULL));
    
    charger_statistiques(); //charge les stats de base 
    
    int choix_menu = 0;

    do {
        printf("\033[2J\033[H");
        printf("======================================\n");
        printf("        BIENVENUE DANS MEMO RPG       \n");
        printf("======================================\n\n");
        printf("  Que voulez-vous faire ?\n\n");
        printf("  1. Aventure ! (Lancer une partie)\n");
        printf("  2. Hall of Fame (Voir les stats)\n");
        printf("  0. Rentrer a la maison (Quitter)\n\n");
        printf("Votre choix : ");

        int r = scanf("%d", &choix_menu);
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
        if (r != 1) choix_menu = -1;

        if (choix_menu == 1) {
            int rejouer = 0;
            do {
                aventurier joueurs[4];
                int nb_joueurs = configurer_partie(joueurs);

                if (nb_joueurs > 0) {
                    partie(joueurs, nb_joueurs);
                }

                printf("\n======================================\n");
                printf("  Alors, pret pour une revanche ?\n\n");
                printf("  1. Oui, on repart !\n");
                printf("  2. Non, je rentre au village.\n");
                printf("Votre choix : ");
                int r2 = scanf("%d", &rejouer);
                while ((c = getchar()) != '\n' && c != EOF) { }
                if (r2 != 1) rejouer = 0;

            } while (rejouer == 1);
        }
        else if (choix_menu == 2) {
            afficher_scores();
            printf("Appuyez sur [Entree] pour revenir au menu...");
            while ((c = getchar()) != '\n' && c != EOF) { }
            getchar();
        }

    } while (choix_menu != 0);

    sauvegarder_statistiques();
    printf("\nMerci d'avoir joue, aventurier. A bientot !\n");
    return 0;
}