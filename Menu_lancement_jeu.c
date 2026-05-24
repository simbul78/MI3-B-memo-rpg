#include "fichier.h"
#include "projet.h"
#include "fichier_sauvg.h"
const char* noms_des_classes[] = {"Guerrier(re)", "Ranger", "Magicien(nes)", "Voleur(euse)"};
const char* noms_monstres[] = {"Basilic", "Zombie", "Troll", "Harpie"};
const char* noms_armes[] = {"Epee de Feu", "Baton des Familiers", "Grimoire a 5 feuilles", "Dague du Sommeil"};
int choix_case(){
	int resultat_scanf;
	do{
        	printf("joueurs, choisissez votre case de départs (1 à 5)");
        	resultat_scanf = scanf("%d",&p);
        	int c;
        	while ((c = getchar()) != '\n' && c != EOF) { }
        	if(resultat_scanf != 1 || p<1 || p>5){
            		printf("ERREUR ! Le numéro de la case de départs est compris entre 1 et 5 !");

        	}
        }while(p<1 || p>5);
        return p;
}
	
int configurer_partie(aventurier joueurs[]){
    int nb_joueurs;
    int Classe;
    int resultat_scanf;
    for(int i=0;i<4;i++){
        joueurs[i].nb_coffre = 0;
        joueurs[i].a.x = 0;
        joueurs[i].a.y = 0;
        joueurs[i].joueur_qui_controle = NULL;
        joueurs[i].booleen_arme_antique =0;
        joueurs[i].vie_joueur = 1;
        joueurs[i].en_teleportation = 0;
        joueurs[i].nb_monstres_tues = 0;
        joueurs[i].nb_cases_parcourues = 0;
    }
    for(int i=0;i<7;i++){
        labyrinthe[0][i].Categorie_Carte = Bordure;
        labyrinthe[6][i].Categorie_Carte = Bordure;
        labyrinthe[i][6].Categorie_Carte = Bordure;
        labyrinthe[i][0].Categorie_Carte = Bordure;
    }
    do{
        printf("choisisez le nombre de joueur(max 4) !");
        resultat_scanf = scanf("%d",&nb_joueurs);
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
        if(resultat_scanf != 1 || nb_joueurs<1 || nb_joueurs>4){
        printf("ERREUR ! le nb de joueurs est compris entre 1 et 4 !");
        }
    }while(nb_joueurs <1  || nb_joueurs > 4);
    
    p = choix_case();
    for(int i = 0; i<nb_joueurs;i++){
        char nom_saisi[50];
        printf("joueur %d, Quel est votre nom ?", i+1);
        scanf("%s",nom_saisi); //voir plus tard comment rendre robuste
        joueurs[i].joueur_qui_controle = obtenir_ou_creer_profil(nom_saisi);
        do{
            printf("%s, choisissez votre classe d'aventurier : 1/Guerrier 2/Ranger 3/Magicien 4/Voleur\n", joueurs[i].joueur_qui_controle->nom);
    
            // scanf renvoie 1 s'il a réussi à lire un entier, 0 sinon
            resultat_scanf = scanf("%d", &Classe); 
    
            // LA CHASSE D'EAU : On vide la mémoire du clavier (buffer)
            // On lit tous les caractères restants jusqu'à trouver la touche "Entrée" (\n)
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { } 

    // On vérifie deux choses : si ce n'est PAS un chiffre OU si c'est hors limites
        if(resultat_scanf != 1 || Classe < 1 || Classe > 4) {
        printf("ERREUR ! Veuillez entrer un CHIFFRE valide entre 1 et 4 ! Recommencez.\n\n");
        Classe = 0; // On force la classe à 0 pour être sûr que le while() nous fasse recommencer
    }
        }while(Classe<1 || Classe>4);
        switch(Classe){
            case 1 : 
                joueurs[i].classe_joueur = guerrier;
                printf("vous êtes donc un(e) %s\n",noms_des_classes[Classe - 1]);
                break;
            case 2 : 
                joueurs[i].classe_joueur = ranger;
                printf("vous êtes donc un(e) %s\n",noms_des_classes[Classe - 1]);
                break;
            case 3 : 
                joueurs[i].classe_joueur = magicien;
                printf("vous êtes donc un(e) %s\n",noms_des_classes[Classe - 1]);
                break;
            case 4: 
                joueurs[i].classe_joueur = voleur;
                printf("vous êtes donc un(e) %s\n",noms_des_classes[Classe - 1]);
                break;

        }

        joueurs[i].nb_coffre = 0;
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

    //fonction QUI REMPLI LE PLATEAU
    printf("\n \n Plateau : \n");
    int nb_monstres = 16;
    int nb_arme_antiques = 4;
    int EpeeDeFeu = 1, BatonFamilliers =1, Grimoire5feuilles=1 ,DagueDuSommeil =1;
    int nb_totems = 2;
    int nb_coffre = 2;
    int nb_portail = 1;
    for(int i = 1; i<6;i++){
        for(int y = 1; y<6; y++){
            labyrinthe[i][y].Etat_carte = 0;
            int tirage_valide = 0;
            int tirage_valide_armes =0;
            do{
                labyrinthe[i][y].Categorie_Carte = rand()%5;
                switch(labyrinthe[i][y].Categorie_Carte){
                    case Monstre : 
                        if (nb_monstres > 0) {
                            nb_monstres--;
                            tirage_valide = 1; // Indispensable pour sortir de la boucle !
                        }
                        break;
                    case ArmeAntiques : 
                        if (nb_arme_antiques > 0) { 
                            nb_arme_antiques--; 
                            tirage_valide = 1; 
                        }
                        break;
                    case Totem : 
                        if (nb_totems > 0) { 
                            nb_totems--; 
                            tirage_valide = 1; 
                        }
                        break;
                    case Portail : 
                        if (nb_portail > 0) { 
                            nb_portail--; 
                            tirage_valide = 1; 
                        }
                        break;
                    case Coffre : 
                        if (nb_coffre > 0) { 
                            nb_coffre--; 
                            tirage_valide = 1; 
                        }
                        break;
                    case Bordure : // <--- AJOUTE ÇA
                            break; 
                }
            }while(tirage_valide == 0);
            if(labyrinthe[i][y].Categorie_Carte == Monstre){
                labyrinthe[i][y].type_monstre = rand() % 4;
                printf("%s ;", noms_monstres[labyrinthe[i][y].type_monstre]);
            }
            else if(labyrinthe[i][y].Categorie_Carte == ArmeAntiques){
                do{
                labyrinthe[i][y].Arme_legendaire = rand()%4;
                switch(labyrinthe[i][y].Arme_legendaire){
                    case 0 : 
                        if (EpeeDeFeu > 0) {
                            EpeeDeFeu--;
                            tirage_valide_armes = 1; // Indispensable pour sortir de la boucle !
                            printf("Epee de feu ;");
                        }
                        break;
                    case 1 : 
                        if (BatonFamilliers > 0) { 
                            BatonFamilliers--; 
                            tirage_valide_armes = 1;
                            printf("Baton des fammilliers ;"); 
                        }
                        break;
                    case 2 : 
                        if (Grimoire5feuilles > 0) { 
                            Grimoire5feuilles--; 
                            tirage_valide_armes = 1;
                            printf("Grimoire 5 feuilles ;");
                        }
                        break;
                    case 3 : 
                        if (DagueDuSommeil > 0) { 
                            
                            DagueDuSommeil--; 
                            tirage_valide_armes = 1;
                            printf("Dague du sommeil ;");
                        }
                        break;
                    }
                }while(tirage_valide_armes == 0);
            }
            else if(labyrinthe[i][y].Categorie_Carte == Totem){
                printf("Totem ;");
            }
            else if(labyrinthe[i][y].Categorie_Carte == Portail){
                printf("Portail ;");
            }
            else if(labyrinthe[i][y].Categorie_Carte == Coffre){
                printf("Coffre ;");
            }
        }    
        printf("\n");
        
    }
    return nb_joueurs;
}
