#ifndef BTREE_H
#define BTREE_H

#include <stdbool.h>

#define M 6 // Maximum degree of the B-tree

// B-tree node structure
struct BTreeNode
{
    int num_keys;                  // Number of keys currently in the node
    int keys[M - 1];               // Array of keys
    struct BTreeNode *children[M]; // Array of child pointers
    bool is_leaf;                  // True if node is a leaf
};

struct BTreeNode *createNode(bool is_leaf);
void splitChild(struct BTreeNode *parent, int index);
void insertNonFull(struct BTreeNode *node, int key);
void insert(struct BTreeNode **root, int key);
void traverse(struct BTreeNode *node, int level);
void print_tree(struct BTreeNode *root);
bool search(struct BTreeNode *node, int key);
void removeFromNode(struct BTreeNode *node, int k);
void removeFromLeaf(struct BTreeNode *node, int idx);
void removeFromNonLeaf(struct BTreeNode *node, int idx);
int getPredecessor(struct BTreeNode *node, int idx);
int getSuccessor(struct BTreeNode *node, int idx);
void fill(struct BTreeNode *node, int idx);
void borrowFromPrev(struct BTreeNode *node, int idx);
void borrowFromNext(struct BTreeNode *node, int idx);
void merge(struct BTreeNode *node, int idx);
void removeKey(struct BTreeNode **root, int k);
int findKey(struct BTreeNode *node, int k);
void freeNode(struct BTreeNode *node);
void experiment();




#endif // BTREE_H
