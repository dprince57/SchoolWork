
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
  double speed;
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

GLubyte indvert[]={
  0,1, 1,2, 2,3, 3,0, 4,5, 5,6, 6,7, 7,4, 0,4, 1,5, 2,6, 3,7
};
 
GLUquadric *track, *outerwall;

double pov;

VIEWER moi;  /* French for me */

void display();
void keyboard(unsigned char c, int x, int y);
void reshape(int w, int h);
void init();
void update_viewer();
void move_viewer(int dir);
void arrows(int c, int x, int y);
void move();

int main(int argc, char *argv[])
{
  init();

  pov = (argc == 1) ? 60.0 : atof(argv[1]);
  glutInit(&argc, argv);
  glutInitWindowSize(800,600);
  glutInitWindowPosition(400,100);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("The Three Musketeers");

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(arrows);
  glutReshapeFunc(reshape);
  glutIdleFunc(move);

  glutMainLoop();
}
void race_track()
{
  glColor3f(0.0, 0.0, 0.5);
  glRotatef(-90.0, 1.0, 0.0, 0.0);
  gluDisk(track, 5.0, 10.0, 96, 8);
  glColor3f(0.6, 0.6, 0.0);
  gluCylinder(outerwall, 10.0, 10.0, 1.0, 48, 6);
  gluCylinder(outerwall, 5.0, 5.0, 1.0, 48, 6);
  glRotatef(90.0, 1.0, 0.0, 0.0);
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
  glTranslatef(0.0, -0.01, 0.0);
  glBegin(GL_POLYGON);
    glVertex3f(-20.0, 0.0, -20.0);
    glVertex3f(-20.0, 0.0,  20.0);
    glVertex3f( 20.0, 0.0,  20.0);
    glVertex3f( 20.0, 0.0, -20.0);
  glEnd();
  glTranslatef(0.0,  0.01, 0.0);
  race_track();
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
      moi.speed += 0.01;
      break;
    case 'j':
      moi.speed *= 0.9;
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
    case 'h':
    case GLUT_KEY_LEFT:
      moi.theta -= 0.1;
      break;
    case GLUT_KEY_UP:
      moi.speed += 0.01;
      break;
    case GLUT_KEY_DOWN:
      moi.speed *= 0.9;
      break;
    case GLUT_KEY_RIGHT:
      moi.theta += 0.1;
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
  gluPerspective(pov, (GLdouble)w/(GLdouble)h, 0.001, 50.0);
  glMatrixMode(GL_MODELVIEW);
}
void update_viewer()
{
  moi.vx = cos(moi.theta);
  moi.vy = sin(moi.phi);
  moi.vz = sin(moi.theta);
}
void init()
{
  moi.x =  0.0;
  moi.y =  0.2;
  moi.z = -9.0;
  moi.vx = 0.0;
  moi.vy = 0.0;
  moi.vz = 0.0;
  moi.theta = M_PI/2.0;
  moi.phi = 0.0;
  moi.speed = 0.0;

  track = gluNewQuadric();
  gluQuadricDrawStyle(track, GLU_LINE);
  outerwall = gluNewQuadric();
  gluQuadricDrawStyle(outerwall, GLU_FILL);
}
void move()
{
  double rr;

  moi.x += moi.speed * moi.vx;
  moi.y += moi.speed * moi.vy;
  moi.z += moi.speed * moi.vz;
  rr = moi.x*moi.x + moi.z*moi.z;
  if(rr >= 100.0){     /* hit wall */
    moi.speed = 0;
    moi.x *= (99.0/rr);
    moi.z *= (99.0/rr);
  } else if(rr <= 25.0){     /* hit wall */
    moi.speed = 0;
    moi.x *= (26.0/rr);
    moi.z *= (26.0/rr);
  } else {
    moi.speed *= 0.9999;
  }
  glutPostRedisplay();
}
