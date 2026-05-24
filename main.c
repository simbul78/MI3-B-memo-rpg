#include "fichier.h"
#include "projet.h"
#include "fichier_sauvg.h"
#include <windows.h>

int p = 0;  // variable globale pour la position de départ des joueurs (case 1 à 5)
int main() {

    // Permet d'afficher les emojis et caractères spéciaux dans le terminal Windows
    SetConsoleOutputCP(CP_UTF8);
    // Initialisation du générateur d'aléatoire 
    srand(time(NULL));
    
    charger_statistiques(); //charge les statistiques de base 
    
    int choix_menu = 0;  // stocke le choix du joueur dans le menu

    do {
        // Efface le terminal et affiche le menu principal
        
        printf("\033[2J\033[H");
        printf("======================================\n");
        printf("        BIENVENUE DANS MEMO RPG       \n");
        printf("======================================\n\n");
        printf("  Que voulez-vous faire ?\n\n");
        printf("  1. Aventure ! (Lancer une partie)\n");
        printf("  2. Hall of Fame (Voir les stats)\n");
        printf("  0. Rentrer a la maison (Quitter)\n\n");
        printf("Votre choix : ");
// Lecture du choix avec vérification : si la saisie n'est pas un nombre, on met -1
        int r = scanf("%d", &choix_menu);
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
        if (r != 1) choix_menu = -1;

        // CAS 1 : Lancer une partie

        if (choix_menu == 1) {
            int rejouer = 0;  // contrôle la boucle "rejouer"
            do {
                aventurier joueurs[4]; // tableau des 4 aventuriers possibles
                
                // Configure la partie : demande noms, classes, position de départ
                // et remplit le plateau aléatoirement. Retourne le nombre de joueurs.
                
                int nb_joueurs = configurer_partie(joueurs);

                // Lance la partie uniquement si la configuration a réussi

                if (nb_joueurs > 0) {
                    partie(joueurs, nb_joueurs);
                }
// Propose de rejouer une fois la partie terminée
                printf("\n======================================\n");
                printf("  Alors, pret pour une revanche ?\n\n");
                printf("  1. Oui, on repart !\n");
                printf("  2. Non, je rentre au village.\n");
                printf("Votre choix : ");
                int r2 = scanf("%d", &rejouer);
                while ((c = getchar()) != '\n' && c != EOF) { }
                if (r2 != 1) rejouer = 0;// saisie invalide → on ne relance pas

            } while (rejouer == 1);  // boucle tant que le joueur veut rejouer
        }

            // CAS 2 : Afficher les statistiques ( STATISTIQUES DES JOUEURS ) 
            
        else if (choix_menu == 2) {
            afficher_scores();    // affiche le tableau des stats de tous les joueurs
            printf("Appuyez sur [Entree] pour revenir au menu...");
            while ((c = getchar()) != '\n' && c != EOF) { }   // vide le buffer
            getchar();   // attend que le joueur appuie sur Entrée
        }

    } while (choix_menu != 0);    // boucle tant que le joueur ne choisit pas 0 (Quitter) 

    // Sauvegarde les statistiques mises à jour dans le fichier avant de quitter

    sauvegarder_statistiques();
    printf("\nMerci d'avoir joue, aventurier. A bientot !\n");
    return 0; // fin du programme
    
}
