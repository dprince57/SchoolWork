
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define N  7
#define R  0.8

double theta = 0.0;

typedef struct pointtype {
  double x,y;
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
  glutInit(&argc, argv);
  glutInitWindowSize(600,600);
  glutInitWindowPosition(400,100);
  glutCreateWindow("The Three Musketeers");

  my_init();

  glutDisplayFunc(display);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
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

  glClearColor(0.9, 0.9, 0.5, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 0.6);
  glLineWidth(2.0);
  glBegin(GL_POLYGON);
    for(i=0;i<N;i++)
      glVertex2f(poly[i].x, poly[i].y);
  glEnd();
  glFlush();
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

  for(i=0;i<N;i++){
    poly[i].x = R * cos(2.0 * M_PI * (double)i/(double) N); 
    poly[i].y = R * sin(2.0 * M_PI * (double)i/(double) N); 
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
