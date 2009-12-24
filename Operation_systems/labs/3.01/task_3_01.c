/* task_3_01.c
 * Task 3.01 on Unix course.
 * Vladimir Rutsky <altsysrq@gmail.com>
 * 24.12.2009
 */

/* Program allows run not more than 3 copy at the same time
 * using System V semaphores.
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

static int const maxNProcesses = 3;

int tryRun( key_t key )
{
  int semId;
  
  /* Semaphor already exists.
   * Locating and using it */
  if ((semId = semget(key, 0, IPC_CREAT)) != -1)
  {
    struct sembuf sops[1];
    int semopResult;
        
    sops[0].sem_num =  0;          /* Operate on semaphore 0 */
    sops[0].sem_op  = -1;          /* Decrement semaphor value */
    sops[0].sem_flg =  IPC_NOWAIT | SEM_UNDO;
                                   /* Don't wait for free semaphor resources,
                                    * and free resource automatically on 
                                    * process exit */
        
    /* Decreasing semaphor on 1 if possible.
     * If not possible - quiting */
    if ((semopResult = semop(semId, sops, 1)) != -1)
    {
      /* Allocated resource.
       * Waiting current process termination to free resource */
      /* TODO: If program will be terminated here, resource will not be freed */
      fprintf(stdout, "Program is running.\n");
      
      {
        int instancesLeft;
        if ((instancesLeft = semctl(semId, 0, GETVAL)) != -1)
        {
          fprintf(stdout, "%d instances left.\n", instancesLeft);
        }
        else
        {
          perror("semctl");
          fprintf(stderr, "Error: semctl.\n");
        }
      }
      fprintf(stdout, "Press enter to terminate...\n");
      fgetc(stdin);
    }
    else if (errno == EAGAIN)
    {
      /* No free resources. Quiting */
      fprintf(stdout, "All %d program instances is running.\n", maxNProcesses);
      return 0;
    }
    else
    {
      perror("semop");
      fprintf(stderr, "Error: semop() failed.\n");
      return -1;
    }
  }
  else
  {
    perror("semget");
    fprintf(stderr, "Error: semget() failed.\n");
    return -1;
  }

  return 0;
}

int main( int argc, char const *argv[] )
{
  char const *keyPathName = argv[0];
  int const keyProjId = 1;
  
  key_t key;
  
  /* All program processes will share same IPC key created 
   * from program name and project id equal to 1. */
  if ((key = ftok(keyPathName, keyProjId)) != -1)
  {
    int semId;
    
    /* Trying to create new semaphor */
    if ((semId = semget(key, 1, IPC_CREAT | IPC_EXCL | 0600)) != -1)
    {
      /* New not initialized semaphor created.
       * Initializing it */
       
      if (semctl(semId, 0, SETVAL, maxNProcesses) != -1)
      {
        /* Initialized.
         * Running */
        int result;
        if ((result = tryRun(key)) != 0)
          return result;
      }
      else
      {
        perror("semctl");
        fprintf(stderr, "Error: semctl() failed.\n");
      }
    }
    else if (errno == EEXIST)
    {
      int result;
      if ((result = tryRun(key)) != 0)
        return result;
    }
    else
    {
      /* Some actual failure in creating semaphor */
      perror("semget");
      fprintf(stderr, "Error: semget() failed.\n");
      return -1;
    }
  }
  else
  {
    perror("ftok");
    fprintf(stderr, "Error: ftok('%s', %d) failed.\n", keyPathName, keyProjId);
    return -1;
  }
  
  return 0;
}
