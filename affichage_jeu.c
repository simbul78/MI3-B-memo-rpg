// Gestion de tout l'affichage du jeu Memo-RPG
 //Affichage : plateau 7x7, panneau joueurs, log des evenements
 

#include <stdio.h>
#include <string.h>
#include "projet.h"   // structures aventurier, Carte, labyrinthe... 


#define LARGEUR_CASE   7    // nb de caracteres par case du plateau       
#define LOG_MAX_LIGNES 6    // nb de lignes conservees dans le log        
#define LOG_MAX_CHARS  60   // longueur max d'une ligne de log            


//  Carte cachee   :  [ ? ]
//  Monstre        :  [ M ]   (Basilic=B  Zombie=Z  Troll=T  Harpie=H)
//  Coffre         :  [ C ]
//   Arme antique   :  [ A ]
//  Portail        :  [ P ]
// Totem          :  [ T ]
 //  Bordure/vide   :     (espace)
 // Joueur         :  [ G ] / [ R ] / [ W ] / [ V ]


// Lettres des classes pour afficher le joueur sur sa case 
static const char LETTRE_CLASSE[] = {'G', 'R', 'W', 'V'};
//                                   ^guerrier ^ranger ^magicien ^voleur  


static const char *NOM_CLASSE[] = {"Guerrier", "Ranger", "Magicien", "Voleur"};


static const char *NOM_ARME_BASE[] = {
    "Bouclier", "Torche", "Arc long", "Hache"
};


static const char *NOM_ARME_ANTIQUE[] = {
    "Epee de Feu", "Baton Familiers", "Grimoire", "Dague Sommeil"
};


static const char *NOM_MONSTRE[] = {"Basilic", "Zombie", "Troll", "Harpie"};


typedef struct {
    char lignes[LOG_MAX_LIGNES][LOG_MAX_CHARS];
    int  nb;   // nombre de lignes actuellement stockees 
} LogEvenements;

// Variable globale du log, initialisee a vide 
LogEvenements log_jeu = { .nb = 0 };


 // log_ajouter()
// Ajoute un message dans le log en decalant les anciens vers le bas.
 // Si le log est plein, la ligne la plus ancienne est ecrasee.
 
void log_ajouter(const char *message) {
    // Si le log est plein, on decale tout vers le haut (supprime la 1re ligne) 
    if (log_jeu.nb == LOG_MAX_LIGNES) {
        for (int i = 0; i < LOG_MAX_LIGNES - 1; i++) {
            strncpy(log_jeu.lignes[i], log_jeu.lignes[i + 1], LOG_MAX_CHARS - 1);
            log_jeu.lignes[i][LOG_MAX_CHARS - 1] = '\0';
        }
        log_jeu.nb = LOG_MAX_LIGNES - 1;
    }
    strncpy(log_jeu.lignes[log_jeu.nb], message, LOG_MAX_CHARS - 1);
    log_jeu.lignes[log_jeu.nb][LOG_MAX_CHARS - 1] = '\0';
    log_jeu.nb++;
}



 // joueur_sur_case()
 // Renvoie l'index du joueur present sur la case (x,y), ou -1 si vide.
 // On compare les coordonnees de chaque aventurier actif.
 
static int joueur_sur_case(aventurier joueurs[], int nb_joueurs, int x, int y) {
    for (int j = 0; j < nb_joueurs; j++) {
        /* On n'affiche le joueur que s'il est dans le labyrinthe (pas en Bordure) */
        if (joueurs[j].a.x == x && joueurs[j].a.y == y) {
            return j;
        }
    }
    return -1;
}




 // symbole_case()
 // Renvoie le caractere a afficher au centre d'une case revelee.
 
static char symbole_case(Carte c) {
    switch (c.Categorie_Carte) {
        case Monstre:
            // Lettre specifique au type de monstre 
            switch (c.type_monstre) {
                case Basilic: return 'B';
                case Zombie:  return 'Z';
                case Troll:   return 'T';
                case Harpie:  return 'H';
                default:       return 'M';
            }
        case ArmeAntiques: return 'A'; //faire la meme chose que pour les monstre : montrer quelle est l'arme antique en question
        case Totem:        return 'O';
        case Portail:      return 'P';
        case Coffre:       return 'C';
        default:           return ' ';
    }
}


// afficher_case()
// Affiche le contenu d'une case en 7 caracteres : "[ X ]  "
// Si un joueur est dessus, priorite au symbole du joueur.
// Si la case est une Bordure, on affiche des espaces.
 
static void afficher_case(Carte c, int idx_joueur, int x, int y) {
    // Case bordure = vide (cases en dehors du labyrinthe 5x5) 
    if (c.Categorie_Carte == Bordure) {
        printf("       "); // 7 espaces 
        return;
    }

    // Un joueur est present sur cette case 
    if (idx_joueur >= 0) {
        printf("[ %c ]  ", LETTRE_CLASSE[idx_joueur]);
        return;
    }

    //Case cachee 
    if (c.Etat_carte == 0) {
        printf("[ ? ]  ");
        return;
    }

    // Case revelee 
    printf("[ %c ]  ", symbole_case(c));
}


// afficher_separateur_ligne()
// Affiche une ligne de separation entre deux rangees du plateau.
// Ne trace la ligne que pour les colonnes non-Bordure.
 
static void afficher_separateur_ligne(int y) {
    for (int x = 0; x < 7; x++) {
        if (labyrinthe[y][x].Categorie_Carte == Bordure)
            printf("       ");
        else
            printf("+------");
    }
    printf("+\n");
}


//  AFFICHAGE DU PANNEAU JOUEURS (colonne de droite)
// Chaque appel affiche UNE ligne du panneau.
 // On appelle cette fonction en meme temps qu'on affiche
//  les rangees du plateau pour aligner les deux colonnes.



// afficher_panneau_joueur_ligne()
// Affiche la ligne numero `ligne` du panneau joueurs.
// Le panneau fait (nb_joueurs * 4 + 2) lignes :
//  - 1 ligne titre
//   - pour chaque joueur : nom, classe, arme, nb_coffre
//   - 1 ligne vide de separation
 
static void afficher_panneau_joueur_ligne(aventurier joueurs[], int nb_joueurs,
      int nb_tours, int ligne) {
    // Calcul du nombre total de lignes du panneau joueurs 
    int lignes_par_joueur = 4; // nom, classe, arme active, coffres 
    int total_lignes = 1 + nb_joueurs * (lignes_par_joueur + 1);

    if (ligne == 0) {
        printf("  JOUEURS (tour %d)", nb_tours);
        return;
    }

    int l = ligne - 1; 

    // ligne relative dans la liste des joueurs           
    int bloc = lignes_par_joueur + 1; 
// taille d'un bloc joueur (infos + ligne vide) 
    int j = l / bloc;
    int sous_ligne = l % bloc;

    if (j >= nb_joueurs) return; 
// plus de joueur a afficher 

    aventurier *av = &joueurs[j];
    switch (sous_ligne) {
        case 0:
            // Nom du joueur avec son symbole 
            printf("  [%c] %s",
                   LETTRE_CLASSE[av->classe_joueur],
                   av->joueur_qui_controle ? av->joueur_qui_controle->nom : "???");
            break;
        case 1:
            printf("      Classe : %s", NOM_CLASSE[av->classe_joueur]);
            break;
        case 2:
            printf("      Arme   : %s", NOM_ARME_BASE[av->arme_active]);
            break;
        case 3:
            printf("      Coffres: %d  Pos:(%d,%d)",
                   av->nb_coffre, av->a.x, av->a.y);
            break;
        case 4:
            printf("  "); // ligne vide entre deux joueurs 
            break;
        default:
            break;
    }
}

// AFFICHAGE DU LOG 

static void afficher_log(void) {
    printf("\n  --- Dernieres actions ---\n");
    if (log_jeu.nb == 0) {
        printf("  (aucune action pour le moment)\n");
        return;
    }
    for (int i = 0; i < log_jeu.nb; i++) {
        printf("  > %s\n", log_jeu.lignes[i]);
    }
}

/* =========================================================
 *  FONCTION PRINCIPALE : afficher_jeu()
 *
 *  Efface le terminal, affiche :
 *    - le titre et le temps ecoule
 *    - le plateau 7x7 avec les joueurs
 *    - le panneau joueurs sur la droite (aligne)
 *    - le log des evenements en dessous
 *
 *  Parametres :
 *    joueurs    : tableau des aventuriers
 *    nb_joueurs : nombre de joueurs actifs
 *    nb_tours   : numero du tour actuel
 *    temps_s    : temps ecoule en secondes depuis le debut
 * ========================================================= */

// PARTIE ZIAD 

void afficher_jeu(aventurier joueurs[], int nb_joueurs, int nb_tours, int temps_s) {


   // On efface le terminal pour rafraichir l'ecran 
    printf("\033[H\033[2J");
    fflush(stdout);

    // pour afficher le temps de la partie 
    int mm = temps_s / 60;
    int ss = temps_s % 60;
    printf("=== MEMO-RPG === Tour : %d   Temps : %02d:%02d\n\n", nb_tours, mm, ss);


    /*
     * Affichage cote a cote :
     *   plateau (7 colonnes x 7 lignes) | panneau joueurs
     *
     * On parcourt les lignes du plateau (y de 0 a 6).
     * A chaque rangee on affiche aussi la ligne correspondante
     * du panneau joueurs.
     *
     * Chaque rangee = 1 ligne separateur + 1 ligne de cases.
     * Total lignes d'affichage = 7 * 2 + 1 = 15 lignes.
     * Le panneau joueurs occupe au plus 15 lignes aussi.
     */

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



//  AFFICHAGE FIN DE PARTIE
 
// Revele tout le plateau et affiche le gagnant.

void afficher_fin_partie(aventurier joueurs[], int nb_joueurs,
                         int nb_tours, int temps_s,
                         int idx_gagnant) {

// Revele toutes les cartes 
    for (int y = 1; y <= 5; y++)
        for (int x = 1; x <= 5; x++)
            labyrinthe[y][x].Etat_carte = 1;

// Affiche le plateau final 

    afficher_jeu(joueurs, nb_joueurs, nb_tours, temps_s);

    printf("========================================\n");
    if (idx_gagnant >= 0 && joueurs[idx_gagnant].joueur_qui_controle != NULL) {
        printf("  VICTOIRE de %s (%s) !\n",
               joueurs[idx_gagnant].joueur_qui_controle->nom,
               NOM_CLASSE[joueurs[idx_gagnant].classe_joueur]);
    } else {
        printf("  Partie terminee - aucun vainqueur.\n");
    }
    printf("  Duree : %02d:%02d  |  Tours joues : %d\n",
           temps_s / 60, temps_s % 60, nb_tours);
    printf("========================================\n\n");
}

/* =========================================================
 *  AFFICHAGE STATISTIQUES DES JOUEURS (stats longue duree)
 * ========================================================= */
void afficher_scores(void) {
    extern int nb_joueurs_enregistres;

    printf("\033[2J\033[H");
    printf("========================================\n");
    printf("           STATISTIQUES DES JOUEURS                 \n");
    printf("========================================\n");
    printf("  %-20s  %7s  %9s\n", "Nom", "Parties", "Victoires");
    printf("  %-20s  %7s  %9s\n",
           "--------------------", "-------", "---------");

    if (nb_joueurs_enregistres == 0) {
        printf("  (aucun joueur enregistre)\n");
    } else {
        for (int i = 0; i < nb_joueurs_enregistres; i++) {
            printf("  %-20s  %7d  %9d\n",
                   Donnees_joueur[i].nom,
                   Donnees_joueur[i].parties_jouees,
                   Donnees_joueur[i].victoires);
        }
    }

    printf("========================================\n\n");
}

