/*
 * 4.3. Напишите программу, моделирующую решение задачи «спящего брадобрея».
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h>

#define N_CUSTOMERS_FLOWS 4

int const maxQueueLen = 3;

int const shavingTimeMin = 1;
int const shavingTimeMax = 10;
int const customerSleepTimeMin = 1;
int const customerSleepTimeMax = 10;

void sleepInRange( int min, int max )
{
  sleep(min + rand() % (max - min));
}

void doShaving()
{
  sleepInRange(shavingTimeMin, shavingTimeMax);
}

void sleepForNextShave()
{
  sleepInRange(customerSleepTimeMin, customerSleepTimeMax);
}

static pthread_mutex_t mutex          = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t barbersMutex   = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t customersMutex = PTHREAD_MUTEX_INITIALIZER;
static int waiting = 0;

typedef void * (*thread_routine_t)( void * );

typedef struct
{
  pthread_t threadId;
  int customersFlowId;
} customer_thread_info_t;

static void *barber( void * )
{
  printf("Barber created.\n");
  
  while (1)
  {
    printf("Barber: sleeping (locking customersMutex)...\n");
    pthread_mutex_lock(&customersMutex);
    printf("Barber: awaked (locked customersMutex), locking waiting queue (locking mutex)...\n");
    pthread_mutex_lock(&mutex);
    printf("Barber: locked waiting queue (locked mutex). Selecting customer from queue and starting shaving...\n");
    --waiting;
    if (waiting > 0)
    {
      printf("Barber: Queue to barber is not empty (unlocking customersMutex).\n");
      pthread_mutex_unlock(&customersMutex);
    }
    printf("Barber: (unlocking barbersMutex).\n");
    pthread_mutex_unlock(&barbersMutex);
    printf("Barber: (unlocking mutex).\n");
    pthread_mutex_unlock(&mutex);
    printf("Barber: shaving...\n");
    doShaving();
  }
  
  return NULL;
}

static void *customersFlow( customer_thread_info_t *info )
{
  printf("Customers flow #%d created.\n", info->customersFlowId);
  
  while (1)
  {
    printf("Customer from #%d flow: sleeping for next shave...\n", info->customersFlowId);
    sleepForNextShave();
    
    printf("Customer from #%d flow: (locking mutex)...\n", info->customersFlowId);
    pthread_mutex_lock(&mutex);
    printf("Customer from #%d flow: (locked mutex).\n", info->customersFlowId);
    
    if (waiting + 1 < maxQueueLen)
    {
      printf("Customer from #%d flow: found free chair, he sits and waits for barber...\n", info->customersFlowId);
      ++waiting;
      printf("Customer from #%d flow: (unlocking customersMutex).\n", info->customersFlowId);
      pthread_mutex_unlock(&customersMutex);
      printf("Customer from #%d flow: (unlocking mutex).\n", info->customersFlowId);
      pthread_mutex_unlock(&mutex);
      printf("Customer from #%d flow: (locking barbersMutex).\n", info->customersFlowId);
      pthread_mutex_lock(&barbersMutex);
      printf("Customer from #%d flow started his shaving!\n", info->customersFlowId);
    }
    else
    {
      printf("Customer from #%d flow: no free chairs found, going away (unlocking mutex).\n", info->customersFlowId);
      pthread_mutex_unlock(&mutex);
    }
  }
  
  return NULL;
}

int main( int argc, char const *argv[] )
{
  int i;
  customer_thread_info_t customersFlowsThreads[N_CUSTOMERS_FLOWS];
  pthread_t barberThreadId;
  
  srand(0);
  
  pthread_mutex_lock(&barbersMutex);
  pthread_mutex_lock(&customersMutex);
 
  if (pthread_create(&barberThreadId, NULL, (thread_routine_t)barber, NULL) != 0)
  {
    perror("pthread_create");
    return -1;
  }
  
  for (i = 0; i < N_CUSTOMERS_FLOWS; ++i)
  {
    customersFlowsThreads[i].customersFlowId = i + 1;
    if (pthread_create(&customersFlowsThreads[i].threadId, NULL, (thread_routine_t)customersFlow, (void *)&customersFlowsThreads[i]) != 0)
    {
      perror("pthread_create");
      return -1;
    }
  }
  
  getchar();
  
  return 0;
}
