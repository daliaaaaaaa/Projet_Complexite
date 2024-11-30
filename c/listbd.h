#ifndef BIDIRECTIONAL_LIST_H
#define BIDIRECTIONAL_LIST_H

#include <stdbool.h>

// Définition de la structure du nœud pour une liste chaînée bidirectionnelle
typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

// Prototypes des fonctions
void insertbd(Node **head, int value);
void delete_nodebd(Node **head, int key);
void removeKeybd(Node **head, int key);
bool searchbd(Node *head, int key);
void print_bd(Node *head);
void experimentbd();
void bd_operations();

#endif // BIDIRECTIONAL_LIST_H
