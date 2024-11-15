#ifndef BTREE_H
#define BTREE_H

#include <stdbool.h>

struct BTreeNode
{
    int *keys;
    struct BTreeNode **children;
    int num_keys;
    bool is_leaf;
};

struct BTreeNode *createNode(bool is_leaf);
void splitChild(struct BTreeNode *parent, int index);
void insertNonFull(struct BTreeNode *node, int key);
void insert(struct BTreeNode **root, int key);
void traverse(struct BTreeNode *node, int level);
void print_tree(struct BTreeNode *root);
/* void delete_predecessor(struct BTreeNode *node, int index);
void delete_successor(struct BTreeNode *node, int index);
void delete_merge(struct BTreeNode *node, int index);
void delete_sibling(struct BTreeNode *node, int index);
void deleteNode(struct BTreeNode *node, int key);
 */
void search(struct BTreeNode *root, int key);

#endif // BTREE_H
