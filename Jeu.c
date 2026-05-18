#include "projet.h"
#include "fichier.h"
void deplacer_joueur(aventurier *joueur,int numero_joueur,int count,char direction){
    if(count == 1){
        printf("Pour le premier tour vous rentrez dans le labyrinthe en avancant tout droit\n");
        switch(numero_joueur) {
            case 0 :   
                joueur->a.x++;
                break;
            case 1 :   
                joueur->a.y--;
                break;
            case 2 :   
                joueur->a.x--;
                break;
            case 3 :   
                joueur->a.y++;
                break;
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
void combattre_monstre(aventurier *joueur,Carte monstre){
    if(monstre.type_monstre == 0){
        printf("C'est un Basilic !\n");
        switch (joueur->arme_active)
        {
        case 0:
            printf("Vous avez battu le Basilic !\n");
            break;
        default:
            printf("Vous avez perdu contre le Basilic!\n");
            joueur->vie_joueur = 0;
            break;
        }
    }
    else if(monstre.type_monstre == 1){
        printf("C'est un Zombie !\n");
        switch (joueur->arme_active)
        {
        case 1:
            printf("Vous avez battu le Zombie!\n");
            break;
        default:
            printf("Vous avez perdu contre le Zombie!\n");
            joueur->vie_joueur = 0;
            break;
        }
    }
    else if(monstre.type_monstre == 2){
        printf("C'est un Troll !");
        switch (joueur->arme_active)
        {
        case 2:
            printf("Vous avez battu le Troll!\n");
            break;
        case 3:
            printf("Vous avez perdu contre le Troll !\n");
            joueur->vie_joueur = 0;
            break;
        default:
            printf("Vous avez perdu contre le Troll !\n");
            joueur->vie_joueur = 0;
            break;
        }
    }
    else{
        printf("C'est une Harpie !");
        switch (joueur->arme_active)
        {
        case 3:
            printf("Vous avez battu la Harpie !\n");
            break;
        default:
            printf("Vous avez perdu contre la Harpie !\n");
            joueur->vie_joueur = 0;
            break;
        }
    }
}
void arme_legendaire(aventurier *joueur,Carte arme_leg){
    if(arme_leg.Arme_legendaire== 0){
        printf("Vous trouvez l’épée de feu\n");
        switch(joueur->classe_joueur){
            case 0 : 
                    if(joueur->nb_coffre ==0){
                        printf("C'est exactement ce que vous chercher ! Vous la prenez donc et continuer votre chemin\n");
                    }
                    joueur->booleen_arme_antique = 1;
                    break;
            default : 
                    printf("Malheureusement, ce n'est pas l'arme que vous chercher... Vous continuer alors votre chemin...\n");
                    break;

        }


    }
    else if(arme_leg.Arme_legendaire== 1){
        printf("Vous trouvez le baton de contrôle des familiers\n");
        switch(joueur->classe_joueur){
            case 1 :
                    if(joueur->nb_coffre ==0){
                        printf("C'est exactement ce que vous chercher ! Vous la prenez donc et continuer votre chemin\n");
                    }
                    joueur->booleen_arme_antique = 1;
                    break;
            default : 
                    printf("Malheureusement, ce n'est pas l'arme que vous chercher... Vous continuer alors votre chemin...\n");
                    break;

        }
        
    }
    else if(arme_leg.Arme_legendaire== 2){
        printf("Vous trouvez le grimoire interdit !\n");
        switch(joueur->classe_joueur){
            case 2 : 
                    if(joueur->nb_coffre ==0){
                        printf("C'est exactement ce que vous chercher ! Vous la prenez donc et continuer votre chemin\n");
                    }
                    joueur->booleen_arme_antique = 1;
                    break;
            default : 
                printf("Malheureusement, ce n'est pas l'arme que vous chercher... Vous continuer alors votre chemin...\n");
                break;
        }
        
    }
    else if(arme_leg.Arme_legendaire== 3){
        printf("Vous trouvez la dague de sommeil!\n");
        switch(joueur->classe_joueur){
            case 3 : 
                    if(joueur->nb_coffre ==0){
                        printf("C'est exactement ce que vous chercher ! Vous la prenez donc et continuer votre chemin\n");
                    }
                    joueur->booleen_arme_antique = 1;
                    break;
            default : 
                    printf("Malheureusement, ce n'est pas l'arme que vous chercher... Vous continuer alors votre chemin...\n");
                    break;

        }

        
    }




}
void partie(aventurier joueurs[],int nb_joueurs){
    int partie_termine= 0;
    int compteur_tours = 1;
    while(partie_termine == 0){
        time_t debut_manche = time(NULL);
        printf("Round %d \n",compteur_tours);
        for(int i=0;i<nb_joueurs;i++){
            for(int j = 1; j<6;j++){
                for(int y = 1; y<6; y++){
                    labyrinthe[j][y].Etat_carte = 0;
                }
            }   
            if(joueurs[i].vie_joueur == 0){
                printf(" %s ressuscite et revient a sa base !\n", joueurs[i].joueur_qui_controle->nom);
                joueurs[i].vie_joueur = 1;
                joueurs[i].booleen_arme_antique = 0;
                joueurs[i].nb_coffre= 0;
                if (i == 0)      { joueurs[i].a.x = 0; joueurs[i].a.y = 3; } // Joueur 1 : En haut
                else if (i == 1) { joueurs[i].a.x = 3; joueurs[i].a.y = 6; } // Joueur 2 : A droite
                else if (i == 2) { joueurs[i].a.x = 6; joueurs[i].a.y = 3; } // Joueur 3 : En bas
                else if (i == 3) { joueurs[i].a.x = 3; joueurs[i].a.y = 0; }
            }
            while(joueurs[i].vie_joueur ==1 ){
                int resultat_scanf;
                char choix_dir;
                printf("\nC'est au tour de %s !\n", joueurs[i].joueur_qui_controle->nom);
                if(joueurs[i].vie_joueur == 1){
                    // Pour rendre le code beaucoup plus lisible, on stocke x et y
                    int x = joueurs[i].a.x;
                    int y = joueurs[i].a.y;

                    // On regarde si la case en HAUT est bloquée (soit c'est le bord de la carte, soit elle est révélée)
                    // Le bouclier : "x - 1 < 0" protège le tableau. Si c'est vrai, l'ordi ne lit pas la suite !
                    int haut_bloque = (x - 1 < 0) || (labyrinthe[x - 1][y].Etat_carte == 1);

                    // On fait pareil pour le BAS (la limite est 6 car le labyrinthe est un [7][7])
                    int bas_bloque = (x + 1 > 6) || (labyrinthe[x + 1][y].Etat_carte == 1);

                    // Pareil pour la GAUCHE
                    int gauche_bloque = (y - 1 < 0) || (labyrinthe[x][y - 1].Etat_carte == 1);

                    // Pareil pour la DROITE
                    int droite_bloque = (y + 1 > 6) || (labyrinthe[x][y + 1].Etat_carte == 1);


                    // Et maintenant, le test final devient d'une simplicité absolue !
                    if (haut_bloque && bas_bloque && gauche_bloque && droite_bloque) {
                        printf("Vous etes piege ! Toutes les cartes autour de vous ont ete revelees ou sont des murs.\n");
                        joueurs[i].vie_joueur = 0; 
                    }
                    
                    do{
                        printf("De quel arme voulez vous vous équiper ? BouclierReflechissant(0),Torche(1),ArcLong(2),HacheEnPierre(3)\n");
                        resultat_scanf = scanf("%d",(int*)&joueurs[i].arme_active); //voir s'il est préférable d'entrer le nom entier de l'arme ou le numero

                        int c;
                        while ((c = getchar()) != '\n' && c != EOF) { }
                        if(resultat_scanf != 1 ||   joueurs[i].arme_active <0 || joueurs[i].arme_active>3 ) printf("Il n'ya que 4 armes !! Recommencez ! ");
                    }while(resultat_scanf != 1 ||   joueurs[i].arme_active <0 || joueurs[i].arme_active>3 );
                    printf("Position actuelle : (%d, %d)\n", joueurs[i].a.x, joueurs[i].a.y);
                    if (compteur_tours > 1) {
                        do{
                            printf("Vers quelle direction voulez vous aller ? (z/q/s/d) ?");
                            resultat_scanf = scanf(" %c", &choix_dir);
                            int c;
                            while ((c = getchar()) != '\n' && c != EOF) { };
                            if(resultat_scanf != 1 ||   (choix_dir != 'z' && choix_dir != 'q' && choix_dir != 's' && choix_dir != 'd')) printf("Erreur d'entrée ! Recommencez ! ");
                        }while(resultat_scanf != 1 ||   (choix_dir != 'z' && choix_dir != 'q' && choix_dir != 's' && choix_dir != 'd'));
                    } 
                    else {
                    // Si c'est le tour 1, on donne une valeur bidon à choix_dir
                    // car la fonction deplacer_joueur va forcer l'avancée de toute façon !
                        choix_dir = 'z'; 
                    }
                    do{
                        deplacer_joueur(&joueurs[i],i,compteur_tours,choix_dir);
                        if(labyrinthe[joueurs[i].a.x][joueurs[i].a.y].Etat_carte == 1) printf("Vous vous diriger deja vers une carte revele ! Recommencer ! \n");
                    }while(labyrinthe[joueurs[i].a.x][joueurs[i].a.y].Etat_carte == 1);
                    labyrinthe[joueurs[i].a.x][joueurs[i].a.y].Etat_carte = 1;
                    switch (labyrinthe[joueurs[i].a.x][joueurs[i].a.y].Categorie_Carte){
                        case 0 :
                            printf("Vous tomber sur un monstre !");
                            combattre_monstre(&joueurs[i],labyrinthe[joueurs[i].a.x][joueurs[i].a.y]);
                            break;
                        case 1 : 
                            arme_legendaire(&joueurs[i],labyrinthe[joueurs[i].a.x][joueurs[i].a.y]);
                            if(joueurs[i].booleen_arme_antique == 1 && joueurs[i].nb_coffre >= 1) {
                                printf("\n %s a trouve l'arme et possède deja un coffre ! VICTOIRE !\n", joueurs[i].joueur_qui_controle->nom);
                                return; // On quitte la fonction 'partie', le jeu s'arrête net.
                            }
                            
                            break;
                        case 2 : 
                            printf("Vous etes tombe sur un totem de transmutation ! Vous devez donc choisir la carte non revelee avec laquelle vous voulez echanger le totem \n");
                            int totem_x;
                            int totem_y;
                            do{
                                printf("quelle est la coordonnee x de la carte que vous voulez échanger avec le totem ?");
                                resultat_scanf = scanf("%d",&totem_x);
                                printf("quelle est la coordonnee y de la carte que vous voulez échanger avec le totem ?");
                                resultat_scanf = scanf("%d",&totem_y);
                                int c;
                                while ((c = getchar()) != '\n' && c != EOF) { };
                                if(totem_x <=0 || totem_x >=6) printf("Votre coordonnee x n'est pas valide ! \n");
                                if(totem_y <=0 || totem_y >=6) printf("Votre coordonnee y n'est pas valide ! \n");
                                if(labyrinthe[totem_x][totem_y].Etat_carte == 1) printf("La carte que vous vous voulez echanger est deja revele ! \n");
                            }while(totem_x <=0 || totem_x >=6 || totem_y <=0 || totem_y >=6 || labyrinthe[totem_x][totem_y].Etat_carte == 1);
                            labyrinthe[joueurs[i].a.x][joueurs[i].a.y].Categorie_Carte = labyrinthe[totem_x][totem_y].Categorie_Carte;
                            labyrinthe[totem_x][totem_y].Categorie_Carte = 2;
                            joueurs[i].vie_joueur = 0;
                            break;
                        case 3 : 
                            printf("SWOOSH ! Tu tombes sur un Portail mysterieux (pouvoir en construction) !\n");
                            //return;
                            break;       
                        case 4 :  
                            joueurs[i].nb_coffre++;
                            printf("C'est un trésor ! Vous l'ouvrez et prenez son contenu. Votre nb de coffre ouvert est a %d",joueurs[i].nb_coffre++);
                            if(joueurs[i].booleen_arme_antique == 1 && joueurs[i].nb_coffre >= 1) {
                                printf("\n %s a trouve l'arme et possède deja un coffre ! VICTOIRE !\n", joueurs[i].joueur_qui_controle->nom);
                                return; // On quitte la fonction 'partie', le jeu s'arrête net.
                            }
                            break;
                        case 5 :  
                            printf("\n la con de ta mere c une bordure");
                            break;
                        default:    
                            break;
                    }
                    
                    
                        
            }

        }
        if (partie_termine == 0) {
            time_t fin_manche = time(NULL);
            double temps_ecoule = difftime(fin_manche, debut_manche);
            
            // --- CONVERSION EN HH:MM:SS ---
            int total_secondes = (int)temps_ecoule;
            
            int heures = total_secondes / 3600;
            int minutes = (total_secondes % 3600) / 60;
            int secondes = total_secondes % 60;
            
            // L'astuce du "%02d" permet d'afficher un zéro devant si le chiffre est plus petit que 10 
            // (ex: 01:05:09 au lieu de 1:5:9)
            printf("\n Fin du Round %d. ⏱ Temps ecoule : %02d:%02d:%02d\n", 
                   compteur_tours, heures, minutes, secondes);
        compteur_tours ++;
    }
    for(int i=1;i<6;i++){
        for(int j=1;j<6;j++){
            labyrinthe[i][j].Etat_carte = 0;
        }
    }
    

    }
}
}

//detail de ce qu'il reste a faire dans ce fichier :
//   -Portail
//   -stat : nb de cases parcourues, nb de monstres tués, nb de victoires
// système de durée
//des variantes ??