#ifndef donnees_h
#define donnees_h

// Dimensions du plateau 7x7 (dont les bordures)

#define NB_RANGEES   7
#define NB_COLONNES  7

//  ÉNUMÉRATIONS

// Les 4 classes de personnage jouables

typedef enum {
    guerrier, ranger, magicien, voleur
} classe;

// Les 4 armes de base choisies avant chaque déplacement
// + Aucune : état initial avant que le joueur choisisse

typedef enum {
    BouclierReflechissant,      // efficace contre les Basilics
    Torche,                    // efficace contre les Zombies
    ArcLong,                  // efficace contre les Harpies
    HacheEnPierre,           // efficace contre les Trolls
    Aucune                  // état par défaut (pas encore choisi)
} armesDeBase;

// Les 4 armes antiques cachées dans le labyrinthe
// Chaque aventurier en recherche une précise pour gagner

typedef enum {
    EpeeDeFeu,             // recherchée par le Guerrier
    BatonFamilliers,      // recherchée par le Ranger
    Grimoire5feuilles,   // recherché par le Magicien
    DagueDuSommeil      // recherchée par le Voleur
} armesAntiques;

// Les 4 types de monstres présents dans le labyrinthe

typedef enum {
    Basilic,     // vaincu par le Bouclier Réfléchissant
    Zombie,     // vaincu par la Torche
    Troll,     // vaincu par la Hache
    Harpie    // vaincue par l'Arc Long
} monstre;

//  STRUCTURES

// Position d'un joueur sur le plateau (ligne, colonne)

typedef struct {
    int x; // ligne (0 à 6)
    int y; // colonne (0 à 6)
} coordonnees;

// Profil long-terme d'un joueur

typedef struct {
    char nom[50];            // nom saisi par le joueur au début de la partie
    int  parties_jouees;    // nombre total de parties jouées sur cette machine
    int  victoires;        // nombre total de victoires
} ProfilJoueur;

// État complet d'un aventurier pendant une partie

typedef struct {
    classe       classe_joueur;                     // guerrier / ranger / magicien / voleur
    armesDeBase  arme_active;                      // arme choisie ce tour avant de se déplacer
    int          nb_coffre;                       // nombre de coffres trouvés (besoin d'au moins 1 pour gagner)
    int          booleen_arme_antique;           // 1 si l'aventurier a trouvé son arme antique, 0 sinon
    int          en_teleportation;              // 1 si le joueur vient de passer par un portail (téléportation libre)
    coordonnees  a;                            // position actuelle sur le plateau (x, y)
    ProfilJoueur *joueur_qui_controle;        // pointeur vers le profil du joueur (nom, stats)
    int          vie_joueur;                 // 1 = vivant, 0 = vaincu par un monstre
    int          nb_cases_parcourues;       // nombre de cases révélées par ce joueur (pour les stats)
    int          nb_monstres_tues;         // nombre de monstres vaincus par ce joueur (pour les stats)
} aventurier;

//  TYPE D'UNE CASE DU PLATEAU

// Ce que peut contenir une case du labyrinthe 7x7

typedef enum {
    Monstre,              // un des 4 types de monstres
    ArmeAntiques,        // une des 4 armes légendaires
    Totem,              // totem de transmutation : échange deux cases et fin de tour
    Portail,           // portail magique : prochaine case libre au choix
    Coffre,           // coffre au trésor : nécessaire pour la victoire
    Bordure          // case hors du labyrinthe (les 24 cases autour du 5x5 central)
} TypeCarte;

// Représente une case du plateau 7x7

typedef struct {
    TypeCarte    Categorie_Carte;       // type de la case (Monstre, Coffre, Bordure...)
    monstre      type_monstre;         // type du monstre si Categorie_Carte == Monstre
    armesAntiques Arme_legendaire;    // arme présente si Categorie_Carte == ArmeAntiques
    int          Etat_carte;         // 0 = cachée [?], 1 = révélée
} Carte;

//  VARIABLES GLOBALES PARTAGÉES 

extern int p;                                // position de départ choisie par les joueurs (1 à 5)
extern Carte labyrinthe[7][7];              // plateau de jeu complet 7x7
extern ProfilJoueur Donnees_joueur[100];   // tableau des 100 profils joueurs enregistrés
extern int nb_joueurs_enregistres;        // nombre de profils actuellement enregistrés

//  PROTOTYPES DES FONCTIONS PRINCIPALES

int  configurer_partie(aventurier joueurs[]);         // prépare la partie : noms, classes, plateau
void partie(aventurier joueurs[], int nb_joueurs);   // boucle principale du jeu

void log_ajouter(const char *message);                                                  // ajoute un message dans le journal d'événements
void afficher_jeu(aventurier joueurs[], int nb_joueurs, int nb_tours, int temps_s);    // rafraîchit l'écran
void afficher_scores(void);                                                           // affiche les statistiques long-terme des joueurs

#endif

