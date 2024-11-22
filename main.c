#include <stdio.h>
#include <stdlib.h>
#include "abr.h"
#include "btree.h"

// void bst_operations();   // Function to manage BST operations
void btree_operations(); // Function to manage B-tree operations

int main()
{
    int choice;
    Noeud *racine = NULL;
    do
    {
        printf("\nSelect a Data Structure:\n");
        printf("1. Listes doublement chaînées: \n");
        printf("2. Arbre binaire de recherche (BST) : \n");
        printf("3. B-Tree\n");
        printf("4. Tas (Heap)\n");
        printf("5. Quitter\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            printf("Listes doublement chaînées: \n");
            // fonction()
            break;
        }
        case 2:
        {
            printf(" Arbre binaire de recherche (BST) : \n\n");
            menu_abr(&racine);
            break;
        }
        case 3:
        {
            printf("B-tree : \n\n");
            //btree_operations();
            break;
        }
        case 4:

        {
            printf("Tas (Heap) : \n\n");
            // fonction()
            break;
        }
        case 5:
            printf("Quitter le programme.\n");
            break;
        }
    } while (choice != 5);

    return 0;
}
