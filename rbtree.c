#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "rbtree.h"
#include <GL/glut.h>
#include <math.h>

int max(int a, int b) { return (a > b) ? a : b; }
int height(RBNode* node) {
  if(!node) return 0; return 1 + max(height(node->left), height(node->right)); }

RBNode* createRBNode(int key){
  RBNode* node = (RBNode*)malloc(sizeof(RBNode));
  node->key = key;
  node->color = RED;
  node->parent = NULL;
  node->left = NULL;
  node->right = NULL;
  return node;
}

RBTree* createRBTree() {
  RBTree* rbtree = (RBTree*)malloc(sizeof(RBTree));
  rbtree->root = NULL;
  return rbtree;
}

void leftRotate(RBTree* T, RBNode* x) {
  RBNode* y = x->right;
  x->right = y->left;
  if(y->left != NULL)
    y->left->parent = x;
  y->parent = x->parent;
  if(x->parent == NULL) {
    T->root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else x->parent->right = y;
  y->left = x;
  x->parent = y;
}

void rightRotate(RBTree* T, RBNode* y) {
  RBNode* x = y->left;
  y->left = x->right;
  if(x->right != NULL)
    x->right->parent = y;
  x->parent = y->parent;
  if(y->parent == NULL) {
    T->root = x;
  } else if (y == y->parent->right) {
    y->parent->right = x;
  } else y->parent->left = x;
  x->right = y;
  y->parent = x;
}

void insertRBNode(RBTree* T, RBNode* z) {
  RBNode* x = T->root;
  RBNode* y = NULL;
  while(x != NULL) {
    y = x;
    if(z->key < x->key)
      x = x->left;
    else x = x->right;
  }
  z->parent = y;
  if(y == NULL) {
    T->root = z;
    z->color = BLACK;
  }else if(z->key < y->key) {
    y->left = z;
  }else y->right = z;

  if(height(T->root) > 1) {
    RBInsertFixup(T, z);
  }
}

void RBInsertFixup(RBTree* T, RBNode* z) {
  while(z->parent && z->parent->color == RED) {
    if(z->parent == z->parent->parent->left) {
      RBNode* y = z->parent->parent->right;
      if(y && y->color == RED) {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      }else {
        if(z == z->parent->right) {
          z = z->parent;
          leftRotate(T, z);
        }
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        rightRotate(T, z->parent->parent);
      }
    }else {
      RBNode* y = z->parent->parent->left;
      if(y && y->color == RED) {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      }else {
        if(z == z->parent->left) {
          z = z->parent;
          rightRotate(T, z);
        }
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        leftRotate(T, z->parent->parent);
      }
    }
  }
  T->root->color = BLACK;
}

void printTree(RBNode* node, int level) {
  if (node != NULL) {
    printTree(node->right, level+1);
    for (int i = 0; i < level-1; ++i) {
      printf("   ");
    }
    printf("|--");
    printf("%d\n", node->key);
    printTree(node->left, level+1);
  }
}

void printTreeColor(RBNode* node, int level) {
  if (node != NULL) {
    printTreeColor(node->right, level+1);
    for (int i = 0; i < level-1; ++i) {
      printf("   ");
    }
    printf("|--");
    if(node->color == RED) {
      printf("R\n");
    }else if(node->color == BLACK) {
      printf("B\n");
    }
    printTreeColor(node->left, level+1);
  }
}

void drawNode(float x, float y, int value, Color color) {
  // Dibujar círculo nodo
  if (color == RED) glColor3f(1.0f, 0.0f, 0.0f); // RED
  else glColor3f(0.0f, 0.0f, 0.0f); // BLACK

  const float radius = 0.05f; // Radio nodo
  glBegin(GL_TRIANGLE_FAN);
  for (int i = 0; i <= 360; i++) {
    float theta = i * 3.14159f / 180.0f;
    glVertex2f(x + radius * cosf(theta), y + radius * sinf(theta));
  }
  glEnd();

  // Dibujar valor nodo
  char buffer[10];
  snprintf(buffer, sizeof(buffer), "%d", value);
  glColor3f(1.0f, 1.0f, 1.0f); // Blanco para el texto
  if(-10 < value && value < 10) {
    glRasterPos2f(x - 0.01f, y - 0.015f); // Centrar 1 cifra
  }else { 
    glRasterPos2f(x - 0.02f, y - 0.015f); // Centrar 2 cifras (3 cifras no se centra)
  }
  for (char* c = buffer; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
  }
}

void drawEdge(float x1, float y1, float x2, float y2) {
  glColor3f(0.0f, 0.0f, 0.0f); // Arista negra
  glBegin(GL_LINES);
  glVertex2f(x1, y1);
  glVertex2f(x2, y2);
  glEnd();
}

void drawTree(RBNode* node, float x, float y, float offsetX, float offsetY) {
  if (node == NULL) return;

  // Dibujar nodo actual
  drawNode(x, y, node->key, node->color);

  // Dibujar subárbol izquierdo
  if (node->left != NULL) {
    float leftX = x - offsetX;
    float leftY = y - offsetY;
    drawEdge(x, y, leftX, leftY); // Dibujar arista hacia hijo izquierdo
    drawTree(node->left, leftX, leftY, offsetX / 2, offsetY);
  }

  // Dibujar el subárbol derecho
  if (node->right != NULL) {
    float rightX = x + offsetX;
    float rightY = y - offsetY;
    drawEdge(x, y, rightX, rightY); // Dibujar arista hacia hijo derecho
    drawTree(node->right, rightX, rightY, offsetX / 2, offsetY);
  }
}
