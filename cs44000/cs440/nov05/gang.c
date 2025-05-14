
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#define DEGRAD        57.295779513
#define K           1024

#define WSIZ          50.0

#define NBOB         100

#define MAXTICKS      60
#define NSLIDES        8
#define FPS           10

typedef struct viewer {
  GLfloat x,y,z;
  GLfloat theta, phi;
  GLfloat vx,vy,vz;
} VIEWER;

typedef struct monstertype {
  GLfloat lowerleglen, upperleglen, bodylen, headrad;
  GLfloat x,y,z;
  GLfloat heading;
  GLfloat leftleg,rightleg;
  GLfloat leftankle,rightankle;
  int nslides, fps;
} MONSTER;

typedef struct walkdata {
  GLfloat leftleg[NSLIDES];
  GLfloat rightleg[NSLIDES];
  GLfloat leftankle[NSLIDES];
  GLfloat rightankle[NSLIDES];
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
MONSTER bob[NBOB];
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
void start_monster(MONSTER *p)
{
  p->fps = lrand48() % FPS;
  p->nslides = 0;
}
void keyboard(unsigned char c, int x, int y)
{
  int i;

  switch(c){
    case 27:  /* escape key */
      exit(0);
    case 'w':
      if(!automode){
        automode = 1;
        for(i=0;i<NBOB;i++)
          start_monster(bob+i);
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
      moi.theta += 0.1;
      break;
    case GLUT_KEY_UP:
      moi.y += 0.1;
      break;
    case GLUT_KEY_DOWN:
      moi.y -= 0.1;
      break;
    case GLUT_KEY_RIGHT:
      moi.theta -= 0.1;
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
  gluPerspective(pov, (GLdouble)w/(GLdouble)h, 0.001, 90.0);
  glMatrixMode(GL_MODELVIEW);
}
void init_monster(MONSTER *p)
{
  memset(p,0,sizeof(MONSTER));
  p->lowerleglen = 0.5;
  p->upperleglen = 0.5;
  p->bodylen = 0.5 + drand48() * 2.0;
  p->headrad = 0.2 + drand48() * 0.8;
  p->x = drand48() * ( 2.0 * WSIZ) - WSIZ;
  p->z = drand48() * ( 2.0 * WSIZ) - WSIZ;
  p->heading = 360.0 * drand48(); 
  p->y = 1.0;
}
void read_walk(WALK *w)
{
  FILE *fd;
  int i;

  fd = fopen("/u1/junk/cs440/nov03/walk1.txt","r");
  for(i=0;i<NSLIDES;i++)
    fscanf(fd,"%f %f %f %f %f %f\n",
      &w->leftleg[i],
      &w->rightleg[i],
      &w->leftankle[i],
      &w->rightankle[i],
      &w->height[i],
      &w->ds[i]);
  fclose(fd);
  w->fps = FPS;
}
void init()
{
  int i;

  srand48(getpid());

  moi.x =   0.0;
  moi.y =   1.5;
  moi.z = -WSIZ;
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

  read_walk(&walk1);
  for(i=0;i<NBOB;i++)
    init_monster(bob+i);
}
void animate()
{
  MONSTER *p;
  int i;

  if(!automode)
    return;

  for(i=0;i<NBOB;i++){
    p = bob + i;
    p->fps++;
    if(p->fps == walk1.fps){
      p->leftleg = walk1.leftleg[p->nslides];
      p->rightleg = walk1.rightleg[p->nslides];
      p->leftankle = walk1.leftankle[p->nslides];
      p->rightankle = walk1.rightankle[p->nslides];
      p->y = walk1.height[p->nslides];
      p->x += walk1.ds[p->nslides] * cos(p->heading/DEGRAD);
      p->z += walk1.ds[p->nslides] * sin(p->heading/DEGRAD);
      p->fps = 0;
      p->nslides++;
      if(p->nslides == NSLIDES){
        automode = 1;
        p->fps = 0;
        p->nslides = 0;
      }
      if(fabs(p->x) > WSIZ || fabs(p->z) > WSIZ)
        p->heading = -p->heading;
      else
        p->heading += 30.0 * (drand48() - 0.5);
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
            moi.vx, moi.vy, moi.vz,
            0.0, 1.0, 0.0);

/* floor */

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  matamb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  matdif);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matspe);
  glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS,50.0);
  glBegin(GL_QUADS);
    glNormal3f(  0.0, 1.0, 0.0);
    glVertex3f(-WSIZ, 0.0,-WSIZ);
    glVertex3f(-WSIZ, 0.0, WSIZ);
    glVertex3f( WSIZ, 0.0, WSIZ);
    glVertex3f( WSIZ, 0.0,-WSIZ);
  glEnd();

  for(i=0;i<NBOB;i++)
    monster(bob + i);

  glutSwapBuffers();
}
void monster(MONSTER *p)
{
  glPushMatrix();

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  objamb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  objdif);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objspe);
  glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS,10.0);

  glTranslatef(p->x, 0.0, p->z);
  glRotatef(-p->heading, 0.0, 1.0, 0.0);
  glRotatef(-90.0, 1.0, 0.0, 0.0);

/* torso and head*/

  glPushMatrix();

  glTranslatef(0.0, 0.0,  p->bodylen  + p->headrad + p->y);
  gluSphere(body, p->headrad, 12, 12);

  glTranslatef(0.0, 0.0, -(p->bodylen  + p->headrad));
  glScalef(0.5, 1.0, 1.0);
  gluCylinder(body, 0.2, 0.3, p->bodylen, 12, 12);
  glPopMatrix();

/* legs */

  glPushMatrix();
      glTranslatef(0.0, 0.1, 1.0);             /* 0 is the hip */
      glRotatef(p->rightleg, 0.0, 1.0, 0.0);
/* upper leg */
      glTranslatef(0.0, 0.0,-0.5);
      gluCylinder(body, 0.04, 0.05, 0.5, 12, 12);
/* lower leg */
      glRotatef(p->rightankle, 0.0, 1.0, 0.0);
      glTranslatef(0.0, 0.0,-0.5);               /* 0 is the knee */
      gluCylinder(body, 0.03, 0.04, 0.5, 12, 12);
  glPopMatrix();

  glPushMatrix();
      glTranslatef(0.0,-0.1, 1.0);
      glRotatef(p->leftleg, 0.0, 1.0, 0.0);
      glTranslatef(0.0, 0.0,-0.5);
      gluCylinder(body, 0.05, 0.05, 0.5, 12, 12);
      glRotatef(p->leftankle, 0.0, 1.0, 0.0);
      glTranslatef(0.0, 0.0,-0.5);               /* 0 is the knee */
      gluCylinder(body, 0.03, 0.04, 0.5, 12, 12);
  glPopMatrix();

  glPopMatrix();
}
