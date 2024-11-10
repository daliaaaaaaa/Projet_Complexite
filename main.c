#include <stdio.h>
#include <stdlib.h>
#include <listbd.h>

// void bst_operations();   // Function to manage BST operations
void btree_operations(); // Function to manage B-tree operations

int main()
{
    int choice;

    while (1)
    {
        printf("\nSelect a Data Structure:\n");
        printf("1. Binary Search Tree (BST)\n");
        printf("2. B-Tree\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
case 1:
{
printf("Listes doublement chaînées: \n\n");
//fonction()
break;
}
case 2:
{
printf(" Arbre binaire de recherche (BST) : \n\n");
//fonction()
break;
}
case 3:
{
printf("B-tree : \n\n");
//fonction()
break;
}
case 4:

{
printf("Tas (Heap) : \n\n");
//fonction()
break;
}
}
    }

    return 0;
}
