// Gestion de tout l'affichage du jeu Memo-RPG
 //Affichage : plateau 7x7, panneau joueurs, log des evenements
 

#include <stdio.h>
#include <string.h>
#include "projet-h.c"   // structures aventurier, Carte, labyrinthe... 


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
                case Basilics: return 'B';
                case Zombies:  return 'Z';
                case Trolls:   return 'T';
                case Harpies:  return 'H';
                default:       return 'M';
            }
        case ArmeAntiques: return 'A';
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

/* =========================================================
 *  AFFICHAGE DU LOG D'EVENEMENTS
 * ========================================================= */

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
