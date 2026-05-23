void afficher_jeu(char aventurier_joueurs[], int nb_joueurs, int nb_tours, int temps_s) {

    // On efface le terminal pour rafraichir l'ecran 
    printf("\033[H\033[2J");

    // pour afficher le temps de la partie 
    int mm = temps_s / 60;
    int ss = temps_s % 60;
    printf("=== MEMO-RPG === Tour : %d   Temps : %02d:%02d\n\n", nb_tours, mm, ss);




    // les infos joueurs a droite sur la bonne ligne
    int ligne_panneau = 0;

    for (int rangee = 0; rangee < NB_RANGEES; rangee++) {

        // Ligne horizontale au dessus de la rangee
        afficher_separateur_ligne(rangee);
        printf("  ");
        afficher_panneau_joueur_ligne(joueurs, nb_joueurs, nb_tours, ligne_panneau);
        ligne_panneau++;
        printf("\n");

        // On affiche chaque case de la rangee une par une
        for (int col = 0; col < NB_COLONNES; col++) {
            int idx = joueur_sur_case(joueurs, nb_joueurs, rangee, col);
            afficher_case(labyrinthe[rangee][col], idx, rangee, col);
        }

        // Le bord droit ne s'affiche que pour les vraies lignes du labyrinthe pas pour les rangees 0 et 6 qui sont juste les positions du debut 
       
        if (rangee != 0 && rangee != 6) {
            printf("|");
        }

        printf("  ");
        afficher_panneau_joueur_ligne(joueurs, nb_joueurs, nb_tours, ligne_panneau);
        ligne_panneau++;
        printf("\n");
    }

    // Fermeture du bas du plateau
    afficher_separateur_ligne(NB_RANGEES - 1);
    printf("\n");

    // Rappel des symboles pour que le joueur ou faut qu'on ajoute des images !!!
    printf("-- Legende --\n");
    printf("  [B] Basilic   [Z] Zombie   [T] Troll   [H] Harpie\n");
    printf("  [A] Arme ant. [C] Coffre   [P] Portail [O] Totem\n");
    printf("  [?] Case cachee\n\n");

    // Derniers evenements du jeu : combats, coffres, portails etc 
    afficher_log();
}




