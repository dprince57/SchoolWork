
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define DEGRAD        57.295779513
#define K           1024
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

GLfloat pos[] = {0.0,0.5,1.0,1.0};
GLfloat amb[] = {0.6,0.6,0.6,1.0};
GLfloat dif[] = {0.4,0.4,0.4,1.0};
GLfloat spe[] = {0.2,0.2,0.2,1.0};

GLfloat matamb[] = {0.10, 0.10, 0.10, 1.0};
GLfloat matdif[] = {1.00, 1.00, 1.00, 1.0};
GLfloat matspe[] = {0.20, 0.20, 0.20, 1.0};

double pov;
GLuint bricktex,floortex,ceiltex;

VIEWER moi;  /* French for 'me' */

void display();
void reshape(int w, int h);
void init();
void update_viewer();
void arrows(int c, int x, int y);
void keyboard(unsigned char c, int x, int y);
GLuint readppm(char *filename);

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

  glBindTexture( GL_TEXTURE_2D, bricktex );
  glBegin(GL_QUADS);
    glNormal3f( 1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0,-0.1,-5.0);
    glTexCoord2f(7.0, 0.0); glVertex3f(-1.0,-0.1,10.0);
    glTexCoord2f(7.0, 2.0); glVertex3f(-1.0, 1.1,10.0);
    glTexCoord2f(0.0, 2.0); glVertex3f(-1.0, 1.1,-5.0);

    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f( 1.0,-0.1,-5.0);
    glVertex3f( 1.0,-0.1,10.0);
    glVertex3f( 1.0, 1.1,10.0);
    glVertex3f( 1.0, 1.1,-5.0);

    glNormal3f( 0.1, 0.1,-1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 0.0,10.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, 1.0,10.0);
    glTexCoord2f(1.0, 2.0); glVertex3f( 1.0, 1.0,10.0);
    glTexCoord2f(0.0, 2.0); glVertex3f( 1.0, 0.0,10.0);
  glEnd();

  glBindTexture( GL_TEXTURE_2D, ceiltex );
  glBegin(GL_QUADS);
    glNormal3f( 0.0,-1.0, 0.0);
    glTexCoord2f( 0.0, 0.0); glVertex3f( 1.1, 1.0,-5.0);
    glTexCoord2f(15.0, 0.0); glVertex3f( 1.1, 1.0,10.0);
    glTexCoord2f(15.0, 2.0); glVertex3f(-1.1, 1.0,10.0);
    glTexCoord2f( 0.0, 2.0); glVertex3f(-1.1, 1.0,-5.0);
  glEnd();

  glBindTexture( GL_TEXTURE_2D, floortex );
  glBegin(GL_QUADS);
    glNormal3f( 0.0, 1.0, 0.0);
    glTexCoord2f( 0.0, 0.0); glVertex3f( 1.1, 0.0,-5.0);
    glTexCoord2f(15.0, 0.0); glVertex3f( 1.1, 0.0,10.0);
    glTexCoord2f(15.0, 2.0); glVertex3f(-1.1, 0.0,10.0);
    glTexCoord2f( 0.0, 2.0); glVertex3f(-1.1, 0.0,-5.0);
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
  glEnable(GL_TEXTURE_2D);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  matamb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  matdif);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matspe);
  glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 1.0);

  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

  bricktex = readppm("/u1/junk/cs440/darkbrick.ppm");
  floortex = readppm("/u1/junk/cs440/floor.ppm");
  ceiltex = readppm("/u1/junk/cs440/ceiling.ppm");
}
/*
  The following function does almost all the initialization
  for texture mapping.
*/
GLuint readppm(char *filename)
{
  GLuint texture;
  int i,j,k;
  int width, height, max;
  char b[K];
  char version[K];
  unsigned char *data;
  FILE *fd;

/*
  first we open the file
*/
  fd = fopen(filename, "rb");  /* the 'b' is for Windoze compat */
  if(fd == NULL){
    fprintf(stderr,"You forgot to copy %s to the current directory?\n",filename);
    exit(0);
  }
/*
  The first three lines in the file are ordinary text.
  The first line has the file type: P6 in this case
  The next line has width and height of image.
  The next line has the max RGB value.
  Comment lines (lines beginning with '#') are ignored.
  The rest of the file consists of bytes which are
    grouped into R,G,B triples.  So there are
    3 * width * height bytes of image data.
*/
  do fgets(b,K,fd); while(*b == '#');

  do fgets(b,K,fd); while(*b == '#');
  sscanf(b,"%d %d\n",&width,&height);

  do fgets(b,K,fd); while(*b == '#');
  sscanf(b,"%d\n",&max);

  data = (unsigned char *) malloc(width * height * 3);
  fread(data, width * height * 3, 1, fd);
  fclose(fd);

/*
  This is the minimal initialization, using defaults.
*/
  glGenTextures( 1, &texture );
  glBindTexture( GL_TEXTURE_2D, texture );
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );

  free(data);
  return texture;
}
