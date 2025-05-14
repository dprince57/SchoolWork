
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

void display();
void keyboard(unsigned char c, int x, int y);
void click(int button, int state, int x, int y);
void motion(int x, int y);
void passive(int x, int y);

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitWindowSize(600,600);
  glutInitWindowPosition(400,100);
  glutCreateWindow("The Three Musketeers");

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(click);
  glutMotionFunc(motion);
  glutPassiveMotionFunc(passive);

  glutMainLoop();
}
void display()
{
  glClearColor(0.9, 0.9, 0.5, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 0.6);
  glLineWidth(2.0);
  glBegin(GL_LINES);
    glVertex2f(-0.9, -0.9);
    glVertex2f( 0.9,  0.9);
  glEnd();
  glColor3f(0.7, 0.0, 0.0);
  glPointSize(5.0);
  glBegin(GL_POINTS);
    glVertex2f(-0.9, -0.9);
    glVertex2f( 0.9,  0.9);
  glEnd();
  glFlush();
}
void keyboard(unsigned char c, int x, int y)
{
  if(c == 27)
    exit(0);
}
void click(int button, int state, int x, int y)
{
  printf("%d %d %3d %3d\n", button, state, x, y);
}
void motion(int x, int y)
{
  printf("motion  %3d %3d\n", x, y);
}
void passive(int x, int y)
{
  printf("passive %3d %3d\n", x, y);
}
