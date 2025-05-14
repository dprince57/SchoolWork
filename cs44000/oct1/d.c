
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define NSIDES      4
#define DIM         3

#define NBUILDINGS 12
#define NITEMS      6
#define R          10.0

typedef struct viewer {
  double x,y,z;
  double theta, phi;
  double vx,vy,vz;
} VIEWER;

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

double pov;

VIEWER moi;  /* French for me */

void display();
void keyboard(unsigned char c, int x, int y);
void reshape(int w, int h);
void init();
void update_viewer();
void move_viewer(int dir);
void arrows(int c, int x, int y);

int main(int argc, char *argv[])
{
  init();

  pov = (argc == 1) ? 60.0 : atof(argv[1]);
  glutInit(&argc, argv);
  glutInitWindowSize(600,600);
  glutInitWindowPosition(400,100);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("The Three Musketeers");

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(arrows);
  glutReshapeFunc(reshape);

  glutMainLoop();
}
void building()
{
  int i;

  glColor3f(0.5, 0.0, 0.0);
  glBegin(GL_POLYGON);
    for(i=0;i<NSIDES;i++){
      glVertex3fv(vert[i]);
      glVertex3fv(vert[(i+1)%NSIDES]);
      glVertex3fv(vert[NSIDES+(i+1)%NSIDES]);
      glVertex3fv(vert[NSIDES+i]);
    }
  glEnd();
  glColor3f(0.1, 0.1, 0.1);
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
  gluLookAt(moi.x, moi.y, moi.z,
            moi.x+moi.vx, moi.y+moi.vy, moi.z+moi.vz,
            0.0, 1.0, 0.0);
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
  glScalef(1.0, 2.0, 1.0);
  for(i=0;i<NBUILDINGS;i++){
    building();
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef(30.0, 0.0, 1.0, 0.0);
  }
  glutSwapBuffers();
}
void keyboard(unsigned char c, int x, int y)
{
  switch(c){
    case 27:  /* escape key */
      exit(0);
    case 'h':
      moi.theta -= 0.1;
      break;
    case 'k':
      moi.phi += 0.1;
      break;
    case 'j':
      moi.phi -= 0.1;
      break;
    case 'l':
      moi.theta += 0.1;
      break;
  }
  update_viewer();
  glutPostRedisplay();
}
void arrows(int c, int x, int y)
{
  switch(c){
    case GLUT_KEY_UP:
      move_viewer(1);
      break;
    case GLUT_KEY_DOWN:
      move_viewer(-1);
      break;
  }
  update_viewer();
  glutPostRedisplay();
}
void reshape(int w, int h)
{
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(pov, 1.0, 0.01, 50.0);
  glMatrixMode(GL_MODELVIEW);
}
void move_viewer(int dir)
{
  if(dir > 0){
    moi.x += moi.vx;
    moi.z += moi.vz;
  } else {
    moi.x -= moi.vx;
    moi.z -= moi.vz;
  }
}
void update_viewer()
{
  moi.vx = cos(moi.theta);
  moi.vy = sin(moi.phi);
  moi.vz = sin(moi.theta);
}
void init()
{
  moi.x =   0.0;
  moi.y =   0.5;
  moi.z = -10.0;
  moi.theta = M_PI/2.0;
  moi.phi = 0.0;
}
