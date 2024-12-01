#include <GL/glut.h>
#include <stdio.h>
#include "rbtree.h"
#include "display.h"

RBTree* T;

int main(int argc, char** argv) {
  T = createRBTree();
  /* // Prueba inicial libro de Cormen
  insertRBNode(T, createRBNode(11));
  insertRBNode(T, createRBNode(2));
  insertRBNode(T, createRBNode(14));
  insertRBNode(T, createRBNode(1));
  insertRBNode(T, createRBNode(7));
  insertRBNode(T, createRBNode(15));
  insertRBNode(T, createRBNode(5));
  insertRBNode(T, createRBNode(8));
  insertRBNode(T, createRBNode(4));
  */
  // 11,2,14,1,7,15,5,8,4,6,9,10,13,12,3,9,20,0,17,18,25,19,16,28,30,35
  glutInit(&argc, argv);
  glutInitWindowSize(900, 700);
  glutCreateWindow("RED BLACK TREE__(Jesus Quinteros - B)");
  glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}

