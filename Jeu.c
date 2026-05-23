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
        log_ajouter("C'est un Basilic !");
        switch (joueur->arme_active)
        {
        case 0:
            log_ajouter("Vous avez battu le Basilic !");
            joueur->nb_monstres_tues++;
            break;
        default:
            log_ajouter("Vous avez perdu contre le Basilic!");
            joueur->vie_joueur = 0;
            break;
        }
    }
    else if(monstre.type_monstre == 1){
        log_ajouter("C'est un Zombie !");
        switch (joueur->arme_active)
        {
        case 1:
            log_ajouter("Vous avez battu le Zombie!");
            joueur->nb_monstres_tues++;
            break;
        default:
            log_ajouter("Vous avez perdu contre le Zombie!");
            joueur->vie_joueur = 0;
            break;
        }
    }
    else if(monstre.type_monstre == 2){
        log_ajouter("C'est un Troll !");
        switch (joueur->arme_active)
        {
        case 3:
            log_ajouter("Vous avez battu le Troll!");
            joueur->nb_monstres_tues++;
            break;
        default:
            log_ajouter("Vous avez perdu contre le Troll !");
            joueur->vie_joueur = 0;
            break;
        }
    }
    else{
        log_ajouter("C'est une Harpie !");
        switch (joueur->arme_active)
        {
        case 2:
            log_ajouter("Vous avez battu la Harpie !");
            joueur->nb_monstres_tues++;
            break;
        default:
            log_ajouter("Vous avez perdu contre la Harpie !");
            joueur->vie_joueur = 0;
            break;
        }
    }
}
void arme_legendaire(aventurier *joueur,Carte arme_leg){
    if(arme_leg.Arme_legendaire== 0){
        log_ajouter("Vous trouvez l’épée de feu");
        switch(joueur->classe_joueur){
            case 0 : 
                    if(joueur->nb_coffre ==0){
                        log_ajouter("C'est exactement ce que vous chercher ! Vous la prenez donc et continuer votre chemin");
                    }
                    joueur->booleen_arme_antique = 1;
                    break;
            default : 
                    log_ajouter("Malheureusement, ce n'est pas l'arme que vous chercher... Vous continuer alors votre chemin...");
                    break;

        }


    }
    else if(arme_leg.Arme_legendaire== 1){
        log_ajouter("Vous trouvez le baton de contrôle des familiers");
        switch(joueur->classe_joueur){
            case 1 :
                    if(joueur->nb_coffre ==0){
                        log_ajouter("C'est exactement ce que vous chercher ! Vous la prenez donc et continuer votre chemin");
                    }
                    joueur->booleen_arme_antique = 1;
                    break;
            default : 
                    log_ajouter("Malheureusement, ce n'est pas l'arme que vous chercher... Vous continuer alors votre chemin...");
                    break;

        }
        
    }
    else if(arme_leg.Arme_legendaire== 2){
        log_ajouter("Vous trouvez le grimoire interdit !");
        switch(joueur->classe_joueur){
            case 2 : 
                    if(joueur->nb_coffre ==0){
                        log_ajouter("C'est exactement ce que vous chercher ! Vous la prenez donc et continuer votre chemin");
                    }
                    joueur->booleen_arme_antique = 1;
                    break;
            default : 
                log_ajouter("Malheureusement, ce n'est pas l'arme que vous chercher... Vous continuer alors votre chemin...");
                break;
        }
        
    }
    else if(arme_leg.Arme_legendaire== 3){
        log_ajouter("Vous trouvez la dague de sommeil!");
        switch(joueur->classe_joueur){
            case 3 : 
                    if(joueur->nb_coffre ==0){
                        log_ajouter("C'est exactement ce que vous chercher ! Vous la prenez donc et continuer votre chemin");
                    }
                    joueur->booleen_arme_antique = 1;
                    break;
            default : 
                    log_ajouter("Malheureusement, ce n'est pas l'arme que vous chercher... Vous continuer alors votre chemin...");
                    break;

        }

        
    }




}
void partie(aventurier joueurs[],int nb_joueurs){
    for(int i=0;i<nb_joueurs;i++){
    joueurs[i].joueur_qui_controle->parties_jouees++;
    }
    int partie_termine= 0;
    int compteur_tours = 1;
    while(partie_termine == 0){
        time_t debut_manche = time(NULL);
        printf("Round %d \n",compteur_tours);
        for(int i=0;i<nb_joueurs;i++){  
            if(joueurs[i].vie_joueur == 0){
                log_ajouter(" %s ressuscite et revient a sa base !", joueurs[i].joueur_qui_controle->nom);
                joueurs[i].vie_joueur = 1;
                joueurs[i].booleen_arme_antique = 0;
                joueurs[i].nb_coffre= 0;
                for(int j = 1; j<6;j++){
                    for(int y = 1; y<6; y++){
                        labyrinthe[j][y].Etat_carte = 0;
                    }
                } 
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
                time_t temps_actuel = time(NULL);
                int temps_s = (int)difftime(temps_actuel, debut_manche);
                afficher_jeu(joueurs, nb_joueurs, compteur_tours, temps_s);
                log_ajouter("C'est au tour de %s !", joueurs[i].joueur_qui_controle->nom);
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

                    if (haut_bloque && bas_bloque && gauche_bloque && droite_bloque) {
                        log_ajouter("Vous etes piege ! Toutes les cartes autour de vous ont ete revelees ou sont des murs.");
                        joueurs[i].vie_joueur = 0; 
                    }
                    
                    do{
                        printf("De quel arme voulez vous vous équiper ? BouclierReflechissant(0),Torche(1),ArcLong(2),HacheEnPierre(3)");

                        resultat_scanf = scanf("%d",(int*)&joueurs[i].arme_active); //voir s'il est préférable d'entrer le nom entier de l'arme ou le numero

                        int c;
                        while ((c = getchar()) != '\n' && c != EOF) { }
                        if(resultat_scanf != 1 ||   joueurs[i].arme_active <0 || joueurs[i].arme_active>3 ) printf("Il n'ya que 4 armes !! Recommencez ! ");
                    }while(resultat_scanf != 1 ||   joueurs[i].arme_active <0 || joueurs[i].arme_active>3 );
                    printf("Position actuelle : (%d, %d)", joueurs[i].a.x, joueurs[i].a.y);
                    
                    // 1. On vérifie si le joueur est sur une des 4 bordures (sa base)
                    int mouvement_valide = 0;

                    do {
                        // 1. LE CHECKPOINT : On sauvegarde la position actuelle
                        int ancien_x = joueurs[i].a.x;
                        int ancien_y = joueurs[i].a.y;

                        // 2. On vérifie si on part de la base
                        int est_sur_la_bordure = (ancien_x == 0 || ancien_x == 6 || ancien_y == 0 || ancien_y == 6);

                        // 3. Demander la direction OU forcer la marche avant
                        if (!est_sur_la_bordure && joueurs[i].en_teleportation != 1) {
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
                        else if(!est_sur_la_bordure && joueurs[i].en_teleportation == 1){
                        	printf("\n Pour, rappel vous etes au portail, choississez donc les coordonnees de la carte(non revelee) que vous choisissez ! \n");
                        	do{
                        		printf("quelle est la coordonnee x de la carte ou vous voulez aller  ?");
                                resultat_scanf = scanf("%d",&joueurs[i].a.x);
                                printf("quelle est la coordonnee y de la carte ou vous voulez aller  ? ?");
                                resultat_scanf = scanf("%d",&joueurs[i].a.y);
                                int c;
                                while ((c = getchar()) != '\n' && c != EOF) { };
                                if(joueurs[i].a.x <=0 || joueurs[i].a.x >=6) printf("Votre coordonnee x n'est pas valide ! ");
                                if(joueurs[i].a.y <=0 || joueurs[i].a.y >=6) printf("Votre coordonnee y n'est pas valide ! ");
                                if(labyrinthe[joueurs[i].a.x][joueurs[i].a.y].Etat_carte == 1) printf("La carte que vous vous voulez echanger est deja revele ! \n");
                                
                        	
                        	
                        	}while(joueurs[i].a.x <=0 || joueurs[i].a.x >=6 || joueurs[i].a.y <=0 || joueurs[i].a.y >=6 || labyrinthe[joueurs[i].a.x][joueurs[i].a.y].Etat_carte == 1);
                        }
                        else {
                            printf("Vous rentrez dans le labyrinthe !");
                            // On force la touche absolue pour que le joueur aille vers le centre (x=3, y=3)
                            if (i == 0) choix_dir = 's';      // Joueur en Haut -> Force le Bas
                            else if (i == 1) choix_dir = 'q'; // Joueur à Droite -> Force la Gauche
                            else if (i == 2) choix_dir = 'z'; // Joueur en Bas -> Force le Haut
                            else if (i == 3) choix_dir = 'd'; // Joueur à Gauche -> Force la Droite
                        }

                        // 4. On bouge le joueur (sur le papier)
                        if(joueurs[i].en_teleportation != 1){ //le if permet de traiter les cas ou nous ne sommes pas sur un portail a la case précédente
                            deplacer_joueur(&joueurs[i], choix_dir);
			            }
                        // 5. L'INSPECTEUR DES COLLISIONS
                        // Est-ce qu'il essaie de retourner sur la bordure (x ou y égal à 0 ou 6) ?
                        if (joueurs[i].a.x <= 0 || joueurs[i].a.x >= 6 || joueurs[i].a.y <= 0 || joueurs[i].a.y >= 6) {
                            log_ajouter("Aie ! Vous vous cognez contre le mur exterieur du labyrinthe ! Recommencez.");
                            // ON ANNULE LE MOUVEMENT
                            joueurs[i].a.x = ancien_x;
                            joueurs[i].a.y = ancien_y;
                        } 
                        // Est-ce qu'il va sur une carte déjà retournée ?
                        else if (labyrinthe[joueurs[i].a.x][joueurs[i].a.y].Etat_carte == 1) {
                            log_ajouter("Vous vous dirigez vers une carte deja revelee ! Recommencez.");
                            // ON ANNULE LE MOUVEMENT
                            joueurs[i].a.x = ancien_x;
                            joueurs[i].a.y = ancien_y;
                        } 
                        // Si on arrive ici, c'est que le mouvement est légal !
                        else {
                            mouvement_valide = 1; // On valide, ce qui va casser la boucle
                        }

                    } while (mouvement_valide == 0);// On recommence tout si le mouvement a été annulé
                    joueurs[i].en_teleportation = 0; 
                    joueurs[i].nb_cases_parcourues++;
                    labyrinthe[joueurs[i].a.x][joueurs[i].a.y].Etat_carte = 1;
                    log_ajouter("Position actuelle : (%d, %d)", joueurs[i].a.x, joueurs[i].a.y);
                    switch (labyrinthe[joueurs[i].a.x][joueurs[i].a.y].Categorie_Carte){
                        case 0 :
                            log_ajouter("Vous tomber sur un monstre !");
                            combattre_monstre(&joueurs[i],labyrinthe[joueurs[i].a.x][joueurs[i].a.y]);
                            break;
                        case 1 : 
                            arme_legendaire(&joueurs[i],labyrinthe[joueurs[i].a.x][joueurs[i].a.y]);
                            if(joueurs[i].booleen_arme_antique == 1 && joueurs[i].nb_coffre >= 1) {
                                for(int r = 1; r < 6; r++) {
                                    for(int c = 1; c < 6; c++) {
                                        labyrinthe[r][c].Etat_carte = 1;
                                    }
                                }
    
                                // 2. On recalcule le temps final
                                time_t temps_actuel = time(NULL);
                                int temps_s = (int)difftime(temps_actuel, debut_manche);
    
                                // 3. On appelle la fonction d'affichage pour montrer le labyrinthe ouvert !
                                afficher_jeu(joueurs, nb_joueurs, compteur_tours, temps_s);
                                log_ajouter(" %s a trouve l'arme et possède deja un coffre ! VICTOIRE !", joueurs[i].joueur_qui_controle->nom);
                                joueurs[i].joueur_qui_controle->victoires ++;
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
                            for(int j = 1; j < 6; j++){
                                for(int y = 1; y < 6; y++){
                                    labyrinthe[j][y].Etat_carte = 0;
                                }
                            }
                            break;
                        case 3 : 
                            log_ajouter("SWOOSH ! Tu tombes sur un Portail mysterieux !");
                            joueurs[i].en_teleportation = 1;
                            break;       
                        case 4 :  
                            joueurs[i].nb_coffre++;
                            log_ajouter("C'est un trésor ! Vous l'ouvrez et prenez son contenu. Votre nb de coffre ouvert est a %d",joueurs[i].nb_coffre);
                            if(joueurs[i].booleen_arme_antique == 1 && joueurs[i].nb_coffre >= 1) {
                                for(int r = 1; r < 6; r++) {
                                    for(int c = 1; c < 6; c++) {
                                        labyrinthe[r][c].Etat_carte = 1;
                                    }
                                }
    
                                // 2. On recalcule le temps final
                                time_t temps_actuel = time(NULL);
                                int temps_s = (int)difftime(temps_actuel, debut_manche);
    
                                // 3. On appelle la fonction d'affichage pour montrer le labyrinthe ouvert !
                                afficher_jeu(joueurs, nb_joueurs, compteur_tours, temps_s);
                                log_ajouter(" %s a trouve l'arme et possède deja un coffre ! VICTOIRE !", joueurs[i].joueur_qui_controle->nom);
                                joueurs[i].joueur_qui_controle->victoires ++;
                                return; // On quitte la fonction 'partie', le jeu s'arrête net.
                            }
                            break;
                        default:    
                            break;
                    }
                    time_t t_pause = time(NULL);
                    afficher_jeu(joueurs, nb_joueurs, compteur_tours, (int)difftime(t_pause, debut_manche));
                    
                    printf("\nAction terminee. Appuyez sur [Entree] pour passer a la suite...");
                    int c_clear;
                    while ((c_clear = getchar()) != '\n' && c_clear != EOF) { }
                    getchar();
                    
                    
                        
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
            log_ajouter(" Fin du Round %d. ⏱ Temps ecoule : %02d:%02d:%02d", 
                   compteur_tours, heures, minutes, secondes);
        compteur_tours ++;
        }
    

    }
    
}

}

