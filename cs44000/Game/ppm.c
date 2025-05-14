
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#define K  1024

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

  glGenTextures( 1, &texture );
  glBindTexture( GL_TEXTURE_2D, texture );
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE,data );

  free(data);
  return texture;
}
