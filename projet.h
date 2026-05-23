#ifndef donnees_h
#define donnees_h

typedef enum{
    guerrier,ranger,magicien,voleur
    
}classe;
typedef enum{
    BouclierReflechissant,Torche,ArcLong,HacheEnPierre
    
}armesDeBase;
typedef enum{
    EpeeDeFeu, BatonFamilliers, Grimoire5feuilles,DagueDuSommeil
    
}armesAntiques;
typedef enum{
        Basilic,Zombie,Troll,Harpie
}monstre;
typedef struct{
    int x;
    int y;
}coordonnees;

typedef struct{
    char nom[50]; 
    int parties_jouees;
    int victoires;
} ProfilJoueur;
typedef struct{
    classe classe_joueur;
    armesDeBase arme_active;
    int nb_coffre;
    int booleen_arme_antique;
    int en_teleportation;
    coordonnees a;
    ProfilJoueur *joueur_qui_controle;
    int vie_joueur;
    int nb_cases_parcourues;
    int nb_monstres_tues;
}aventurier;
typedef enum {
    Monstre,ArmeAntiques,Totem,Portail,Coffre,Bordure
}TypeCarte;
typedef struct{
        TypeCarte Categorie_Carte;
        monstre type_monstre;
        armesAntiques Arme_legendaire;
        int Etat_carte;
        
}Carte;
extern int p;
extern Carte labyrinthe[7][7];
extern ProfilJoueur Donnees_joueur[100];
extern int nb_joueurs_enregistres; 
int configurer_partie(aventurier joueurs[]);
void partie(aventurier joueurs[], int nb_joueurs);
#endif
