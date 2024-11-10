// listbd.h
#ifndef LISTBD_H
#define LISTBD_H

#include <stdio.h>
#include <stdlib.h>

// Structure de la liste doublement chaînée
typedef struct Listbd {
    int info;
    struct Listbd* svt;
    struct Listbd* prc;
} Listbd;

// Fonction pour créer un nœud
Listbd* createNode(int info);

// Fonction pour insérer un élément en tête de liste
void insertAttete(Listbd** tete, int info);

// Fonction pour insérer un élément en fin de liste
void insertAtqueue(Listbd** tete, int info);

// Fonction pour afficher la liste dans l'ordre
void affiche_tete(Listbd* tete);

// Fonction pour afficher la liste dans l'ordre inverse
void affiche_queue(Listbd* queue);

// Fonction pour supprimer un élément de la liste
void supp_ele(Listbd** tete, int key);

// Fonction pour tester les opérations sur la liste doublement chaînée
void listbd_operations();

#endif // LISTBD_H
