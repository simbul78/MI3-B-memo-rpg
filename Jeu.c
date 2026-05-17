#include "projet.h"
#include "fichier.h"
void deplacer_joueur(aventurier *joueur,int numero_joueur,int count,char direction){
    if(count == 1){
        printf("Pour le premier tour vous rentrez dans le labyrinthe en avancant tout droit ");
        switch(numero_joueur) {
            case 0 : ;
    }
    }
    
    else{
        switch(numero_joueur) {
        case 0: // Part d'en haut (Regarde vers le bas)
            if (direction == 'z') joueur->a.x++;      // Avance (descend)
            else if (direction == 's') joueur->a.x--; // Recule (monte)
            else if (direction == 'q') joueur->a.y++; // Gauche relative
            else if (direction == 'd') joueur->a.y--; // Droite relative
            break;
            
        case 1: // Part de droite (Regarde vers la gauche)
            if (direction == 'z') joueur->a.y--;      // Avance (gauche)
            else if (direction == 's') joueur->a.y++; // Recule (droite)
            else if (direction == 'q') joueur->a.x++; // Gauche relative
            else if (direction == 'd') joueur->a.x--; // Droite relative
            break;
            
        case 2: // Part d'en bas (Regarde vers le haut)
            if (direction == 'z') joueur->a.x--;      // Avance (monte)
            else if (direction == 's') joueur->a.x++; // Recule (descend)
            else if (direction == 'q') joueur->a.y--; // Gauche relative
            else if (direction == 'd') joueur->a.y++; // Droite relative
            break;
            
        case 3: // Part de gauche (Regarde vers la droite)
            if (direction == 'z') joueur->a.y++;      // Avance (droite)
            else if (direction == 's') joueur->a.y--; // Recule (gauche)
            else if (direction == 'q') joueur->a.x--; // Gauche relative
            else if (direction == 'd') joueur->a.x++; // Droite relative
            break;
    }
    }


}
void partie(aventurier joueurs[],int nb_joueurs){
    int partie_termine= 0;
    int compteur_tours;
    while(partie_termine == 0){
        printf("Round %d \n",compteur_tours);
        for(int i=0;i<nb_joueurs;i++){
            if(joueurs[i].booléen_arme_antique ==1 && joueurs[i].nb_coffre >=1) partie_termine = 1;
            else{
                int resultat_scanf;
                char choix_dir;
                printf("\nC'est au tour de %s !\n", joueurs[i].joueur_qui_controle->nom);
                while(joueurs[i].vie_joueur = 0){

                
                    do{
                        printf("De quel arme voulez vous vous équiper ? BouclierReflechissant(0),Torche(1),ArcLong(2),HacheEnPierre(3)\n");
                        resultat_scanf = scanf("%d",joueurs[i].arme_active); //voir s'il est préférable d'entrer le nom entier de l'arme ou le numero

                        int c;
                        while ((c = getchar()) != '\n' && c != EOF) { }
                        if(resultat_scanf != 1 ||   joueurs[i].arme_active <0 || joueurs[i].arme_active>3 ) printf("Il n'ya que 4 armes !! Recommencez ! ");
                    }while(resultat_scanf != 1 ||   joueurs[i].arme_active <0 || joueurs[i].arme_active>3 );
                    printf("Position actuelle : (%d, %d)\n", joueurs[i].a.x, joueurs[i].a.y);
                    do{
                        printf("Vers quelle direction voulez vous aller ? (z/q/s/d) ?");
                        resultat_scanf = scanf(" %c", &choix_dir);
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF) { };
                        if(resultat_scanf != 1 ||   (choix_dir != 'z' && choix_dir != 'q' && choix_dir != 's' && choix_dir != 'd')) printf("Erreur d'entrée ! Recommencez ! ");
                        }while(resultat_scanf != 1 ||   (choix_dir != 'z' && choix_dir != 'q' && choix_dir != 's' && choix_dir != 'd'));
                    }
                    
                    deplacer_joueur(&joueurs[i],i,compteur_tours,choix_dir);
                    
                    
                        
                    }

            }

            compteur_tours ++;
        }
    }