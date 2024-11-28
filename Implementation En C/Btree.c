#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include "btree.h"

// Function to create a new node
struct BTreeNode *createNode(bool is_leaf)
{
    struct BTreeNode *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    if (newNode == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->num_keys = 0;
    newNode->is_leaf = is_leaf;
    for (int i = 0; i < M; i++)
    {
        newNode->children[i] = NULL;
    }
    return newNode;
}

void freeNode(struct BTreeNode *node)
{
    if (node == NULL)
        return;

    if (!node->is_leaf)
    {
        for (int i = 0; i <= node->num_keys; i++)
        {
            freeNode(node->children[i]);
        }
    }

    free(node->keys);
    free(node->children);
    free(node);
}

// Function to split a full child node
void splitChild(struct BTreeNode *parent, int index)
{
    struct BTreeNode *child = parent->children[index];
    struct BTreeNode *newNode = createNode(child->is_leaf);

    newNode->num_keys = M / 2 - 1;

    // Move keys and children to the new node
    for (int i = 0; i < M / 2 - 1; i++)
    {
        newNode->keys[i] = child->keys[i + M / 2];
    }

    if (!child->is_leaf)
    {
        for (int i = 0; i < M / 2; i++)
        {
            newNode->children[i] = child->children[i + M / 2];
        }
    }

    child->num_keys = M / 2 - 1;

    // Shift parent's children to make space for the new node
    for (int i = parent->num_keys; i > index; i--)
    {
        parent->children[i + 1] = parent->children[i];
    }

    parent->children[index + 1] = newNode;

    // Shift parent's keys to insert the middle key from the child
    for (int i = parent->num_keys - 1; i >= index; i--)
    {
        parent->keys[i + 1] = parent->keys[i];
    }

    parent->keys[index] = child->keys[M / 2 - 1];
    parent->num_keys++;
}

// Function to insert a key into a non-full node
void insertNonFull(struct BTreeNode *node, int key)
{
    int i = node->num_keys - 1;

    if (node->is_leaf)
    {
        // Insert key into the sorted order
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
        // Find the child to insert the key
        while (i >= 0 && node->keys[i] > key)
        {
            i--;
        }
        i++;

        if (node->children[i]->num_keys == M - 1)
        {
            // Split child if it's full
            splitChild(node, i);

            // Determine which of the two children is the new one
            if (node->keys[i] < key)
            {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

// Function to insert a key into the B-tree
void insert(struct BTreeNode **root, int key)
{
    struct BTreeNode *node = *root;

    if (node == NULL)
    {
        // Create a new root node
        *root = createNode(true);
        (*root)->keys[0] = key;
        (*root)->num_keys = 1;
    }
    else
    {
        bool found = search(node, key);
        if (!found)
        {
            if (node->num_keys == M - 1)
            {
                // Split the root if it's full
                struct BTreeNode *new_root = createNode(false);
                new_root->children[0] = node;
                splitChild(new_root, 0);
                *root = new_root;
            }
            insertNonFull(*root, key);
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
    while (node != NULL)
    {
        int i = 0;
        while (i < node->num_keys && key > node->keys[i])
            i++;

        if (i < node->num_keys && node->keys[i] == key)
            return true;

        if (node->is_leaf)
            return false;

        node = node->children[i];
    }
    return false;
}

void experiment()
{
    int num_operations_values[] = {100, 1000, 10000};
    LARGE_INTEGER frequency, start, end;
    double insert_time, search_time, delete_time;

    printf("%-20s %-20s %-20s %-20s\n", "Num Operations", "Search Time (ms)", "Insert Time (ms)", "Delete Time (ms)");
    printf("--------------------------------------------------------------------------\n");

    for (int n = 0; n < 3; n++)
    {
        int num_operations = num_operations_values[n];
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

        // Measure delete time
        QueryPerformanceCounter(&start);
        for (int i = 0; i < num_operations; i++)
        {
            removeKey(&root, keys[i]);
        }
        QueryPerformanceCounter(&end);
        delete_time = (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

        printf("%-20d %-20.3f %-20.3f %-20.3f\n", num_operations, search_time, insert_time, delete_time);

        free(keys);
        freeNode(root);
    }
}

// Function to find the index of the first key that is greater than or equal to k
int findKey(struct BTreeNode *node, int k)
{
    int idx = 0;
    while (idx < node->num_keys && node->keys[idx] < k)
        ++idx;
    return idx;
}

// Function to get the predecessor of the key
int getPredecessor(struct BTreeNode *node, int idx)
{
    struct BTreeNode *cur = node->children[idx];
    while (!cur->is_leaf)
        cur = cur->children[cur->num_keys];
    return cur->keys[cur->num_keys - 1];
}

// Function to get the successor of the key
int getSuccessor(struct BTreeNode *node, int idx)
{
    struct BTreeNode *cur = node->children[idx + 1];
    while (!cur->is_leaf)
        cur = cur->children[0];
    return cur->keys[0];
}

// Function to remove the key k from the sub-tree rooted with this node
void removeFromNode(struct BTreeNode *node, int k)
{
    int idx = findKey(node, k);

    if (idx < node->num_keys && node->keys[idx] == k)
    {
        if (node->is_leaf)
            removeFromLeaf(node, idx);
        else
            removeFromNonLeaf(node, idx);
    }
    else
    {
        if (node->is_leaf)
        {
            // printf("The key %d is not in the tree\n", k);
            return;
        }

        bool flag = (idx == node->num_keys);

        if (node->children[idx]->num_keys < M / 2)
            fill(node, idx);

        if (flag && idx > node->num_keys)
            removeFromNode(node->children[idx - 1], k);
        else
            removeFromNode(node->children[idx], k);
    }
}

// Function to remove the key present in idx-th position in this node which is a leaf
void removeFromLeaf(struct BTreeNode *node, int idx)
{
    for (int i = idx + 1; i < node->num_keys; ++i)
        node->keys[i - 1] = node->keys[i];

    node->num_keys--;
}

// Function to remove the key present in idx-th position in this node which is a non-leaf
void removeFromNonLeaf(struct BTreeNode *node, int idx)
{
    int k = node->keys[idx];

    if (node->children[idx]->num_keys >= M / 2)
    {
        int pred = getPredecessor(node, idx);
        node->keys[idx] = pred;
        removeFromNode(node->children[idx], pred);
    }
    else if (node->children[idx + 1]->num_keys >= M / 2)
    {
        int succ = getSuccessor(node, idx);
        node->keys[idx] = succ;
        removeFromNode(node->children[idx + 1], succ);
    }
    else
    {
        merge(node, idx);
        removeFromNode(node->children[idx], k);
    }
}

// Function to fill the child node at idx which has less than M-1 keys
void fill(struct BTreeNode *node, int idx)
{
    if (idx != 0 && node->children[idx - 1]->num_keys >= M / 2)
        borrowFromPrev(node, idx);
    else if (idx != node->num_keys && node->children[idx + 1]->num_keys >= M / 2)
        borrowFromNext(node, idx);
    else
    {
        if (idx != node->num_keys)
            merge(node, idx);
        else
            merge(node, idx - 1);
    }
}

// Function to borrow a key from the previous sibling
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

// Function to borrow a key from the next sibling
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

// Function to merge the child node at idx with the child node at idx+1
void merge(struct BTreeNode *node, int idx)
{
    struct BTreeNode *child = node->children[idx];
    struct BTreeNode *sibling = node->children[idx + 1];

    child->keys[M / 2 - 1] = node->keys[idx];

    for (int i = 0; i < sibling->num_keys; ++i)
        child->keys[i + M / 2] = sibling->keys[i];

    if (!child->is_leaf)
    {
        for (int i = 0; i <= sibling->num_keys; ++i)
            child->children[i + M / 2] = sibling->children[i];
    }

    for (int i = idx + 1; i < node->num_keys; ++i)
        node->keys[i - 1] = node->keys[i];

    for (int i = idx + 2; i <= node->num_keys; ++i)
        node->children[i - 1] = node->children[i];

    child->num_keys += sibling->num_keys + 1;
    node->num_keys--;

    free(sibling);
}

// Function to remove the key k from the B-tree
void removeKey(struct BTreeNode **root, int k)
{
    if (*root == NULL)
    {
        printf("The tree is empty\n");
        return;
    }

    removeFromNode(*root, k);

    if ((*root)->num_keys == 0)
    {
        struct BTreeNode *tmp = *root;
        if ((*root)->is_leaf)
            *root = NULL;
        else
            *root = (*root)->children[0];

        free(tmp);
    }
}

void btree_operations()
{

    int choice, key;
    const int tree_size = 30;

    float insert_time, delete_time, search_time;

    struct BTreeNode *root = NULL;

    // Fill tree with initial values
    for (int j = 0; j < tree_size; j++)
    {
        int value = rand() % 1000; // Smaller range
        insert(&root, value);
    }

    printf("Arbre Initial: \n");
    print_tree(root);

    while (choice != 6)
    {
        printf("\nB-Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Print Tree\n");
        printf("5. Experimentation\n");
        printf("6. Retour au menu pricipal\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter key to insert: ");
            scanf("%d", &key);
            /*             QueryPerformanceFrequency(&frequency);
                        QueryPerformanceCounter(&start);
             */
            insert(&root, key);
            /*             QueryPerformanceCounter(&end);
                        insert_time = (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;
                        printf("Insert time: %.4f ms\n", insert_time);
             */
            break;

        case 2:
            printf("Enter key to delete: ");
            scanf("%d", &key);
            /*             QueryPerformanceFrequency(&frequency);
                        QueryPerformanceCounter(&start);
             */
            removeKey(&root, key);
            /*             QueryPerformanceCounter(&end);
                        delete_time = (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;
             */
            break;

        case 3:
            printf("Enter key to search: ");
            scanf("%d", &key);
            /*             QueryPerformanceFrequency(&frequency);
                        QueryPerformanceCounter(&start);
             */
            bool found = search(root, key);
            /*             QueryPerformanceCounter(&end);
                        search_time = (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;
             */
            if (found)
                printf("Key found! ");
            else
                printf("Key not found!");

            break;
        case 4:
            print_tree(root);
            break;

        case 5:
            experiment();
            break;

        case 6:
            printf("Retour au menu principal\n");

            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}