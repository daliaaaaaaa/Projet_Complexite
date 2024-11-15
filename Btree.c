#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "btree.h"

int DegreeBTree = 4;

// Function to create a new node
struct BTreeNode *createNode(bool is_leaf)
{
    struct BTreeNode *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    if (newNode == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    newNode->keys = (int *)malloc((DegreeBTree - 1) * sizeof(int));                            // Allocate memory for keys
    newNode->children = (struct BTreeNode **)malloc(DegreeBTree * sizeof(struct BTreeNode *)); // Allocate memory for children
    if (newNode->keys == NULL || newNode->children == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    newNode->num_keys = 0;
    newNode->is_leaf = is_leaf;
    for (int i = 0; i < DegreeBTree; i++)
    {
        newNode->children[i] = NULL;
    }

    return newNode;
}

// Function to free a node
void freeNode(struct BTreeNode *node)
{
    if (node)
    {
        free(node->keys);
        free(node->children);
        free(node);
    }
}

// Adjust all other functions below...

void splitChild(struct BTreeNode *parent, int index)
{
    struct BTreeNode *child = parent->children[index];
    struct BTreeNode *newNode = createNode(child->is_leaf);

    newNode->num_keys = DegreeBTree / 2 - 1;
    for (int i = 0; i < DegreeBTree / 2 - 1; i++)
    {
        newNode->keys[i] = child->keys[i + DegreeBTree / 2];
    }

    if (!child->is_leaf)
    {
        for (int i = 0; i < DegreeBTree / 2; i++)
        {
            newNode->children[i] = child->children[i + DegreeBTree / 2];
        }
    }

    child->num_keys = DegreeBTree / 2 - 1;

    for (int i = parent->num_keys; i > index; i--)
    {
        parent->children[i + 1] = parent->children[i];
    }

    parent->children[index + 1] = newNode;

    for (int i = parent->num_keys - 1; i >= index; i--)
    {
        parent->keys[i + 1] = parent->keys[i];
    }

    parent->keys[index] = child->keys[DegreeBTree / 2 - 1];
    parent->num_keys++;
}

void insertNonFull(struct BTreeNode *node, int key)
{
    int i = node->num_keys - 1;

    if (node->is_leaf)
    {
        while (i >= 0 && node->keys[i] > key)
        {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->num_keys++;
    }
    else
    {
        while (i >= 0 && node->keys[i] > key)
        {
            i--;
        }
        i++;

        if (node->children[i]->num_keys == DegreeBTree - 1)
        {
            splitChild(node, i);
            if (node->keys[i] < key)
            {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

void insert(struct BTreeNode **root, int key)
{
    struct BTreeNode *node = *root;

    if (node == NULL)
    {
        *root = createNode(true);
        (*root)->keys[0] = key;
        (*root)->num_keys = 1;
    }
    else
    {
        if (node->num_keys == DegreeBTree - 1)
        {
            struct BTreeNode *new_root = createNode(false);
            new_root->children[0] = node;
            splitChild(new_root, 0);
            *root = new_root;
        }
        insertNonFull(*root, key);
    }
}

void traverse(struct BTreeNode *node, int level)
{
    if (node == NULL)
    {
        return;
    }

    printf("Level %d: ", level);
    for (int i = 0; i < node->num_keys; i++)
    {
        printf("%d ", node->keys[i]);
    }
    printf("\n");

    if (!node->is_leaf)
    {
        for (int i = 0; i <= node->num_keys; i++)
        {
            traverse(node->children[i], level + 1);
        }
    }
}

void print_tree(struct BTreeNode *root)
{
    traverse(root, 0);
}

void search(struct BTreeNode *root, int key)
{
    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }

    struct BTreeNode *node = root;
    while (node != NULL)
    {
        int i = 0;
        while (i < node->num_keys && key > node->keys[i])
        {
            i++;
        }

        if (i < node->num_keys && node->keys[i] == key)
        {
            // printf("Key %d found in the tree.\n", key);
            return;
        }
        else if (node->is_leaf)
        {
            // printf("Key %d not found in the tree.\n", key);
            return;
        }
        else
        {
            node = node->children[i];
        }
    }
}
void experiment()
{
    int degrees[] = {3, 4, 6, 10};
    int num_degrees = sizeof(degrees) / sizeof(degrees[0]);
    int num_operations = 1000; // Number of operations
    LARGE_INTEGER frequency, start, end;
    double insert_time, search_time;

    printf("%-10s %-20s %-20s\n", "Degree", "Insert Time (ms)", "Search Time (ms)");
    printf("---------------------------------------------------------------\n");

    for (int d = 0; d < num_degrees; d++)
    {
        DegreeBTree = degrees[d];
        struct BTreeNode *root = createNode(true);

        // Prepare random keys
        int *keys = (int *)malloc(num_operations * sizeof(int));
        for (int i = 0; i < num_operations; i++)
        {
            keys[i] = rand();
        }

        // Measure insert time
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for (int i = 0; i < num_operations; i++)
        {
            insert(&root, keys[i]);
        }
        QueryPerformanceCounter(&end);
        insert_time = (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

        // Measure search time
        QueryPerformanceCounter(&start);
        for (int i = 0; i < num_operations; i++)
        {
            search(root, keys[i]);
        }
        QueryPerformanceCounter(&end);
        search_time = (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

        printf("%-10d %-20.4f %-20.4f\n", DegreeBTree, insert_time, search_time);

        free(keys);
        freeNode(root);
    }
}
int main()
{

    int choice, key;
    const int tree_size = 100;

    LARGE_INTEGER frequency, start, end;
    float insert_time, delete_time, search_time;

    struct BTreeNode *root = NULL;

    // Seed the random number generator
    srand(time(NULL));

    // Fill tree with initial values
    for (int j = 0; j < tree_size; j++)
    {
        int value = rand() % 100; // Smaller range
        insert(&root, value);
    }

    while (1)
    {
        printf("\nB-Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Print Tree\n");
        printf("5. Experimentation\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter key to insert: ");
            scanf("%d", &key);
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&start);
            insert(&root, key);
            QueryPerformanceCounter(&end);
            insert_time = (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;
            printf("Insert time: %.4f ms\n", insert_time);
            break;

        case 2:
            printf("Enter key to delete: ");
            scanf("%d", &key);
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&start);
            // deleteNode(root, key);
            QueryPerformanceCounter(&end);
            delete_time = (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;
            printf("Delete time: %.4f ms\n", delete_time);
            break;

        case 3:
            printf("Enter key to search: ");
            scanf("%d", &key);
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&start);
            search(root, key);
            QueryPerformanceCounter(&end);
            search_time = (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;
            printf("Search time: %.4f ms\n", search_time);
            break;

        case 4:
            print_tree(root);
            break;

        case 5:
            experiment();
            break;

        case 6:
            return 0;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}