
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define WID 800
#define HGT 600
#define X   162
#define Y   134 

typedef struct roadsign {
  GLfloat pos;
  GLfloat dx;
  GLfloat scale[3];
  GLfloat size;
  GLfloat hgtfactor;
  GLfloat signsize;
} SIGN;

void display();
void reshape(int w, int h);
void keyboard(unsigned char c, int x, int y);
void drive();
void makeRasterFont(void);

double ph = 1.0;
double zoom = 15.4;

GLfloat pos[4] = {0.00,  1.00, 0.00, 1.00};
GLfloat dir[4] = {0.00, -0.10, 1.00, 1.00};

GLfloat road1[4]   = {0.2, 0.2, 0.2, 1.0};
GLfloat road2[4]   = {0.6, 0.6, 0.6, 1.0};
GLfloat road3[4]   = {0.2, 0.2, 0.2, 1.0};

GLfloat green1[4]   = {0.1, 0.2, 0.1, 1.0};
GLfloat green2[4]   = {0.1, 0.9, 0.1, 1.0};
GLfloat green3[4]   = {0.1, 0.7, 0.1, 1.0};

GLfloat yellow1[4]  = {0.6, 0.6, 0.1, 1.0};
GLfloat yellow2[4]  = {0.9, 0.9, 0.1, 1.0};
GLfloat yellow3[4]  = {0.9, 0.9, 0.1, 1.0};

GLfloat gray1[4]   = {0.1, 0.1, 0.1, 1.0};
GLfloat gray2[4]   = {0.9, 0.9, 0.9, 1.0};
GLfloat gray3[4]   = {0.6, 0.6, 0.6, 1.0};

GLfloat white[4]   = {0.9, 0.9, 0.9, 1.0};
GLfloat black[4]   = {0.1, 0.1, 0.1, 1.0};

GLfloat lightpos[] = {0.0, 0.5, 0.0, 1.0};
GLfloat lightdir[] = {0.0,-0.2,-1.0, 1.0};

GLfloat dist =  0.0;

#define NPOSTS 10

SIGN post[NPOSTS];

main(int argc, char *argv[])
{
  srand48(time(0));

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(WID,HGT);
  glutInitWindowPosition(X,Y);
  glutCreateWindow("September 15, 2001");

  initposts();
  initlighting();

  glutDisplayFunc(display);
  glutIdleFunc(drive);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);

  glutMainLoop();
}
void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  drawroad();
  glutSwapBuffers();
}
void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, w/h, 0.01,100.0);
  glMatrixMode(GL_MODELVIEW);
}
void keyboard(unsigned char c, int x, int y)
{
  switch(c){
    case  27: exit(0);
    case 'h': pos[0] += 0.1; if(pos[0] >  1.0) pos[0] =  1.0; break;
    case 'l': pos[0] -= 0.1; if(pos[0] < -1.0) pos[0] = -1.0; break;
    case 'Z':
      zoom -= 0.1;
      glLightf(GL_LIGHT0,  GL_SPOT_CUTOFF, zoom);
      break;
    case 'z':
      zoom += 0.1;
      glLightf(GL_LIGHT0,  GL_SPOT_CUTOFF, zoom);
      break;
    default:
      break;
  }
  lightpos[0] = pos[0];
  glutPostRedisplay();
}
void drive()
{
  dist += 0.1;
  ph -= 0.1;
  if(ph < 0.0) ph += 1.0;
  glutPostRedisplay();
}
drawroad()
{
  GLfloat origin[] = {0.0,0.8,0.0};
  GLfloat x,y,z;
  int i;

  glMatrixMode(GL_MODELVIEW);
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightdir);

  gluLookAt(pos[0], pos[1], pos[2],
            pos[0]+dir[0], pos[1]+dir[1], pos[2]+dir[2],
               0.0,    1.0,    0.0);
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, road1);
  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, road2);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,road3);
  glBegin(GL_POLYGON);
    glVertex3f( 1.0, 0.0, 50.0);
    glVertex3f(-1.0, 0.0, 50.0);
    glVertex3f(-1.0, 0.0,-50.0);
    glVertex3f( 1.0, 0.0,-50.0);
  glEnd();
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, green1);
  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, green2);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,green3);
  glBegin(GL_POLYGON);
    glVertex3f( 1.0, 0.0, 50.0);
    glVertex3f(25.0,-0.5, 50.0);
    glVertex3f(25.0,-0.5,  0.0);
    glVertex3f( 1.0, 0.0,  0.0);
  glEnd();
  glBegin(GL_POLYGON);
    glVertex3f( -1.0, 0.0, 50.0);
    glVertex3f(-25.0,-0.5, 50.0);
    glVertex3f(-25.0,-0.5,  0.0);
    glVertex3f( -1.0, 0.0,  0.0);
  glEnd();

  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, yellow1);
  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, yellow2);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,yellow3);
  for(z = 0.0; z < 40.0 ; z += 1.0){
    glBegin(GL_POLYGON);
      glVertex3f( 0.05, 0.1, ph+z);
      glVertex3f( 0.05, 0.1, ph+z+0.25);
      glVertex3f(-0.05, 0.1, ph+z+0.25);
      glVertex3f(-0.05, 0.1, ph+z);
    glEnd();
  }
  for(i=0;i<NPOSTS;i++){
    if(post[i].pos > dist){
      glPushMatrix();
      glTranslatef(post[i].dx, 0.0, post[i].pos-dist);
      glScalef(post[i].scale[0],post[i].scale[1],post[i].scale[2]);
      glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,white);
      glMaterialfv(GL_FRONT,GL_SPECULAR,white);
      glutSolidCube(1.0);
      glScalef(1.0/post[i].scale[0],1.0/post[i].scale[1],1.0/post[i].scale[2]);
      glTranslatef(0.0, 1.0, 0.0);
      glScalef(1.0, 1.0, 0.1);
      glutSolidCube(1.0);
      glPopMatrix();
    } else {
      randpost(i);
    }
  }
}
initlighting()
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

  glLightfv(GL_LIGHT0, GL_AMBIENT, white);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT0, GL_SPECULAR,white);

  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightdir);
  glLightf(GL_LIGHT0,  GL_SPOT_CUTOFF, zoom);
  glLightf(GL_LIGHT0,  GL_SPOT_EXPONENT, 3.0);

#if 0
  glEnable(GL_FOG);
  glFogi(GL_FOG_MODE, GL_EXP);
  glFogfv(GL_FOG_COLOR, black);
  glFogf(GL_FOG_DENSITY, 0.2);
  glFogf(GL_FOG_HINT,GL_DONT_CARE);
  glFogf(GL_FOG_START, 5.0);
  glFogf(GL_FOG_END,  50.0);
#endif
}
randpost(int n)
{
  post[n].pos = dist + 40.0 + 40.0*drand48();
  post[n].dx = (lrand48() % 100 < 50) ? 1.5 : -1.5;
  post[n].scale[0] = 0.05;
  post[n].scale[1] = 1.00;
  post[n].scale[2] = 0.05;
  post[n].size =     0.01;
  post[n].signsize = 0.08;
}
initposts()
{
  int i;

  for(i=0;i<NPOSTS;i++)
    randpost(i);
}
