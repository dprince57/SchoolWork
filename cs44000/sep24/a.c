
#include <GL/glut.h>

void display();

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutCreateWindow("The Three Musketeers");
  glutDisplayFunc(display);
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
