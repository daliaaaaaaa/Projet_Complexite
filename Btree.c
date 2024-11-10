#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

#define M 4

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

void splitChild(struct BTreeNode *parent, int index)
{
    struct BTreeNode *child = parent->children[index];
    struct BTreeNode *newNode = createNode(child->is_leaf);

    newNode->num_keys = M / 2 - 1;
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

    for (int i = parent->num_keys; i > index; i--)
    {
        parent->children[i + 1] = parent->children[i];
    }

    parent->children[index + 1] = newNode;

    for (int i = parent->num_keys - 1; i >= index; i--)
    {
        parent->keys[i + 1] = parent->keys[i];
    }

    parent->keys[index] = child->keys[M / 2 - 1];
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

        if (node->children[i]->num_keys == M - 1)
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
        if (node->num_keys == M - 1)
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
        return;

    printf("Level %d: ", level);
    for (int i = 0; i < node->num_keys; i++)
        printf("%d ", node->keys[i]);
    printf("\n");

    if (!node->is_leaf)
    {
        for (int i = 0; i <= node->num_keys; i++)
            traverse(node->children[i], level + 1);
    }
}

void print_tree(struct BTreeNode *root)
{
    traverse(root, 0);
}

void delete_predecessor(struct BTreeNode *node, int index)
{
    struct BTreeNode *child = node->children[index];
    while (!child->is_leaf)
    {
        child = child->children[child->num_keys];
    }

    node->keys[index] = child->keys[child->num_keys - 1];
    child->num_keys--;
}

void delete_successor(struct BTreeNode *node, int index)
{
    struct BTreeNode *child = node->children[index + 1];
    while (!child->is_leaf)
    {
        child = child->children[0];
    }

    node->keys[index] = child->keys[0];
    for (int i = 0; i < child->num_keys - 1; i++)
    {
        child->keys[i] = child->keys[i + 1];
    }
    child->num_keys--;
}

void delete_merge(struct BTreeNode *node, int index)
{
    struct BTreeNode *child = node->children[index];
    struct BTreeNode *sibling = node->children[index + 1];

    child->keys[child->num_keys] = node->keys[index];
    for (int i = 0; i < sibling->num_keys; i++)
    {
        child->keys[child->num_keys + i + 1] = sibling->keys[i];
    }

    if (!child->is_leaf)
    {
        for (int i = 0; i <= sibling->num_keys; i++)
        {
            child->children[child->num_keys + i] = sibling->children[i];
        }
    }

    child->num_keys += sibling->num_keys + 1;
    for (int i = index; i < node->num_keys - 1; i++)
    {
        node->keys[i] = node->keys[i + 1];
        node->children[i + 1] = node->children[i + 2];
    }

    node->num_keys--;
    free(sibling);
}

void delete_sibling(struct BTreeNode *node, int index)
{
    struct BTreeNode *child = node->children[index];
    struct BTreeNode *sibling = node->children[index + 1];

    child->keys[child->num_keys] = node->keys[index];
    node->keys[index] = sibling->keys[0];
    sibling->num_keys--;

    for (int i = 0; i < sibling->num_keys; i++)
    {
        sibling->keys[i] = sibling->keys[i + 1];
    }

    if (!child->is_leaf)
    {
        child->children[child->num_keys + 1] = sibling->children[0];
    }

    child->num_keys++;
}

void deleteNode(struct BTreeNode *node, int key)
{
    int i = 0;

    while (i < node->num_keys && node->keys[i] < key)
    {
        i++;
    }

    if (i < node->num_keys && node->keys[i] == key)
    {
        if (node->is_leaf)
        {
            // Case 1: The node is a leaf, just remove the key
            for (int j = i; j < node->num_keys - 1; j++)
            {
                node->keys[j] = node->keys[j + 1];
            }
            node->num_keys--;
        }
        else
        {
            // Case 2: The node is internal, handle predecessor or successor
            if (node->children[i]->num_keys >= M / 2)
            {
                // Case 2a: The left child has enough keys
                struct BTreeNode *leftChild = node->children[i];
                while (!leftChild->is_leaf)
                {
                    leftChild = leftChild->children[leftChild->num_keys];
                }
                int predecessor = leftChild->keys[leftChild->num_keys - 1];
                node->keys[i] = predecessor;
                deleteNode(node->children[i], predecessor);
            }
            else if (node->children[i + 1]->num_keys >= M / 2)
            {
                // Case 2b: The right child has enough keys
                struct BTreeNode *rightChild = node->children[i + 1];
                while (!rightChild->is_leaf)
                {
                    rightChild = rightChild->children[0];
                }
                int successor = rightChild->keys[0];
                node->keys[i] = successor;
                deleteNode(node->children[i + 1], successor);
            }
            else
            {
                // Case 2c: Merge the children
                delete_merge(node, i);
                deleteNode(node->children[i], key);
            }
        }
    }
    else
    {
        if (node->is_leaf)
        {
            printf("Key %d not found in the tree.\n", key);
            return;
        }

        // Case 3: Recursively delete from the child
        if (node->children[i]->num_keys == M / 2 - 1)
        {
            if (i > 0 && node->children[i - 1]->num_keys >= M / 2)
            {
                delete_sibling(node, i - 1);
            }
            else if (i < node->num_keys && node->children[i + 1]->num_keys >= M / 2)
            {
                delete_sibling(node, i);
            }
            else
            {
                delete_merge(node, i);
            }
        }
        deleteNode(node->children[i], key);
    }
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
            printf("Key %d found in the tree.\n", key);
            return;
        }
        else if (node->is_leaf)
        {
            printf("Key %d not found in the tree.\n", key);
            return;
        }
        else
        {
            node = node->children[i];
        }
    }
}
void btree_operations()
{
    int choice, key;
    struct BTreeNode *root = NULL;

    while (1)
    {
        printf("\nB-Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Print Tree\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter key to insert: ");
            scanf("%d", &key);
            insert(&root, key);
            break;
        case 2:
            printf("Enter key to delete: ");
            scanf("%d", &key);
            deleteNode(root, key);
            break;
        case 3:
            printf("Enter key to search: ");
            scanf("%d", &key);
            search(root, key);
            break;
        case 4:
            print_tree(root);
            break;
        case 5:
            return; // Exit B-tree operations
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}