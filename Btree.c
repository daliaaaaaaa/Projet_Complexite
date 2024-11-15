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

    newNode->keys = (int *)malloc((DegreeBTree - 1) * sizeof(int));
    newNode->children = (struct BTreeNode **)malloc(DegreeBTree * sizeof(struct BTreeNode *));

    if (newNode->keys == NULL || newNode->children == NULL)
    {
        perror("Memory allocation failed for keys/children arrays");
        free(newNode->keys);
        free(newNode->children);
        free(newNode);
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
        // Find the correct position for the new key
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
            i--;

        i++;

        if (node->children[i]->num_keys == DegreeBTree - 1)
        {
            splitChild(node, i);
            if (node->keys[i] < key)
                i++;
        }
        insertNonFull(node->children[i], key);
    }
}

void insert(struct BTreeNode **root, int key)
{
    if (*root == NULL)
    {
        // Tree is empty, create a new node
        *root = createNode(true);
        (*root)->keys[0] = key;
        (*root)->num_keys = 1;
        return;
    }
    bool found = search(*root, key);
    if (!found)
    {
        struct BTreeNode *r = *root;

        if (r->num_keys == DegreeBTree - 1)
        {
            struct BTreeNode *new_root = createNode(false);
            *root = new_root;
            new_root->children[0] = r;
            splitChild(new_root, 0);
            insertNonFull(new_root, key);
        }
        else
        {
            insertNonFull(r, key);
        }
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

bool search(struct BTreeNode *node, int key)
{
    if (node == NULL)
        return false;

    int i = 0;
    while (i < node->num_keys && key > node->keys[i])
        i++;

    if (i < node->num_keys && node->keys[i] == key)
        return true;

    if (node->is_leaf)
        return false;

    return search(node->children[i], key);
}

void experiment()
{
    int degrees[] = {3, 4, 6, 8, 10};
    int num_degrees = sizeof(degrees) / sizeof(degrees[0]);
    int num_operations = 50; // Increase the number of operations
    LARGE_INTEGER frequency, start, end;
    double insert_time, search_time, delete_time;

    printf("%-10s %-20s %-20s %-20s\n", "Degree", "Insert Time (ms)", "Search Time (ms)", "Delete Time (ms)");
    printf("--------------------------------------------------------------------------\n");

    for (int d = 0; d < num_degrees; d++)
    {
        DegreeBTree = degrees[d];
        struct BTreeNode *root = createNode(true);

        // Prepare random keys
        int *keys = (int *)malloc(num_operations * sizeof(int));
        if (keys == NULL)
        {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < num_operations; i++)
        {
            keys[i] = rand() % 100; // Use a larger range to reduce duplicates
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

        // Measure delete time
        QueryPerformanceCounter(&start);
        for (int i = 0; i < num_operations; i++)
        {
            deleteNode(&root, keys[i]);
        }
        QueryPerformanceCounter(&end);
        delete_time = (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

        printf("%-10d %-20.4f %-20.4f %-20.4f\n", DegreeBTree, insert_time, search_time, delete_time);

        free(keys);
        freeNode(root);
    }
}
bool deleteNode(struct BTreeNode **root, int key)
{
    if (*root == NULL)
    {
        // printf("The tree is empty\n");
        return false;
    }

    bool result = delete (*root, key);

    if ((*root)->num_keys == 0)
    {
        struct BTreeNode *tmp = *root;
        if ((*root)->is_leaf)
            *root = NULL;
        else
            *root = (*root)->children[0];
        free(tmp->keys);
        free(tmp->children);
        free(tmp);
    }
    return result;
}

// Modify delete function to return bool
bool delete(struct BTreeNode *node, int key)
{
    // Check if the key exists in the tree
    if (!search(node, key))
    {
        return false;
    }

    int idx = 0;
    while (idx < node->num_keys && node->keys[idx] < key)
        idx++;

    bool result = false;

    if (idx < node->num_keys && node->keys[idx] == key)
    {
        if (node->is_leaf)
        {
            removeFromLeaf(node, idx);
            result = true;
        }
        else
        {
            removeFromNonLeaf(node, idx);
            result = true;
        }
    }
    else
    {
        if (node->is_leaf)
        {
            printf("The key %d is not present in the tree\n", key);
            return false;
        }

        bool flag = (idx == node->num_keys);

        if (node->children[idx]->num_keys < (DegreeBTree + 1) / 2)
            fill(node, idx);

        if (flag && idx > node->num_keys)
            result = delete (node->children[idx - 1], key);
        else
            result = delete (node->children[idx], key);
    }
    return result;
}

// Implement removeFromLeaf
void removeFromLeaf(struct BTreeNode *node, int idx)
{
    for (int i = idx + 1; i < node->num_keys; ++i)
        node->keys[i - 1] = node->keys[i];

    node->num_keys--;
}

// Implement removeFromNonLeaf
void removeFromNonLeaf(struct BTreeNode *node, int idx)
{
    int key = node->keys[idx];

    if (node->children[idx]->num_keys >= (DegreeBTree + 1) / 2)
    {
        int pred = getPredecessor(node->children[idx]);
        node->keys[idx] = pred;
        delete (node->children[idx], pred);
    }
    else if (node->children[idx + 1]->num_keys >= (DegreeBTree + 1) / 2)
    {
        int succ = getSuccessor(node->children[idx + 1]);
        node->keys[idx] = succ;
        delete (node->children[idx + 1], succ);
    }
    else
    {
        merge(node, idx);
        delete (node->children[idx], key);
    }
}

int getPredecessor(struct BTreeNode *node)
{
    while (!node->is_leaf)
        node = node->children[node->num_keys];

    return node->keys[node->num_keys - 1];
}

int getSuccessor(struct BTreeNode *node)
{
    while (!node->is_leaf)
        node = node->children[0];

    return node->keys[0];
}

void fill(struct BTreeNode *node, int idx)
{
    if (idx != 0 && node->children[idx - 1]->num_keys >= (DegreeBTree + 1) / 2)
        borrowFromPrev(node, idx);
    else if (idx != node->num_keys && node->children[idx + 1]->num_keys >= (DegreeBTree + 1) / 2)
        borrowFromNext(node, idx);
    else
    {
        if (idx != node->num_keys)
            merge(node, idx);
        else
            merge(node, idx - 1);
    }
}

void borrowFromPrev(struct BTreeNode *node, int idx)
{
    struct BTreeNode *child = node->children[idx];
    struct BTreeNode *sibling = node->children[idx - 1];

    for (int i = child->num_keys - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    if (!child->is_leaf)
    {
        for (int i = child->num_keys; i >= 0; --i)
            child->children[i + 1] = child->children[i];
    }

    child->keys[0] = node->keys[idx - 1];

    if (!child->is_leaf)
        child->children[0] = sibling->children[sibling->num_keys];

    node->keys[idx - 1] = sibling->keys[sibling->num_keys - 1];

    child->num_keys += 1;
    sibling->num_keys -= 1;
}

void borrowFromNext(struct BTreeNode *node, int idx)
{
    struct BTreeNode *child = node->children[idx];
    struct BTreeNode *sibling = node->children[idx + 1];

    child->keys[child->num_keys] = node->keys[idx];

    if (!child->is_leaf)
        child->children[child->num_keys + 1] = sibling->children[0];

    node->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->num_keys; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->is_leaf)
    {
        for (int i = 1; i <= sibling->num_keys; ++i)
            sibling->children[i - 1] = sibling->children[i];
    }

    child->num_keys += 1;
    sibling->num_keys -= 1;
}

void merge(struct BTreeNode *node, int idx)
{
    struct BTreeNode *child = node->children[idx];
    struct BTreeNode *sibling = node->children[idx + 1];

    // Pull a key from the parent node into the child
    child->keys[DegreeBTree / 2 - 1] = node->keys[idx];

    // Copy keys from sibling to child
    for (int i = 0; i < sibling->num_keys; ++i)
        child->keys[i + DegreeBTree / 2] = sibling->keys[i];

    // Copy children from sibling to child, if not a leaf
    if (!child->is_leaf)
    {
        for (int i = 0; i <= sibling->num_keys; ++i)
            child->children[i + DegreeBTree / 2] = sibling->children[i];
    }

    // Shift keys in the parent node
    for (int i = idx + 1; i < node->num_keys; ++i)
        node->keys[i - 1] = node->keys[i];

    // Shift children in the parent node
    for (int i = idx + 2; i <= node->num_keys; ++i)
        node->children[i - 1] = node->children[i];

    // Update key counts
    child->num_keys += sibling->num_keys + 1;
    node->num_keys--;

    // Free the sibling node
    freeNode(sibling);
}

int main()
{

    int choice, key;
    const int tree_size = 50;

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
            bool deleted = deleteNode(&root, key);
            QueryPerformanceCounter(&end);
            delete_time = (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;
            if (deleted)
                printf("Key deleted successfully. Delete time: %.4f ms\n", delete_time);
            else
                printf("Key not found. Delete time: %.4f ms\n", delete_time);
            break;

        case 3:
            printf("Enter key to search: ");
            scanf("%d", &key);
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&start);
            bool found = search(root, key);
            QueryPerformanceCounter(&end);
            search_time = (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;
            if (found)
                printf("Key found! Search time: %.4f ms\n", search_time);
            else
                printf("Key not found! Search time: %.4f ms\n", search_time);
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