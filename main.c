#include "fichier.h"
#include "projet.h"
int p = 0;
int main() {
    // Initialisation du générateur d'aléatoire 
    // (Très important si ton labyrinthe ou tes monstres sont placés au hasard dans ton menu)
    srand(time(NULL));
    int rejouer = 0;

    do {
        aventurier le_groupe[4]; // Le tableau qui va contenir jusqu'à 4 joueurs
        int nb_joueurs = 0;

        printf("\n======================================\n");
        printf("        BIENVENUE DANS MEMO RPG       \n");
        printf("======================================\n\n");

        // 1. APPEL DE TON MENU 
        // Le fichier Menu_lancement_jeu.c prend le relais pour 
        // initialiser la carte, créer les joueurs et renvoyer le nombre de participants.
        // (Vérifie que c'est bien le nom exact de ta fonction de menu !)
        nb_joueurs = configurer_partie(le_groupe); 

        // 2. LANCEMENT DU JEU
        // Si le menu s'est bien passé et qu'il y a des joueurs, on lance le combat !
        if (nb_joueurs > 0) {
            partie(le_groupe, nb_joueurs);
        }

        // 3. LA BOUCLE DE REPLAY
        printf("\n======================================\n");
        printf("Voulez-vous refaire une partie ? (1 = Oui, 0 = Quitter) : ");
        int resultat = scanf("%d", &rejouer);
        
        // Sécurité habituelle pour nettoyer le clavier
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { } 
        if (resultat != 1) rejouer = 0; 

    } while (rejouer == 1);

    printf("\nMerci d'avoir joue au Memo RPG ! A bientot.\n");
    return 0;
}
