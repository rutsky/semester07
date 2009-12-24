/* task_4_02.c
 * Task 4.02 on Unix course.
 * Vladimir Rutsky <altsysrq@gmail.com>
 * 24.12.2009
 */

/* Solving Readers-writers problem using POSIX threads, 
 * mutexes and semaphores.
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <pthread.h>

/*****
 * Constants.
 *****/

#define NREADERS 5
#define NWRITERS 2

static int const writerMaxPeriod = 10;
static int const writingMaxPeriod = 5;
static int const readerMaxPeriod = 30;
static int const readingMaxPeriod = 5;
static int const randomSleepsPeriod = 3;

/*****
 * Used special types.
 *****/

typedef void * (*thread_routine_type)( void * );
typedef struct
{
  pthread_t threadId;
  int userId;
} thread_info_type;

/*****
 * Common data.
 *****/

/* Database mutual exclusive access */
static pthread_mutex_t databaseMutex = PTHREAD_MUTEX_INITIALIZER;

/* Number of currenlty reading database Readers */
static pthread_mutex_t nReadersMutex = PTHREAD_MUTEX_INITIALIZER;
static int nReaders = 0;

/*****
 * Reader and Writer implementations.
 *****/

static void *writer( thread_info_type *info )
{
  fprintf(stdout, "Writer       #%d started.\n", info->userId);
  
  while (1)
  {
    sleep(rand() % writerMaxPeriod);
    fprintf(stdout, "Writer       #%d attempting to write...\n", info->userId);
    
    fprintf(stdout, "  ##> Writer #%d waiting for DB lock...\n", info->userId);
    pthread_mutex_lock(&databaseMutex);
    fprintf(stdout, " #### Writer #%d got DB lock. Writing...\n", info->userId);

    /* Actual writing in database... */
    sleep(rand() % writingMaxPeriod);

    fprintf(stdout, " <##  Writer #%d done writing. Releasing DB lock.\n", info->userId);
    
    pthread_mutex_unlock(&databaseMutex);
  }
  
  return NULL;
}

static void *reader( thread_info_type *info )
{
  fprintf(stdout, "Reader       #%d started.\n", info->userId);

  while (1)
  {
    sleep(rand() % writerMaxPeriod);
    fprintf(stdout, "Reader       #%d attempting to read...\n", info->userId);
    
    fprintf(stdout, "  --> Reader #%d waiting for readers count lock (before read)...\n", info->userId);
    pthread_mutex_lock(&nReadersMutex);
    fprintf(stdout, " ---- Reader #%d got readers count lock.\n", info->userId);
    if (nReaders == 0)
    {
      fprintf(stdout, "  ##> Reader #%d is first accessing DB. Waiting for DB lock...\n", info->userId);
      pthread_mutex_lock(&databaseMutex);
      fprintf(stdout, " #### Reader #%d locked DB.\n", info->userId);
    }
    ++nReaders;
    fprintf(stdout, " <--  Reader #%d unlocking readers count.\n", info->userId);
    pthread_mutex_unlock(&nReadersMutex);
    
    /* Actual reading of database... */
    sleep(rand() % readingMaxPeriod);
    
    fprintf(stdout, "  --> Reader #%d waiting for readers count lock (after read)...\n", info->userId);
    pthread_mutex_lock(&nReadersMutex);
    fprintf(stdout, " ---- Reader #%d got readers count lock.\n", info->userId);
    --nReaders;
    if (nReaders == 0)
    {
      fprintf(stdout, " <##  Reader #%d was last accessing DB. Releasing DB lock.\n", info->userId);
      pthread_mutex_unlock(&databaseMutex);
    }
    fprintf(stdout, " <--  Reader #%d unlocking readers count.\n", info->userId);
    pthread_mutex_unlock(&nReadersMutex);
  }

  return NULL;
}

/* The main program function */
int main( int argc, char const *argv[] )
{
  int i;
  thread_info_type threads[NREADERS + NWRITERS];
  int nextThreadIdx = 0;
  
  /* Initializing locks to common resources */
  srand(0);

  /* Creating writers */
  for (i = 0; i < NWRITERS; ++i)
  {
    threads[nextThreadIdx].userId = i + 1;
    if (pthread_create(&threads[nextThreadIdx].threadId, NULL, (thread_routine_type)writer, (void *)&threads[nextThreadIdx]) != 0)
    {
      perror("pthread_create");
      fprintf(stderr, "Error: pthread_create() failed.\n");
      return 1;
    }
    
    ++nextThreadIdx;
  }
  
  /* Creating readers */
  for (i = 0; i < NREADERS; ++i)
  {
    
    threads[nextThreadIdx].userId = i + 1;
    if (pthread_create(&threads[nextThreadIdx].threadId, NULL, (thread_routine_type)reader, (void *)&threads[nextThreadIdx]) != 0)
    {
      perror("pthread_create");
      fprintf(stderr, "Error: pthread_create() failed.\n");
      return 1;
    }
    
    ++nextThreadIdx;
  }
  
  /* Get threads time to work */
  while (1)
    ;
  
  return 0;
}
