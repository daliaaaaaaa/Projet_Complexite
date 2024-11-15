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
bool search(struct BTreeNode *node, int key);
bool deleteNode(struct BTreeNode **root, int key);
bool delete(struct BTreeNode *node, int key);
void removeFromLeaf(struct BTreeNode *node, int idx);
void removeFromNonLeaf(struct BTreeNode *node, int idx);
int getPredecessor(struct BTreeNode *node);
int getSuccessor(struct BTreeNode *node);
void fill(struct BTreeNode *node, int idx);
void borrowFromPrev(struct BTreeNode *node, int idx);
void borrowFromNext(struct BTreeNode *node, int idx);
void merge(struct BTreeNode *node, int idx);

#endif // BTREE_H
