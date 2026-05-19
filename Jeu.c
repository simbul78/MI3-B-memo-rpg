#include "projet.h"
#include "fichier.h"

void deplacer_joueur(aventurier *joueur, char direction){
    // Les contrôles absolus : on se repère uniquement par rapport à l'écran !
    if (direction == 'z') joueur->a.x--;      // Haut (On remonte vers la ligne 0)
    else if (direction == 's') joueur->a.x++; // Bas (On descend vers la ligne 6)
    else if (direction == 'q') joueur->a.y--; // Gauche (On va vers la colonne 0)
    else if (direction == 'd') joueur->a.y++; // Droite (On va vers la colonne 6)
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
                switch(i){
            case 0 : 
                joueurs[i].a.x = 0;
                joueurs[i].a.y = p;
                break;
            case 1 : 
                joueurs[i].a.x = p;
                joueurs[i].a.y = 6;
                break;
            case 2 : 
                joueurs[i].a.x = 6;
                joueurs[i].a.y = p;
                break;
            case 3 : 
                joueurs[i].a.x = p;
                joueurs[i].a.y = 0;
                break;

        }
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
                    
                    // 1. On vérifie si le joueur est sur une des 4 bordures (sa base)
                    int mouvement_valide = 0;

                    do {
                        // 1. LE CHECKPOINT : On sauvegarde la position actuelle
                        int ancien_x = joueurs[i].a.x;
                        int ancien_y = joueurs[i].a.y;

                        // 2. On vérifie si on part de la base
                        int est_sur_la_bordure = (ancien_x == 0 || ancien_x == 6 || ancien_y == 0 || ancien_y == 6);

                        // 3. Demander la direction OU forcer la marche avant
                        if (!est_sur_la_bordure && (labyrinthe[x][y].Categorie_Carte != Portail)) {
                            do {
                                printf("Vers quelle direction voulez vous aller ? (z/q/s/d) ? ");
                                resultat_scanf = scanf(" %c", &choix_dir);
                                int c;
                                while ((c = getchar()) != '\n' && c != EOF) { };
                                if (resultat_scanf != 1 || (choix_dir != 'z' && choix_dir != 'q' && choix_dir != 's' && choix_dir != 'd')) {
                                    printf("Erreur d'entree ! Recommencez ! ");
                                }
                            } while (resultat_scanf != 1 || (choix_dir != 'z' && choix_dir != 'q' && choix_dir != 's' && choix_dir != 'd'));
                        }
                        else if(!est_sur_la_bordure && (labyrinthe[x][y].Categorie_Carte == Portail)){
                        	printf("\n Pour, rappel vous etes au portail, choississez donc les coordonnees de la carte(non revelee) que vous choisissez ! \n");
                        	choix_dir = 'n';
                        	do{
                        		printf("quelle est la coordonnee x de la carte ou vous voulez aller  ?");
                                resultat_scanf = scanf("%d",&joueurs[i].a.x);
                                printf("quelle est la coordonnee y de la carte ou vous voulez aller  ? ?");
                                resultat_scanf = scanf("%d",&joueurs[i].a.y);
                                int c;
                                while ((c = getchar()) != '\n' && c != EOF) { };
                                if(joueurs[i].a.x <=0 || joueurs[i].a.x >=6) printf("Votre coordonnee x n'est pas valide ! \n");
                                if(joueurs[i].a.y <=0 || joueurs[i].a.y >=6) printf("Votre coordonnee y n'est pas valide ! \n");
                                if(labyrinthe[joueurs[i].a.x][joueurs[i].a.y].Etat_carte == 1) printf("La carte que vous vous voulez echanger est deja revele ! \n");
                        	
                        	
                        	
                        	}while(joueurs[i].a.x <=0 || joueurs[i].a.x >=6 || joueurs[i].a.y <=0 || joueurs[i].a.y >=6 || labyrinthe[joueurs[i].a.x][joueurs[i].a.y].Etat_carte == 1);
                        }
                        else {
                            printf("Vous rentrez dans le labyrinthe !\n");
                            // On force la touche absolue pour que le joueur aille vers le centre (x=3, y=3)
                            if (i == 0) choix_dir = 's';      // Joueur en Haut -> Force le Bas
                            else if (i == 1) choix_dir = 'q'; // Joueur à Droite -> Force la Gauche
                            else if (i == 2) choix_dir = 'z'; // Joueur en Bas -> Force le Haut
                            else if (i == 3) choix_dir = 'd'; // Joueur à Gauche -> Force la Droite
                        }

                        // 4. On bouge le joueur (sur le papier)
                        if(choix_dir !='n'){ //le if permet de traiter les cas ou nous ne sommes pas sur un portail a la case précédente
                        deplacer_joueur(&joueurs[i], choix_dir);
			}
                        // 5. L'INSPECTEUR DES COLLISIONS
                        // Est-ce qu'il essaie de retourner sur la bordure (x ou y égal à 0 ou 6) ?
                        if (joueurs[i].a.x <= 0 || joueurs[i].a.x >= 6 || joueurs[i].a.y <= 0 || joueurs[i].a.y >= 6) {
                            printf("Aie ! Vous vous cognez contre le mur exterieur du labyrinthe ! Recommencez.\n");
                            // ON ANNULE LE MOUVEMENT
                            joueurs[i].a.x = ancien_x;
                            joueurs[i].a.y = ancien_y;
                        } 
                        // Est-ce qu'il va sur une carte déjà retournée ?
                        else if (labyrinthe[joueurs[i].a.x][joueurs[i].a.y].Etat_carte == 1) {
                            printf("Vous vous dirigez vers une carte deja revelee ! Recommencez.\n");
                            // ON ANNULE LE MOUVEMENT
                            joueurs[i].a.x = ancien_x;
                            joueurs[i].a.y = ancien_y;
                        } 
                        // Si on arrive ici, c'est que le mouvement est légal !
                        else {
                            mouvement_valide = 1; // On valide, ce qui va casser la boucle
                        }

                    } while (mouvement_valide == 0); // On recommence tout si le mouvement a été annulé
                    labyrinthe[joueurs[i].a.x][joueurs[i].a.y].Etat_carte = 1;
                    printf("Position actuelle : (%d, %d)\n", joueurs[i].a.x, joueurs[i].a.y);
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
                            printf("C'est un trésor ! Vous l'ouvrez et prenez son contenu. Votre nb de coffre ouvert est a %d",joueurs[i].nb_coffre);
                            if(joueurs[i].booleen_arme_antique == 1 && joueurs[i].nb_coffre >= 1) {
                                printf("\n %s a trouve l'arme et possède deja un coffre ! VICTOIRE !\n", joueurs[i].joueur_qui_controle->nom);
                                return; // On quitte la fonction 'partie', le jeu s'arrête net.
                            }
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


//detail de ce qu'il reste a faire dans ce fichier :
//   -Portail
// -chrono
//   -stat : nb de cases parcourues, nb de monstres tués, nb de victoires
//des variantes ??
