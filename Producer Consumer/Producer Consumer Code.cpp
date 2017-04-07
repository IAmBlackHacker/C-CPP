#include<iostream>
#include<queue>
#include<pthread.h>
#include<stdlib.h>
#include<windows.h>
#define MAX 1000
using namespace std;

pthread_mutex_t the_mutex;
//pthread_cond_t condc, condp;

queue<int> q;
bool finished=false;

/*defination*/
int pthread_create(pthread_t *th, const pthread_attr_t *attr, void *(* func)(void *), void *arg);
int pthread_join(pthread_t t, void **res);
int pthread_mutex_lock(pthread_mutex_t *m);
int pthread_mutex_unlock(pthread_mutex_t *m);
int pthread_mutex_init(pthread_mutex_t *m, const pthread_mutexattr_t *a);
int pthread_mutex_destroy(pthread_mutex_t *m);

void* producer(void *ptr) {
    for (int i = 1; i <= MAX; i++) {
        pthread_mutex_lock(&the_mutex);
        q.push(i);
        cout<<"\nProducer Produce "<<i;
        pthread_mutex_unlock(&the_mutex);
    }
    finished=true;
    pthread_exit(0);
}

void* consumer(void *ptr) {
  while(true){
    pthread_mutex_lock(&the_mutex);
    while(!q.empty()){
        cout<<"\nConsumer Consume "<<q.front();
        q.pop();
    }
    pthread_mutex_unlock(&the_mutex);
    Sleep(100);
    if(finished && q.empty())break;
  }
  pthread_exit(0);
}

int main(int argc, char **argv) {
  pthread_t pro, con;

  pthread_mutex_init(&the_mutex, NULL);
  /*pthread_cond_init(&condc, NULL);
  pthread_cond_init(&condp, NULL);
  */
  pthread_create(&con, NULL, consumer, NULL);
  pthread_create(&pro, NULL, producer, NULL);

  pthread_join(con, NULL);
  pthread_join(pro, NULL);


  pthread_mutex_destroy(&the_mutex);
  /*pthread_cond_destroy(&condc);
  pthread_cond_destroy(&condp);
  */
}
