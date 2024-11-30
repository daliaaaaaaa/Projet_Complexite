// arbre_binaire.h
#ifndef ARBRE_BINAIRE_H
#define ARBRE_BINAIRE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Noeud {
    int cle;
    struct Noeud* fg;  // fils gauche
    struct Noeud* fd;  // fils droit
} Noeud;

// Fonction pour trouver le minimum dans un sous-arbre
Noeud* minimum(Noeud* noeud);

// Fonction pour supprimer un élément de l'arbre
void Suppression(int x, Noeud** racine);

// Fonction pour insérer un élément dans l'arbre
void insertion(Noeud** racine, int x);

// Fonction pour rechercher un élément dans l'arbre
Noeud* recherche(Noeud* racine, int x);
// Fonction menu
void menu_abr(Noeud** racine);
void mesurer_complexite(Noeud **racine);
void afficher_infixe(Noeud *racine) ;
void afficher_prefixe(Noeud *racine);
void afficher_postfixe(Noeud *racine);
#endif // ARBRE_BINAIRE_H
