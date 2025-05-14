
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

#define DEPTH 8

void display();
void reshape(int w, int h);
void keyboard(unsigned char c, int x, int y);

double theta = 0.0;
double phi   = 0.0;

GLfloat base0[]={ 1.0, 0.0, 1.0};
GLfloat base1[]={-1.0, 0.0, 1.0};
GLfloat base2[]={-1.0, 0.0,-1.0};
GLfloat base3[]={ 1.0, 0.0,-1.0};
GLfloat apex[] ={ 0.0, 1.0, 0.0};

GLuint list;

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
  lightinit();
/*
  add these 4 lines
*/
  list = glGenLists(1);
  glNewList(list,GL_COMPILE);
  drawstuff();
  glEndList();
}
void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  gluLookAt( 0.1, 1.3, 1.9,
             0.0, 0.0, 0.0,
             0.0, 1.0, 0.0);
  glRotatef(theta, 0.0, 1.0, 0.0);
  glRotatef(phi  , 1.0, 0.0, 0.0);
  glCallList(list);
  glScalef(1.0,-1.0,1.0);
  glCallList(list);
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
    case 'j': phi += 3.0; break;
    case 'k': phi -= 3.0; break;
  }
  glutPostRedisplay();
}

drawstuff()
{
  normalize(apex);
  normalize(base0);
  normalize(base1);
  normalize(base2);
  normalize(base3);
  glColor3f(0.75, 0.75, 0.25);
#if 0
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
#endif
  glBegin(GL_TRIANGLES);
    drawtriangle(DEPTH,apex,base0,base1);
    drawtriangle(DEPTH,apex,base1,base2);
    drawtriangle(DEPTH,apex,base2,base3);
    drawtriangle(DEPTH,apex,base3,base0);
  glEnd();
}
normalize(GLfloat v[])
{
  int i;
  double s=0.0;

  for(i=0;i<3;i++)
    s += v[i]*v[i];
  s = sqrt(s);
  if(s < 0.8)
    for(i=0;i<3;i++)
      v[i] /= s;
}
drawtriangle(int depth, GLfloat p1[], GLfloat p2[], GLfloat p3[])
{
  GLfloat m12[3],m13[3],m23[3];
  int i;

  if(depth <= 0){
    glNormal3f(p1[0],p1[1],p1[2]);
    glVertex3f(p1[0],p1[1],p1[2]);
    glNormal3f(p2[0],p2[1],p2[2]);
    glVertex3f(p2[0],p2[1],p2[2]);
    glNormal3f(p3[0],p3[1],p3[2]);
    glVertex3f(p3[0],p3[1],p3[2]);
    return;
  }
  for(i=0;i<3;i++){
    m12[i] = (p1[i]+p2[i])/2.0;
    m13[i] = (p1[i]+p3[i])/2.0;
    m23[i] = (p2[i]+p3[i])/2.0;
  }
  normalize(m12);
  normalize(m13);
  normalize(m23);

  drawtriangle(depth-1,m12,m13,m23);
  drawtriangle(depth-1,p1,m12,m13);
  drawtriangle(depth-1,p2,m12,m23);
  drawtriangle(depth-1,p3,m13,m23);
}
lightinit()
{
  GLfloat pos[] = {0.0,2.0,0.0,1.0};
  GLfloat amb[] = {0.0,0.0,0.0,1.0};
  GLfloat dif[] = {1.0,1.0,1.0,1.0};
  GLfloat spe[] = {1.0,1.0,1.0,1.0};

  GLfloat matamb[] = {0.25, 0.20, 0.10, 1.0};
  GLfloat matdif[] = {0.75, 0.60, 0.30, 1.0};
  GLfloat matspe[] = {0.63, 0.56, 0.37, 1.0};

  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
  glLightfv(GL_LIGHT0, GL_SPECULAR, spe);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  matamb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  matdif);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matspe);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 80.0);
}
