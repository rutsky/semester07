/* task_2_01.c
 * Task 2.01 on Unix course.
 * Vladimir Rutsky <altsysrq@gmail.com>
 * 20.12.2009
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

static long long getFileSize( char const *fileName )
{
  struct stat sb;
  
  if (stat(fileName, &sb) == 0)
  {
    if (S_ISDIR(sb.st_mode))
    {
      /* Directory */
      long long size = 0;
      DIR *dp;
      
      dp = opendir(fileName);
      if (dp != NULL)
      {
        struct dirent *ep;
        
        while ((ep = readdir(dp)) != NULL)
        {
          if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0)
          {
            char *newName;
          
            if ((newName = malloc(sizeof(char) * (strlen(fileName) + 1 + strlen(ep->d_name) + 1))) != NULL)
            {
              long long dirSize = 0;
              sprintf(newName, "%s/%s", fileName, ep->d_name);
          
              dirSize = getFileSize(newName);
              size += dirSize;
          
              free(newName);
            }
            else
              perror("malloc");
          }
        }
    
        if (closedir(dp))
        {
          perror("closedir");
          fprintf(stderr, "Error: closedir() failed on '%s'.\n", fileName);
        }
      }
      else
      {
        perror("opendir");
        fprintf(stderr, "Error: opendir() failed on '%s'.\n", fileName);
      }

      /* Debug */
      fprintf(stderr, "%lld\t%s\n", size, fileName);
      
      return size;
    }
    else if (S_ISREG(sb.st_mode))
    {
      /* Regular file */

      /* Debug */
      fprintf(stderr, "%lld\t%s\n", (long long)sb.st_size, fileName);
      
      return sb.st_size;
    }
    else
    {
      /* Not a regular file, nor a directory */
      
      fprintf(stderr, "Not a regular file: '%s'.\n", fileName);
    }
  }
  else
  {
    perror("stat");
    fprintf(stderr, "Error: stat() failed on '%s'.\n", fileName);
  }

  
  return 0;
}

static int printFileSize( char const *fileName )
{
  long long size = 0;
  
  size = getFileSize(fileName);
  //printf("%lld\t%s\n", (long long)size, fileName);
  
  return 0;
}

int main( int argc, char const *argv[] )
{
  if (argc <= 1)
    return printFileSize(".");
  else
  {
    int i;
    for (i = 1; i < argc; ++i)
    {
      int result = printFileSize(argv[i]);
      if (result != 0)
        return result;
    }
  }

  return 0;
}
