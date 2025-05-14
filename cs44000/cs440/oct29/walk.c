
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#define DEGRAD        57.295779513
#define K           1024

#define MAXTICKS      60
#define NSLIDES        8
#define FPS           15

typedef struct viewer {
  GLfloat x,y,z;
  GLfloat theta, phi;
  GLfloat vx,vy,vz;
} VIEWER;

typedef struct monstertype {
  GLfloat x,y,z;
  GLfloat heading;
  GLfloat leftleg,rightleg;
  int nslides, fps;
} MONSTER;

typedef struct walkdata {
  GLfloat leftleg[NSLIDES];
  GLfloat rightleg[NSLIDES];
  GLfloat height[NSLIDES];
  GLfloat ds[NSLIDES];
  int fps;
} WALK;

int automode = 0;

GLfloat pos1[] = {  1.0,  3.0,  4.0,  1.0};
GLfloat pos2[] = { -1.0,  3.0,  4.0,  1.0};
GLfloat amb[] =  {  0.5,  0.5,  0.5,  1.0};
GLfloat dif[] =  {  0.5,  0.5,  0.5,  1.0};
GLfloat spe[] =  {  0.9,  0.9,  0.9,  1.0};

GLfloat matamb[] = {0.30,  0.30,  0.30,  1.0};
GLfloat matdif[] = {0.50,  0.50,  0.50,  1.0};
GLfloat matspe[] = {0.10,  0.10,  0.10,  1.0};

GLfloat objamb[] = {0.60,  0.10,  0.10,  1.0};
GLfloat objdif[] = {0.10,  0.10,  0.10,  1.0};
GLfloat objspe[] = {0.10,  0.10,  0.80,  1.0};

GLUquadric *body;
MONSTER bob;
WALK walk1;

double pov;
VIEWER moi;

void display();
void animate();
void reshape(int w, int h);
void arrows(int c, int x, int y);
void keyboard(unsigned char c, int x, int y);

void init();
void update_viewer();
void monster(MONSTER *p);

int main(int argc, char *argv[])
{

  pov = (argc == 1) ? 60.0 : atof(argv[1]);
  glutInit(&argc, argv);
  glutInitWindowSize(800,600);
  glutInitWindowPosition(400,100);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutCreateWindow("BoiLeRPLaTe");

  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutSpecialFunc(arrows);
  glutReshapeFunc(reshape);
  glutIdleFunc(animate);

  init();
  display();

  glutMainLoop();
}
void keyboard(unsigned char c, int x, int y)
{
  switch(c){
    case 27:  /* escape key */
      exit(0);
    case 'w':
      if(!automode){
        automode = 1;
        bob.fps = 0;
        bob.nslides = 0;
      }
      break;
  }
  update_viewer();
  glutPostRedisplay();
}
void arrows(int c, int x, int y)
{
  switch(c){
    case GLUT_KEY_LEFT:
      bob.heading += 90.0;
      break;
    case GLUT_KEY_UP:
      moi.y += 0.1;
      break;
    case GLUT_KEY_DOWN:
      moi.y -= 0.1;
      break;
    case GLUT_KEY_RIGHT:
      bob.heading -= 90.0;
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
void init_monster(MONSTER *p)
{
  memset(p,0,sizeof(MONSTER));
  p->y = 1.0;
}
void read_walk(WALK *w)
{
  FILE *fd;
  int i;

  fd = fopen("walk1.txt","r");
  for(i=0;i<NSLIDES;i++)
    fscanf(fd,"%f %f %f %f\n",
      &w->leftleg[i],
      &w->rightleg[i],
      &w->height[i],
      &w->ds[i]);
  fclose(fd);
  w->fps = FPS;
}
void init()
{
  moi.x =  0.0;
  moi.y =  1.5;
  moi.z =  5.0;
  moi.theta = -M_PI/2.0;
  moi.phi = 0.0;

  automode = 0;

  update_viewer();

  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);

  glLightfv(GL_LIGHT0, GL_POSITION, pos1);
  glLightfv(GL_LIGHT0, GL_AMBIENT,  amb);
  glLightfv(GL_LIGHT0, GL_DIFFUSE,  dif);
  glLightfv(GL_LIGHT0, GL_SPECULAR, spe);

  glLightfv(GL_LIGHT0, GL_POSITION, pos2);
  glLightfv(GL_LIGHT0, GL_AMBIENT,  amb);
  glLightfv(GL_LIGHT0, GL_DIFFUSE,  dif);
  glLightfv(GL_LIGHT0, GL_SPECULAR, spe);

  body = gluNewQuadric();
  gluQuadricDrawStyle(body, GLU_LINE);

  init_monster(&bob);
  read_walk(&walk1);
}
void animate()
{

  if(!automode)
    return;

  bob.fps++;
  if(bob.fps == walk1.fps){
    bob.leftleg = walk1.leftleg[bob.nslides];
    bob.rightleg = walk1.rightleg[bob.nslides];
    bob.y = walk1.height[bob.nslides];
    bob.x += walk1.ds[bob.nslides] * cos(bob.heading/DEGRAD);
    bob.z += walk1.ds[bob.nslides] * sin(bob.heading/DEGRAD);
    bob.fps = 0;
    bob.nslides++;
    if(bob.nslides == NSLIDES){
      automode = 1;
      bob.fps = 0;
      bob.nslides = 0;
    }
  }
  update_viewer();
  glutPostRedisplay();
}
void update_viewer()
{
  moi.vx = cos(moi.theta);
  moi.vy = sin(moi.phi);
  moi.vz = sin(moi.theta);
}
void display()
{
  int i,j,k,u,v;

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLineWidth(2.0);
  glLoadIdentity();

  gluLookAt(moi.x, moi.y, moi.z,
            moi.x+moi.vx, moi.y+moi.vy, moi.z+moi.vz,
            0.0, 1.0, 0.0);

/* floor */

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  matamb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  matdif);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matspe);
  glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS,50.0);
  glBegin(GL_QUADS);
    glNormal3f(  0.0, 1.0, 0.0);
    glVertex3f(-10.0, 0.0,-10.0);
    glVertex3f(-10.0, 0.0, 10.0);
    glVertex3f( 10.0, 0.0, 10.0);
    glVertex3f( 10.0, 0.0,-10.0);
  glEnd();

  monster(&bob);

  glutSwapBuffers();
}
void monster(MONSTER *p)
{
  glPushMatrix();

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  objamb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  objdif);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objspe);
  glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS,10.0);

  glTranslatef(bob.x, 0.0, bob.z);
  glRotatef(bob.heading, 0.0, 1.0, 0.0);
  glRotatef(-90.0, 1.0, 0.0, 0.0);

/* torso and head*/

  glPushMatrix();

  glTranslatef(0.0, 0.0,  1.5 + bob.y);
  gluSphere(body, 0.5, 12, 12);

  glTranslatef(0.0, 0.0, -1.5);
  glScalef(0.5, 1.0, 1.0);
  gluCylinder(body, 0.2, 0.3, 1.0, 12, 12);
  glPopMatrix();

/* legs */

  glPushMatrix();
  glTranslatef(0.0, 0.1, 1.0);
  glRotatef(p->rightleg, 0.0, 1.0, 0.0);
  glTranslatef(0.0, 0.0,-1.0);
  gluCylinder(body, 0.05, 0.05, 1.0, 12, 12);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0,-0.1, 1.0);
  glRotatef(p->leftleg, 0.0, 1.0, 0.0);
  glTranslatef(0.0, 0.0,-1.0);
  gluCylinder(body, 0.05, 0.05, 1.0, 12, 12);
  glPopMatrix();

  glPopMatrix();
}
