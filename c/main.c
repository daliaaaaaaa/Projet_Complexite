// Executez gcc main.c abr.c Btree.c listbd.c Max-heap.c Min-heap.c -o main

#include <stdio.h>
#include <stdlib.h>
#include "abr.h"
#include "btree.h"
#include "Heap.h"
#include "listbd.h"

void btree_operations();

int main()
{
    int main_choice;
    printf("Select Part:\n");
    printf("1. Part 1\n");
    printf("2. Part 2\n");
    printf("3. Quitter\n");
    printf("Enter your choice: ");
    scanf("%d", &main_choice);

    if (main_choice == 1)
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
                bd_operations();
                break;
            }
            case 2:
            {
                printf(" Arbre binaire de recherche (BST) : \n\n");
                /// menu_abr(&racine);
                break;
            }
            case 3:
            {
                printf("B-tree : \n\n");
                btree_operations();
                break;
            }
            case 4:
            {
                printf("Tas (Heap) : \n\n");
                int heap_choice;
                printf("Select Heap Type:\n");
                printf("1. Max-Heap\n");
                printf("2. Min-Heap\n");
                printf("Enter your choice: ");
                scanf("%d", &heap_choice);

                switch (heap_choice)
                {
                case 1:
                    printf("Max-Heap operations:\n");
                    operrationTASmax();
                    break;
                case 2:
                    printf("Min-Heap operations:\n");
                    operationsTASmin();
                    break;
                default:
                    printf("Invalid choice.\n");
                    break;
                }
                break;
            }
            case 5:
                printf("Quitter le programme.\n");
                break;
            }
        } while (choice != 5);
    }
    else if (main_choice == 2)
    {
        int choice;
        do
        {
            printf("\nSelect a Sorting Algorithm:\n");
            printf("1. Trie par TAS\n");
            printf("2. Trie Fusion\n");
            printf("3. Trie Rapide\n");
            printf("4. Quitter\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                printf("Trie par TAS:\n");
                TriParTas_operations();
                break;
            case 2:
                printf("Tri Fusion:\n");
                // Call the function for Tri Fusion
                break;
            case 3:
                printf("Trie Rapide:\n");
                // Call the function for Trie Rapide
                break;
            case 4:
                printf("Quitter le programme.\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
        } while (choice != 4);
    }
    else
    {
        printf("Invalid choice.\n");
    }

    return 0;
}
