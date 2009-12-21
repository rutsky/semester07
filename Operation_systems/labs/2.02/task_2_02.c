/* task_2_01.c
 * Task 2.01 on Unix course.
 * Vladimir Rutsky <altsysrq@gmail.com>
 * 20.12.2009
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char const *argv[] )
{
  FILE **fps;
  int nStreams = argc;
  
  if ((fps = malloc(sizeof(FILE *) * nStreams)) != NULL)
  {
    int i;
  
    int openingFailed = 0;
    fps[0] = stdout;
    for (i = 1; i < nStreams; ++i)
    {
      char const *fileName = argv[i];
    
      if ((fps[i] = fopen(fileName, "w")) == NULL)
      {
        perror("fopen");
        fprintf(stderr, "Error: Failed to open '%s' for writing.", fileName);
        
        for (--i; i > 0; --i)
          fclose(fps[i]);
        
        openingFailed = 1;
        break;
      }
    }
    
    if (!openingFailed)
    {
      int ch;
      while ((ch = fgetc(stdin)) != EOF)
      {
        for (i = 0; i < nStreams; ++i)
          fputc(ch, fps[i]);
      }
      
      for (i = 1; i < argc; ++i)
        fclose(fps[i]);
    }
  
    free(fps);
  }
  else
  {
    perror("malloc");
  }

  return 0;
}
