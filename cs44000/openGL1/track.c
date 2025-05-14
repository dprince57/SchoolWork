
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define RAD2DEG    57.2957795
#define ROTHACK    50.0

#define NSIDES      4
#define DIM         3

#define NBUILDINGS 12
#define NITEMS      6
#define R          10.0

#define NORMAL         0
#define CRASH          1
#define TICSPERCRASH 100

typedef struct viewer {
  int flag;
  int timer;
  double spinrate;

  double tirerot;

  double x,y,z;
  double theta, phi;
  double vx,vy,vz;
  double speed;
  int steering;
} VIEWER;

GLfloat lightamb[]={0.9, 0.9, 0.9, 1.0};
GLfloat lightdif[]={0.9, 0.9, 0.9, 1.0};
GLfloat lightspe[]={0.9, 0.9, 0.9, 1.0};
GLfloat lightpos[]={7.5, 1.0, 0.0, 1.0};

GLfloat matamb[]={1.0, 0.1, 0.1, 1.0};
GLfloat matdif[]={0.1, 1.0, 0.1, 1.0};
GLfloat matspe[]={0.8, 0.8, 1.0, 1.0};

GLfloat wallamb[]={1.0, 0.1, 0.1, 1.0};
GLfloat walldif[]={1.0, 1.0, 1.0, 1.0};
GLfloat wallspe[]={0.1, 0.1, 0.1, 1.0};
 
GLUquadric *track, *outerwall;

double pov;

VIEWER moi;  /* French for me */

void display();
void reshape(int w, int h);
void init();
void update_viewer();
void move_viewer(int dir);
void arrows(int c, int x, int y);
void move();
void crash();
void keyboard(unsigned char c, int x, int y);

int main(int argc, char *argv[])
{
  pov = (argc == 1) ? 60.0 : atof(argv[1]);
  glutInit(&argc, argv);
  glutInitWindowSize(800,600);
  glutInitWindowPosition(400,100);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("The Three Musketeers");

  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutSpecialFunc(arrows);
  glutReshapeFunc(reshape);
  glutIdleFunc(move);

  init();

  glutMainLoop();
}
void race_car()
{
  glTranslatef(moi.x, moi.y, moi.z);
  glRotatef(-RAD2DEG*moi.theta, 0.0, 1.0, 0.0);
  glTranslatef(0.1,-0.1, 0.0);
  glRotatef(moi.tirerot, 0.0, 0.0,-1.0);
 
  glTranslatef(0.0, 0.0,-0.05);
  glColor3f(0.1, 0.1, 0.1);
  glutSolidTorus(0.01, 0.04, 24, 24);
  glColor3f(0.5, 0.1, 0.1);
  glutWireTorus(0.012, 0.042, 24, 24);

  glTranslatef(0.0, 0.0, 0.10);
  glColor3f(0.1, 0.1, 0.1);
  glutSolidTorus(0.01, 0.04, 24, 24);
  glColor3f(0.5, 0.1, 0.1);
  glutWireTorus(0.012, 0.042, 24, 24);
}
void race_track()
{
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matamb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matdif);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matspe);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, (GLfloat) 10.0);

  glColor3f(0.0, 0.3, 0.0);
  glutSolidSphere(4.0, 36, 36);
  glColor3f(0.0, 0.0, 0.5);
  glRotatef(-90.0, 1.0, 0.0, 0.0);
  gluDisk(track, 5.0, 10.0, 96, 8);
  glColor3f(0.6, 0.6, 0.0);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, wallamb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, walldif);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wallspe);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, (GLfloat) 50.0);

  gluCylinder(outerwall, 10.0, 10.0, 0.4, 48, 6);
  gluCylinder(outerwall, 5.0, 5.0, 0.4, 48, 6);
  glRotatef(90.0, 1.0, 0.0, 0.0);
}
void display()
{
  int i;

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

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, wallamb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, walldif);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wallspe);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, (GLfloat) 50.0);

  glBegin(GL_POLYGON);
    glVertex3f(-20.0, 0.0, -20.0);
    glVertex3f(-20.0, 0.0,  20.0);
    glVertex3f( 20.0, 0.0,  20.0);
    glVertex3f( 20.0, 0.0, -20.0);
  glEnd();
  glTranslatef(0.0,  0.01, 0.0);
  race_track();
  race_car();
  glutSwapBuffers();
}
void keyboard(unsigned char c, int x, int y)
{
  switch(c){
    case 27:  /* escape key */
      exit(0);
    case 32:
      moi.steering = 0;
  }
  update_viewer();
  glutPostRedisplay();
}
void arrows(int c, int x, int y)
{
  switch(c){
    case 'h':
    case GLUT_KEY_LEFT:
      if(moi.steering > -3) moi.steering--;
      break;
    case GLUT_KEY_UP:
      moi.speed += 0.01;
      break;
    case GLUT_KEY_DOWN:
      moi.speed *= 0.9;
      break;
    case GLUT_KEY_RIGHT:
      if(moi.steering < 3) moi.steering++;
      break;
  }
/*
  update_viewer();
  glutPostRedisplay();
*/
}
void reshape(int w, int h)
{
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(pov, (GLdouble)w/(GLdouble)h, 0.001, 250.0);
  glMatrixMode(GL_MODELVIEW);
}
void update_viewer()
{
  moi.vx = cos(moi.theta);
//  moi.vy = sin(moi.phi);
  moi.vz = sin(moi.theta);
}
void init()
{
  moi.tirerot = 0.0;

  moi.flag = NORMAL;
  moi.x =  0.0;
  moi.y =  0.5;
  moi.z = -9.0;
  moi.vx = 0.0;
  moi.vy = 0.0;
  moi.vz = 0.0;
  moi.theta = M_PI/2.0;
  moi.phi = 0.0;
  moi.speed = 0.0;
  moi.steering = 0;

  track = gluNewQuadric();
  gluQuadricDrawStyle(track, GLU_LINE);
  outerwall = gluNewQuadric();
  gluQuadricDrawStyle(outerwall, GLU_FILL);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  glLightfv(GL_LIGHT0, GL_AMBIENT, lightamb);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightdif);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightspe);
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
}
void move()
{
  double rr;

  if(moi.flag == CRASH){
    crash();
    return;
  }
  if(moi.steering){
    switch(moi.steering){
      case -3: moi.theta -= 0.010; moi.speed *= 0.99; break;
      case -2: moi.theta -= 0.005; moi.speed *= 0.999; break;
      case -1: moi.theta -= 0.002; moi.speed *= 0.9999; break;
      case  1: moi.theta += 0.002; moi.speed *= 0.9999; break;
      case  2: moi.theta += 0.005; moi.speed *= 0.999; break;
      case  3: moi.theta += 0.010; moi.speed *= 0.99; break;
    }
  }
  moi.x += moi.speed * moi.vx;
  moi.y += moi.speed * moi.vy;
  moi.z += moi.speed * moi.vz;
  moi.tirerot += ROTHACK * moi.speed;

  rr = moi.x*moi.x + moi.z*moi.z;
  moi.speed *= 0.9999;
  update_viewer();
  glutPostRedisplay();
  fprintf(stderr,"%f\n", moi.speed);
}
void crash()
{
  if(moi.timer > 0){
    --moi.timer;
    moi.theta += moi.spinrate;
    moi.spinrate *= 0.99;
  } else {
    moi.flag = NORMAL;
  }
  update_viewer();
  glutPostRedisplay();
}
