#ifndef LISTBD_H
#define LISTBD_H

#include <stdbool.h>

// Définition de la structure Node pour une liste chaînée bidirectionnelle
typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

// Déclarations des fonctions pour la gestion de la liste chaînée bidirectionnelle

// Fonction pour insérer un élément dans la liste triée
void insert(Node **head, int value);

// Fonction pour supprimer un nœud de la liste
void delete_node(Node **head, int key);

// Fonction pour supprimer un élément par sa clé
void removeKey(Node **head, int key);

// Fonction pour rechercher un élément dans la liste
bool search(Node *head, int key);

// Fonction pour afficher la liste
void print_tree(Node *head);

// Fonction pour expérimenter les temps d'exécution des insertions
void experiment();

// Fonction pour gérer les opérations interactives sur la liste
void bd_operations();

#endif // LISTBD_H
