/*
 * 3.2. [1] Напишите две программы, которые работают попеременно: если первая
 *      программа уже запущена в тот момент, когда запускается вторая, то первая
 *      программа завершается, и наоборот.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int acquireAndWait( int const semId )
{
  printf("Acquiring semaphor...\n");
  {
    typedef struct sembuf sembuf_t;
    sembuf_t semOp;
    int semopResult;

    semOp.sem_num =  0;
    semOp.sem_op  = -1;
    semOp.sem_flg =  SEM_UNDO;
    
    if ((semopResult = semop(semId, &semOp, 1)) == -1)
    {
      perror("semop");
      return -1;
    }
  }
  
  printf("Waiting for other processes to request semaphor...\n");
  while (1)
  {
    usleep(300000);
    
    if (semctl(semId, 0, GETNCNT) != 0)
    {
      printf("Process waiting semaphor found, quiting (with releasing semaphor).\n");
      return 0;
    }
  }
}
 
int main( int argc, char const *argv[] )
{
  char const *pathname = argv[0];
  int const proj_id = 30;
  key_t key;
  
  if ((key = ftok(pathname, proj_id)) != -1)
  {
    int semId;
    
    if ((semId = semget(key, 1, IPC_CREAT | IPC_EXCL | 0600)) != -1)
    {
      if (semctl(semId, 0, SETVAL, 1) != -1)
      {
        printf("Created new semaphor with initial value 1.\n");
        int result = acquireAndWait(semId);
        if (result != 0)
          return result;
      }
      else
      {
        perror("semctl");
        return -1;
      }
    }
    else if (errno == EEXIST)
    {
      if ((semId = semget(key, 1, 0)) != -1)
      {
        printf("Opened existing semaphor.\n");
        int result = acquireAndWait(semId);
        if (result != 0)
          return result;
      }
      else
      {
        perror("semget");
        return -1;
      }
    }
    else
    {
      perror("semget");
      return -1;
    }
  }
  else
  {
    perror("ftok");
    return -1;
  }
  
  return 0;
}
