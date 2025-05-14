
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define WID 800
#define HGT 800

#define X   200
#define Y   100

#define DEPTH 6

void display();
void reshape(int w, int h);
void keyboard(unsigned char c, int x, int y);

double theta = 0.0;
double phi   = 0.0;

GLfloat base0[]={ 5.0, 0.0, 5.0};
GLfloat base1[]={-5.0, 0.0, 5.0};
GLfloat base2[]={-5.0, 0.0,-5.0};
GLfloat base3[]={ 5.0, 0.0,-5.0};

GLuint dlist;

GLfloat pos[] = { 0.0, 2.0, 0.0, 1.0};

main(int argc, char *argv[])
{
  srand48(getpid());

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(WID,HGT);
  glutInitWindowPosition(X,Y);
  glutCreateWindow("CS440");

  CS440Init();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);

  glutMainLoop();
}
CS440Init()
{
  glClearColor(0.3, 0.1, 0.1, 0.0);
  glShadeModel(GL_FLAT);
  initlight();
  dlist = glGenLists(1);
  glNewList(dlist,GL_COMPILE);
  drawstuff();
  glEndList();
}
void display()
{
  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  gluLookAt( 0.0, 1.4, 4.0,
             0.0, 0.0, 0.0,
             0.0, 1.0, 0.0);
  glRotatef(theta, 0.0, 1.0, 0.0);
  glRotatef(phi  , 1.0, 0.0, 0.0);
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  glCallList(dlist);
  glPopMatrix();
  glutSwapBuffers();
}
void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90.0, 1.0, 0.01, 50.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
void keyboard(unsigned char c, int x, int y)
{
  switch(c){
    case 27: exit(0);
    case 'h': theta += 3.0; break;
    case 'l': theta -= 3.0; break;
    case 'j': phi   += 3.0; break;
    case 'k': phi   -= 3.0; break;
    case 'x': initlight(); break;
  }
  glutPostRedisplay();
}

drawstuff()
{
  fiddle(base0);
  fiddle(base1);
  fiddle(base2);
  fiddle(base3);
#if 1
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
#endif
  glBegin(GL_QUADS);
    drawquad(DEPTH,base0,base1,base2,base3);
  glEnd();
}
do_vertex(GLfloat v[])
{
  GLfloat norm[3];

  findnormal(norm,v);
  glNormal3f(norm[0],norm[1],norm[2]);
  glVertex3f(v[0],v[1],v[2]);
}
drawquad(int dep, GLfloat p1[], GLfloat p2[], GLfloat p3[], GLfloat p4[])
{
  GLfloat mid[3],m12[3],m23[3],m34[3],m41[3];
  GLfloat ma[3],mb[3];
  int i;

  if(dep <= 0){
    do_vertex(p1);
    do_vertex(p2);
    do_vertex(p3);
    do_vertex(p4);
    return;
  }
  mean(m12,p1,p2);
  mean(m23,p2,p3);
  mean(m34,p3,p4);
  mean(m41,p4,p1);
  mean(ma,m12,m34);
  mean(mb,m23,m41);
  mean(mid,ma,mb);

  fiddle(m12);
  fiddle(m23);
  fiddle(m34);
  fiddle(m41);
  fiddle(mid);

  drawquad(dep-1,p1,m12,mid,m41);
  drawquad(dep-1,p2,m23,mid,m12);
  drawquad(dep-1,p3,m34,mid,m23);
  drawquad(dep-1,p4,m41,mid,m34);
}
mean(GLfloat m[], GLfloat u[], GLfloat v[])
{
  int i;

  for(i=0;i<3;i++)
    m[i] = (u[i]+v[i])/2.0;
}
normalize(GLfloat v[])
{
  int i;
  double s = 0.0;

  for(i=0;i<3;i++)
    s += v[i]*v[i];
  s = sqrt(s);
  if(s > 0.0)
    for(i=0;i<3;i++)
      v[i] /= s;
}
findnormal(GLfloat norm[], GLfloat v[])
{
  GLfloat r,t;

  r = v[0]*v[0]+v[2]*v[2];
  t = 2.0*r/((1.0+r*r)*(1.0+r*r));
  norm[0] =  t*v[0];
  norm[1] =  1.0;
  norm[2] =  t*v[2];
  normalize(norm);
}
fiddle(GLfloat v[])
{
  GLfloat r;

  r = v[0]*v[0]+v[2]*v[2];
  v[1] = 1.0/(1.0+r*r);
}
initlight()
{
  int i;

  GLfloat amb[] = {0.0, 0.0, 0.0, 1.0};
  GLfloat dif[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat spe[] = {0.8, 0.8, 0.8, 1.0};

  GLfloat matamb[] = {0.05, 0.05, 0.00, 1.0};
  GLfloat matdif[] = {0.50, 0.50, 0.40, 1.0};
  GLfloat matspe[] = {0.70, 0.70, 0.40, 1.0};

  glEnable(GL_LIGHTING); 
  glEnable(GL_LIGHT0); 
  glEnable(GL_DEPTH_TEST); 

  glLightfv(GL_LIGHT0, GL_AMBIENT,  amb);
  glLightfv(GL_LIGHT0, GL_DIFFUSE,  dif);
  glLightfv(GL_LIGHT0, GL_SPECULAR, spe);

  glLightfv(GL_LIGHT0, GL_POSITION, pos);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matamb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matdif);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matspe);
  glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 128.0*0.078125);
}
