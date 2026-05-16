#ifndef FICHIER_H
#define FICHIER_H

#include "donnees.h"

// Charge les profils depuis le fichier au démarrage du jeu
void charger_statistiques();

// Sauvegarde le tableau des profils dans le fichier en fin de partie
void sauvegarder_statistiques();

// Cherche si le nom existe déjà (renvoie son profil) ou le crée s'il est nouveau
ProfilJoueur* obtenir_ou_creer_profil(const char* nom_recherche);

#endif