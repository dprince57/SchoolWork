
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#define WALKFILE   "walk1.txt"
#define MAPFILE    "map.txt"

#define DEGRAD        57.295779513
#define K           1024

#define CT_FLOOR       0
#define CT_EAST        1
#define CT_NORTH       2
#define CT_WEST        3
#define CT_SOUTH       4
#define CT_WALL        9

#define CELLSIZE       5.0
#define MSIZ          20
#define WSIZ         100.0
#define FUDGE          0.2

#define NBOB         100

#define BUILDING_PROB 15

#define MAXTICKS      60
#define NSLIDES        8
#define FPS           10

typedef
  unsigned char
uchar;

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

uchar map[MSIZ][MSIZ];

int automode = 0;

GLfloat pos1[] = {  1.0,  3.0,  4.0,  1.0};
GLfloat pos2[] = { -1.0,  3.0,  4.0,  1.0};
GLfloat amb[] =  {  0.5,  0.5,  0.5,  1.0};
GLfloat dif[] =  {  0.5,  0.5,  0.5,  1.0};
GLfloat spe[] =  {  0.9,  0.9,  0.9,  1.0};

GLfloat matamb[] = {0.30,  0.30,  0.30,  1.0};
GLfloat matdif[] = {0.50,  0.50,  0.50,  1.0};
GLfloat matspe[] = {0.10,  0.10,  0.10,  1.0};

GLfloat monamb[] = {0.60,  0.10,  0.10,  1.0};
GLfloat mondif[] = {0.10,  0.10,  0.10,  1.0};
GLfloat monspe[] = {0.10,  0.10,  0.80,  1.0};

GLfloat objamb[] = {0.20,  0.10,  0.10,  1.0};
GLfloat objdif[] = {0.70,  0.50,  0.50,  1.0};
GLfloat objspe[] = {0.60,  0.10,  0.10,  1.0};

GLUquadric *body;
GLUquadric *item;
MONSTER bob[NBOB];
WALK walk1;

double pov;
VIEWER moi;

void display();
void animate();
void reshape(int w, int h);
void arrows(int c, int x, int y);
void keyboard(unsigned char c, int x, int y);
void building();

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
      moi.theta -= 0.1;
      break;
    case GLUT_KEY_UP:
      moi.vy += 0.1;
      break;
    case GLUT_KEY_DOWN:
      moi.vy -= 0.1;
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
  p->heading = 360.0 * drand48(); 
  p->y = 1.0;
  do {
    p->x = drand48() * WSIZ;
    p->z = drand48() * WSIZ;
  } while(get_cell_type(p) != CT_FLOOR);
}
void read_map(uchar map[MSIZ][MSIZ])
{
  FILE *fd;
  int i,j,k;

  fd = fopen(MAPFILE,"r");
  if(!fd){
    fprintf(stderr,"Map file '%s' missing?\n", MAPFILE);
    exit(0);
  }
  for(i=0;i<MSIZ;i++)
    for(j=0;j<MSIZ;j++){
      fscanf(fd,"%d", &k);
      map[j][MSIZ-1-i] = k;
    }
  fclose(fd);
}
void read_walk(WALK *w)
{
  FILE *fd;
  int i;

  fd = fopen(WALKFILE,"r");
  if(!fd){
    fprintf(stderr,"Walk file '%s' missing?\n", WALKFILE);
    exit(0);
  }
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
  int i,j;

  srand48(getpid());

  moi.x =  WSIZ/2.0;
  moi.y =  5.0;
  moi.z =  WSIZ/2.0;
  moi.theta = M_PI/4.0;
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
  item = gluNewQuadric();
  gluQuadricDrawStyle(body, GLU_LINE);
  gluQuadricDrawStyle(item, GLU_FILL);

  read_walk(&walk1);
  read_map(map);

  for(i=0;i<NBOB;i++)
    init_monster(bob+i);
}
int get_cell_type(MONSTER *p)
{
  int x,z;

  x = (int)(p->x / CELLSIZE);
  z = (int)(p->z / CELLSIZE);
  return map[x][z];
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
      switch(get_cell_type(p)){
        case CT_EAST:
          p->heading =  0.0;
          break;
        case CT_NORTH:
          p->heading =  90.0;
          break;
        case CT_WEST:
          p->heading = 180.0;
          break;
        case CT_SOUTH:
          p->heading = 270.0;
          break;
        case CT_WALL:
          init_monster(p);
          break;
      }
      if(p->x < FUDGE || p->z < FUDGE)
        p->heading = 45.0;
      else if(p->x > WSIZ - FUDGE || p->z > WSIZ - FUDGE)
        p->heading = 225.0;
      else
        p->heading += 10.0 * (drand48() - 0.5);
    }
  }
  update_viewer();
  glutPostRedisplay();
}
void update_viewer()
{
  moi.vx = cos(moi.theta);
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
            moi.x + moi.vx, moi.y + moi.vy, moi.z + moi.vz,
            0.0, 1.0, 0.0);

/* floor */

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  matamb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  matdif);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matspe);
  glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 150.0);
  glBegin(GL_QUADS);
    glNormal3f(  0.0, 1.0,  0.0);
    glVertex3f(  0.0, 0.0,  0.0);
    glVertex3f( WSIZ, 0.0,  0.0);
    glVertex3f( WSIZ, 0.0, WSIZ);
    glVertex3f(  0.0, 0.0, WSIZ);
  glEnd();

  building();

  for(i=0;i<NBOB;i++)
    monster(bob + i);

  glutSwapBuffers();
}
void monster(MONSTER *p)
{
  glPushMatrix();

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  monamb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  mondif);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, monspe);
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
/*
  buildings are just QUAD's occupying a little bit less
  than one CELLSIZE square
*/
void building()
{
  int i,j;
  GLfloat fx,fz;

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  objamb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  objdif);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objspe);
  glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS,60.0);

  for(i=0;i<MSIZ;i++){
    fx = CELLSIZE * i;
    for(j=0;j<MSIZ;j++){
      if(map[i][j] == CT_WALL){
        fz = CELLSIZE * j;
        glBegin(GL_QUADS);
          glNormal3f( 0.0, 1.0, 0.0);
          glVertex3f(fx+FUDGE, 0.1, fz+FUDGE);
          glVertex3f(fx+CELLSIZE - FUDGE, 0.1, fz+FUDGE);
          glVertex3f(fx+CELLSIZE - FUDGE, 0.1, fz+CELLSIZE - FUDGE);
          glVertex3f(fx+FUDGE, 0.1, fz+CELLSIZE - FUDGE);
        glEnd();
      }
    }
  }
}
