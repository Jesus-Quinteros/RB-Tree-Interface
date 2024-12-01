#ifndef RBTREE_H
#define RBTREE_H

typedef enum { RED, BLACK } Color;

typedef struct sRBNode {
  int key;
  Color color;
  struct sRBNode* parent;
  struct sRBNode* left;
  struct sRBNode* right;
} RBNode;

typedef struct {
  RBNode* root;
} RBTree;

RBTree* createRBTree();
RBNode* createRBNode(int);
void insertRBNode(RBTree*, RBNode*);
void leftRotate(RBTree* T, RBNode* x);
void rightRotate(RBTree* T, RBNode* y);
void RBInsertFixup(RBTree* T, RBNode* z);

void printTree(RBNode*, int);
void printTreeColor(RBNode*, int);
int max(int, int);
int height(RBNode*);

#endif
