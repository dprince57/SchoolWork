
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define NSIDES     4
#define DIM        3

#define NBUILDINGS 6
#define NITEMS     6
#define R         10.0

GLfloat vert[2*NSIDES][DIM]={
  {0.1, 0.01, 0.1},
  {0.1, 0.01, 0.9},
  {0.9, 0.01, 0.9},
  {0.9, 0.01, 0.1},
  {0.1, 3.00, 0.1},
  {0.1, 3.00, 0.9},
  {0.9, 3.00, 0.9},
  {0.9, 3.00, 0.1}
};

double theta = 0.0;
double xeye = R, yeye = 0.0, zeye = 0.0;
int item=0;

void display();
void keyboard(unsigned char c, int x, int y);
void reshape(int w, int h);

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitWindowSize(600,600);
  glutInitWindowPosition(400,100);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("The Three Musketeers");

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);

  glutMainLoop();
}
void building()
{
  int i;

  glBegin(GL_LINES);
    for(i=0;i<NSIDES;i++){
      glVertex3fv(vert[i]);
      glVertex3fv(vert[(i+1)%NSIDES]);

      glVertex3fv(vert[NSIDES+i]);
      glVertex3fv(vert[NSIDES+(i+1)%NSIDES]);

      glVertex3fv(vert[i]);
      glVertex3fv(vert[NSIDES+i]);
    }
  glEnd();
}
void display()
{
  int i;

  glEnable(GL_DEPTH_TEST);
  glClearColor(0.9, 0.9, 0.5, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLineWidth(2.0);
  glLoadIdentity();
/*
  aim the camera
*/
  xeye = R * sin(theta);
  zeye = R * cos(theta);
  gluLookAt(xeye,yeye,zeye,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
/*
  draw the world
*/
  glColor3f(0.3, 0.3, 0.0);
  glBegin(GL_POLYGON);
    glVertex3f(-20.0, 0.0, -20.0);
    glVertex3f(-20.0, 0.0,  20.0);
    glVertex3f( 20.0, 0.0,  20.0);
    glVertex3f( 20.0, 0.0, -20.0);
  glEnd();
  glColor3f(0.5, 0.0, 0.0);
  for(i=0;i<NBUILDINGS;i++){
    building();
    glTranslatef(1.0, 0.0, 0.0);
  }
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
  gluPerspective(60.0, 1.0, 0.2, 50.0);
  glMatrixMode(GL_MODELVIEW);
}
