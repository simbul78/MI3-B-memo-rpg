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
        Basilics,Zombies,Trolls,Harpies
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
    armesAntiques Arme_legendaires;
    coordonnees a;
    ProfilJoueur *joueur_qui_controle;
    
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
extern Carte labyrinthe[7][7];
extern ProfilJoueur Donnees_joueur[100];
#endif