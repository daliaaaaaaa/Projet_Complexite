#include <stdio.h>
#include <stdlib.h>

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
            // bst_operations(); // Function for BST operations
            break;
        case 2:
            btree_operations(); // Function for B-tree operations
            break;
        case 3:
            printf("Exiting...\n");
            exit(0); // Exit the program
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
