
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define N  7
#define R  0.8

double theta = 0.0;

typedef struct pointtype {
  double x,y;
  double r,g,b;
} POINT;

POINT poly[N];

void my_init();

void display();
void keyboard(unsigned char c, int x, int y);
void click(int button, int state, int x, int y);
void motion(int x, int y);
void passive(int x, int y);
void rotate();

int main(int argc, char *argv[])
{
  my_init();

  glutInit(&argc, argv);
  glutInitWindowSize(600,600);
  glutInitWindowPosition(400,100);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutCreateWindow("The Three Musketeers");

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(click);
  glutMotionFunc(motion);
  glutPassiveMotionFunc(passive);
  glutIdleFunc(rotate);

  glutMainLoop();
}
void display()
{
  int i;

  glClearColor(0.9, 0.9, 0.5, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glLineWidth(2.0);
  glBegin(GL_POLYGON);
    for(i=0;i<N;i++){
      glColor3f(poly[i].r,poly[i].g,poly[i].b);
      glVertex2f(poly[i].x, poly[i].y);
    }
  glEnd();
  glutSwapBuffers();
}
void keyboard(unsigned char c, int x, int y)
{
  if(c == 27)
    exit(0);
}
void click(int button, int state, int x, int y)
{
  printf("%d %d %3d %3d\n", button, state, x, y);
}
void motion(int x, int y)
{
  printf("motion  %3d %3d\n", x, y);
}
void passive(int x, int y)
{
  printf("passive %3d %3d\n", x, y);
}

void my_init()
{
  int i;

  srand48(getpid());

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
  glShadeModel(GL_SMOOTH);

  for(i=0;i<N;i++){
    poly[i].x = R * cos(2.0 * M_PI * (double)i/(double) N); 
    poly[i].y = R * sin(2.0 * M_PI * (double)i/(double) N); 
    poly[i].r = drand48();
    poly[i].g = drand48();
    poly[i].b = drand48();
  }
}
void rotate()
{
  int i;

  theta += 0.01;
  for(i=0;i<N;i++){
    poly[i].x = R * cos(theta + 2.0 * M_PI * (double)i/(double) N); 
    poly[i].y = R * sin(theta + 2.0 * M_PI * (double)i/(double) N); 
  }
  glutPostRedisplay();
}
