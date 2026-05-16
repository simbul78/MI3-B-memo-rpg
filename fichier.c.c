#include <stdio.h>
#include <string.h>
#include "fichier.h"

#define FICHIER_SAVE "sauvegarde_scores.dat"

/**
 * Ouvre le fichier en mode binaire lecture, remplit le tableau global,
 * puis ferme proprement le fichier.
 */
void charger_statistiques() {
    FILE* file = fopen(FICHIER_SAVE, "rb");
    nb_joueurs_enregistres = 0;

    // Si le fichier n'existe pas, on ne crash pas : on commence à 0 joueur
    if (file == NULL) {
        return;
    }

    // Lecture élément par élément dans la limite du tableau global (100)
    while (nb_joueurs_enregistres < 100 && 
           fread(&Donnees_joueur[nb_joueurs_enregistres], sizeof(ProfilJoueur), 1, file) == 1) {
        nb_joueurs_enregistres++;
    }

    fclose(file); // Fermeture obligatoire du fichier après lecture
}

/**
 * Ouvre le fichier en mode binaire écriture, enregistre les données à long terme,
 * puis ferme proprement le fichier.
 */
void sauvegarder_statistiques() {
    FILE* file = fopen(FICHIER_SAVE, "wb");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier pour sauvegarder.\n");
        return; // Gestion d'erreur robuste sans crash
    }

    // Écriture du tableau complet jusqu'au nombre exact de joueurs enregistrés
    fwrite(Donnees_joueur, sizeof(ProfilJoueur), nb_joueurs_enregistres, file);
    
    fclose(file); // Fermeture obligatoire du fichier après écriture
}

/**
 * Parcourt le tableau pour lier un joueur existant ou l'ajouter
 */
ProfilJoueur* obtenir_ou_creer_profil(const char* nom_recherche) {
    // 1. Recherche si le joueur a déjà un historique
    for (int i = 0; i < nb_joueurs_enregistres; i++) {
        if (strcmp(Donnees_joueur[i].nom, nom_recherche) == 0) {
            return &Donnees_joueur[i]; // Profil trouvé, on renvoie son adresse
        }
    }

    // 2. Si le joueur n'existe pas, on l'ajoute au tableau global
    if (nb_joueurs_enregistres < 100) {
        strncpy(Donnees_joueur[nb_joueurs_enregistres].nom, nom_recherche, 49);
        Donnees_joueur[nb_joueurs_enregistres].nom[49] = '\0'; // Sécurité chaîne
        Donnees_joueur[nb_joueurs_enregistres].parties_jouees = 0;
        Donnees_joueur[nb_joueurs_enregistres].victoires = 0;
        
        nb_joueurs_enregistres++;
        return &Donnees_joueur[nb_joueurs_enregistres - 1];
    }

    printf("Erreur : Tableau des profils de joueurs plein !\n");
    return NULL;
}