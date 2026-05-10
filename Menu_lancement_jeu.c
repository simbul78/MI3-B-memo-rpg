#include "fichier.h"
#include "donnees.h"
const char* noms_des_classes[] = {"Guerrier(re)", "Ranger", "Magicien(nes)", "Voleur(euse)"};
int main(){
    int p;
    int nb_joueurs;
    int Classe;
    aventurier joueurs[4];
    for(int i=0;i<7;i++){
        labyrinthe[0][i].Categorie_Carte = Bordure;
        labyrinthe[6][i].Categorie_Carte = Bordure;
        labyrinthe[i][6].Categorie_Carte = Bordure;
        labyrinthe[i][0].Categorie_Carte = Bordure;
    }
    do{
        printf("choisisez le nombre de joueur(max 4) !");
        scanf("%d",&nb_joueurs);
        if(nb_joueurs<1 || nb_joueurs>4){
        printf("ERREUR ! le nb de joueurs est compris entre 1 et 4 !");
        }
    }while(nb_joueurs <1  || nb_joueurs > 4);
    do{
        printf("joueurs, choisissez votre case de départs (1 à 5)");
        scanf("%d",&p);
        if(p<1 || p>5){
            printf("ERREUR ! Le numéro de la case de départs est compris entre 1 et 5 !");

        }
    }while(p<1 || p>5);
    for(int i = 0; i<nb_joueurs;i++){
        joueurs[i].joueur_qui_controle = &Donnees_joueur[i];
        printf("joueur %d, Quel est votre nom ?", i+1);
        scanf("%s",joueurs[i].joueur_qui_controle->nom); //voir plus tard comment rendre robuste
        do{
            printf("%s, choisissez votre classe d'aventuriers : 1/Guerrier 2/Ranger 3/Magicien 4/Voleur", joueurs[i].joueur_qui_controle->nom);
            scanf("%d",&Classe);
            if(Classe<1 || Classe>4){
                printf("ERREUR ! Mauvaise entrée ! Recommencer \n");
            }
        }while(Classe<1 || Classe>4);
        switch(Classe){
            case 1 : 
                joueurs[i].classe_joueur = guerrier;
                printf("vous êtes donc un(e) %s",noms_des_classes[Classe - 1]);
                break;
            case 2 : 
                joueurs[i].classe_joueur = ranger;
                printf("vous êtes donc un(e) %s",noms_des_classes[Classe - 1]);
                break;
            case 3 : 
                joueurs[i].classe_joueur = magicien;
                printf("vous êtes donc un(e) %s",noms_des_classes[Classe - 1]);
                break;
            case 4: 
                joueurs[i].classe_joueur = voleur;
                printf("vous êtes donc un(e) %s",noms_des_classes[Classe - 1]);
                break;

        }

        joueurs[i].nb_coffre =0;
        switch(i){
            case 1 : 
                joueurs[i].a.x = 0;
                joueurs[i].a.y = p;
                break;
            case 2 : 
                joueurs[i].a.x = p;
                joueurs[i].a.y = 6;
                break;
            case 3 : 
                joueurs[i].a.x = 6;
                joueurs[i].a.y = p;
                break;
            case 4 : 
                joueurs[i].a.x = p;
                joueurs[i].a.y = 0;
                break;

        }
        joueurs[i].joueur_qui_controle->parties_jouees = 0;
        joueurs[i].joueur_qui_controle->victoires = 0;

    }
    for(int i = 0; i<100;i++){
    printf("%s ;",Donnees_joueur[i].nom);
    }
    return 0;
}
