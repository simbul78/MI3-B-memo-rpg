#include "fichier.h"
#include "donnees.h"

int main(){
    int p;
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