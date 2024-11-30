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

