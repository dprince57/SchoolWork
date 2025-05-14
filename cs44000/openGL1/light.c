
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define DEGRAD        57.295779513

#define CARSIZE        0.8
#define NORMAL         0
#define CRASH          1
#define TICSPERCRASH 180

#define INRAD          5.00
#define MIDRAD         7.50
#define OUTRAD        10.00
#define INRADRAD      25.00
#define MIDRADRAD     56.25
#define OUTRADRAD    100.00

typedef struct viewer {
  GLfloat x,y,z;
  GLfloat theta, phi;
  GLfloat vx,vy,vz;
} VIEWER;

GLfloat pos[] = {0.0,0.1,-1.0,1.0};
GLfloat amb[] = {0.1,0.1,0.1,1.0};
GLfloat dif[] = {0.5,0.5,0.5,1.0};
GLfloat spe[] = {0.6,0.6,0.6,1.0};

GLfloat matamb[] = {0.10, 0.10, 0.10, 1.0};
GLfloat matdif[] = {1.00, 0.00, 0.00, 1.0};
GLfloat matspe[] = {0.50, 0.50, 0.50, 1.0};

double pov;

VIEWER moi;  /* French for 'me' */

void display();
void reshape(int w, int h);
void init();
void update_viewer();
void arrows(int c, int x, int y);
void keyboard(unsigned char c, int x, int y);

int main(int argc, char *argv[])
{
  init();

  pov = (argc == 1) ? 60.0 : atof(argv[1]);
  glutInit(&argc, argv);
  glutInitWindowSize(800,600);
  glutInitWindowPosition(400,100);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutCreateWindow("The ISU 500");

  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutSpecialFunc(arrows);
  glutReshapeFunc(reshape);

  lightinit();
  display();

  glutMainLoop();
}
void display()
{
  int i;

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLineWidth(2.0);
  glLoadIdentity();

  gluLookAt(moi.x, moi.y, moi.z,
            moi.x+moi.vx, moi.y+moi.vy, moi.z+moi.vz,
            0.0, 1.0, 0.0);

  glBegin(GL_QUADS);
    glNormal3f( 1.0, 0.0, 0.0);
    glVertex3f(-1.0,-0.1,-5.0);
    glVertex3f(-1.0,-0.1,10.0);
    glVertex3f(-1.0, 1.1,10.0);
    glVertex3f(-1.0, 1.1,-5.0);

    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f( 1.0,-0.1,-5.0);
    glVertex3f( 1.0,-0.1,10.0);
    glVertex3f( 1.0, 1.1,10.0);
    glVertex3f( 1.0, 1.1,-5.0);

    glNormal3f( 0.0,-1.0, 0.0);
    glVertex3f( 1.1, 1.0,-5.0);
    glVertex3f(-1.1, 1.0,-5.0);
    glVertex3f(-1.1, 1.0,10.0);
    glVertex3f( 1.1, 1.0,10.0);

    glNormal3f( 0.0, 1.0, 0.0);
    glVertex3f( 1.1, 0.0,-5.0);
    glVertex3f( 1.1, 0.0,10.0);
    glVertex3f(-1.1, 0.0,10.0);
    glVertex3f(-1.1, 0.0,-5.0);

    glNormal3f( 0.0, 0.0,-1.0);
    glVertex3f(-1.0, 1.0,10.0);
    glVertex3f(-1.0, 0.0,10.0);
    glVertex3f( 1.0, 0.0,10.0);
    glVertex3f( 1.0, 1.0,10.0);
  glEnd();
  glutSwapBuffers();
}
void keyboard(unsigned char c, int x, int y)
{
  switch(c){
    case 27:  /* escape key */
      exit(0);
    case 'k':
      moi.z += 0.25; break;
    case 'j':
      moi.z -= 0.25; break;
  }
  update_viewer();
  glutPostRedisplay();
}
void arrows(int c, int x, int y)
{
  switch(c){
    case GLUT_KEY_LEFT:
      moi.theta -= 0.1;
      break;
    case GLUT_KEY_UP:
      moi.phi += 0.1;
      break;
    case GLUT_KEY_DOWN:
      moi.phi -= 0.1;
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
  moi.y =  0.5;
  moi.z = -5.0;
  moi.theta = M_PI/2.0;
  moi.phi = 0.0;
  update_viewer();
}
lightinit()
{
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  glLightfv(GL_LIGHT0, GL_AMBIENT,  amb);
  glLightfv(GL_LIGHT0, GL_DIFFUSE,  dif);
  glLightfv(GL_LIGHT0, GL_SPECULAR, spe);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  matamb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  matdif);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matspe);
  glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 1.0);
}

