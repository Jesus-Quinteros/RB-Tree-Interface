#include <GL/glut.h>
#include <stdio.h>
#include "rbtree.h"
#include <math.h>
#include <string.h>

extern RBTree* T;

void drawText(const char* text, float x, float y) {
  glRasterPos2f(x, y);
  for (int i = 0; i < strlen(text); i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
  }
}

void drawRoundedRect(float x, float y, float width, float height, float radius) {
  glColor3f(1.0f, 1.0f, 0.3f); // Amarillo suave
  glBegin(GL_POLYGON);

  glVertex2f(x + radius, y);
  glVertex2f(x + width - radius, y);
  glVertex2f(x + width, y + radius);
  glVertex2f(x + width, y + height - radius);
  glVertex2f(x + width - radius, y + height);
  glVertex2f(x + radius, y + height);
  glVertex2f(x, y + height - radius);
  glVertex2f(x, y + radius);

  glEnd();
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

void keyboard(unsigned char key, int x, int y) {
  if(key == 'i') {
    int value;
    printf("Value insert: ");
    scanf("%d", &value);
    insertRBNode(T, createRBNode(value));
    glutPostRedisplay();
  }
  if(key == 27) {
    exit(0);
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  drawRoundedRect(-0.98f, 0.75f, 0.4f, 0.2f, 0.03f);

  glColor3f(0.0f, 0.0f, 0.0f);
  drawText("Insert -> (i)", -0.9f, 0.87f);
  drawText("Exit -> (Esc)", -0.9f, 0.80f);

  if (T && T->root) {
    float startX = 0.0f;   // Coordenada X inicial (root)
    float startY = 0.8f;   // Coordenada Y inicial (root)
    float offsetX = 0.5f;  // Separación horizontal inicial entre nodos
    float offsetY = 0.2f;  // Separación vertical entre niveles
    drawTree(T->root, startX, startY, offsetX, offsetY);
  }

  glFlush();
}

