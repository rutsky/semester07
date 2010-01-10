/*
 * 2.1. [1] Напишите программу, вычисляющую суммарный размер всех файлов в указанном
 *      каталоге и его подкаталогах.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef long long ll_t ;

ll_t computeDirSize( char const *fileName )
{
  typedef struct stat stat_t;
  stat_t sb;
  
  if (lstat(fileName, &sb) == 0)
  {
    if (S_ISREG(sb.st_mode))
      return sb.st_size;
    else if (S_ISLNK(sb.st_mode))
      return sb.st_size;
    else if (S_ISDIR(sb.st_mode))
    {
      ll_t size = sb.st_size;
      DIR *dp;
      
      dp = opendir(fileName);
      if (dp != NULL)
      {
        typedef struct dirent dirent_t;
        dirent_t *ep;
        
        while ((ep = readdir(dp)) != NULL)
        {
          if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0)
          {
            char *newName;
          
            if ((newName = (char *)malloc(sizeof(char) * (strlen(fileName) + 1 + strlen(ep->d_name) + 1))) != NULL)
            {
              sprintf(newName, "%s/%s", fileName, ep->d_name);
              size += computeDirSize(newName);
          
              free(newName);
            }
            else
              perror("malloc");
          }
        }
    
        closedir(dp);
      }
      else
      {
        fprintf(stderr, "Cannot open file or directory '%s'.\n", fileName);
      }

      return size;
    }
  }
  else
  {
    perror("stat");
    fprintf(stderr, "Error: stat() failed on '%s'.\n", fileName);
  }
  
  return 0;
}

int main( int argc, char *argv[] )
{
  if (argc == 1)
    printf("%lld\t.\n", computeDirSize("."));
  else
  {
    int i;
    for (i = 1; i < argc; ++i)
      printf("%lld\t%s\n", computeDirSize(argv[i]), argv[i]);
  }

  return 0;
}

