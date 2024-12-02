#include <GL/glut.h>
#include <stdio.h>
#include "display.h"
#define SIZE 50

int main(int argc, char** argv) {
  int keys[SIZE];
  int c = 0;
  while(scanf("%d", &keys[c]) != EOF){
    c++;
    if(c >= SIZE) break;
  }

  setData(keys, c);

  glutInit(&argc, argv);
  glutInitWindowSize(900, 700);
  glutCreateWindow("RED BLACK TREE__(Jesus Quinteros - B)");
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
