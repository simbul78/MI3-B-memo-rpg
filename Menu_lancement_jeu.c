#include "fichier.h"
#include "donnees.h"

int main(){
    int p;
    for(int i=0;i<7;i++){
        labyrinthe[0][i].Categorie_Carte = Bordure;
        labyrinthe[6][i].Categorie_Carte = Bordure;
        labyrinthe[i][6].Categorie_Carte = Bordure;
        labyrinthe[i][0].Categorie_Carte = Bordure;
    }
    do{
    printf("joueurs, choisissez votre case de départs (1 à 5)");
    scanf("%d",&p);
    if(p<1 || p>5){
        printf("ERREUR ! Le numéro de la case de départs est compris entre 1 et 5 !");

    }
    }while(p<1 || p>5);
    switch(p){
        case 1 : ;
        

        case 2 : ;


        case 3 : ;


        case 4 : ;


        case 5 : ;


    }

}