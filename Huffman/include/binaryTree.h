#ifndef BINARYTREE_H_
#define BINARYTREE_H_

typedef struct Node Node;
typedef struct Tree BT;

BT *createTree();
Node *newNode(void *data);
void setLeft(Node *parent, Node *child);
void setRight(Node *parent, Node *child);
void *getData(Node *node);
Node *getLeft(Node *node);
Node *getRight(Node *node);
Node *getRoot(BT *tree);
void setRoot(BT *tree, Node *node);
void destroyTree(BT *tree);

#endif