
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define R    4.0

double theta = 0.0;
double xeye = R, yeye = 0.0, zeye = 0.0;

void display();
void keyboard(unsigned char c, int x, int y);
void reshape(int w, int h);

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitWindowSize(600,600);
  glutInitWindowPosition(400,100);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutCreateWindow("The Three Musketeers");

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);

  glutMainLoop();
}
void display()
{
  glClearColor(0.9, 0.9, 0.5, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glColor3f(0.4, 0.0, 0.0);
/*
  aim the camera
*/
  xeye = R * cos(theta);
  zeye = R * sin(theta);
  gluLookAt(xeye,yeye,zeye,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
/*
  draw the world
*/
  glutWireCube(1.0);
  glutSwapBuffers();
}
void keyboard(unsigned char c, int x, int y)
{
  switch(c){
    case 27:  /* escape key */
      exit(0);
    case 'h':
      theta -= 0.1;
      break;
    case 'k':
      yeye += 0.1;
      break;
    case 'j':
      yeye -= 0.1;
      break;
    case 'l':
      theta += 0.1;
      break;
  }
  glutPostRedisplay();
}
void reshape(int w, int h)
{
  glViewport(0,0,w,h); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, 1.0, 1.0, 10.0);
  glMatrixMode(GL_MODELVIEW);
}
