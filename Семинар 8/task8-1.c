#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int calculation_result = 0;

void *printCalcResult(void *dummy) {
  pthread_t thread = pthread_self();

  printf("Thread: %lu, calculation result: %d\n", thread, ++calculation_result);
  return NULL;
}

void createThread(pthread_t *thread) {
    int result = pthread_create(thread, (pthread_attr_t *)NULL, printCalcResult, NULL);
      if (result != 0) {
        printf ("Error code: %d\n", result);
        exit(result);
    }

    printf("Thread %lu created\n", *thread);
}

int main() {
  pthread_t thread_1, thread_2;

  // Первая нить
  createThread(&thread_1);

  // Второя нить
  createThread(&thread_2);

  // Главная нить
  pthread_t main_thread = pthread_self();
  
  printf("Main tread: %lu\n\n", main_thread);

  ++calculation_result;

  printf("Thread: %lu, calculation result: %d\n", main_thread, calculation_result);

  // Ожидание завершения
  pthread_join(thread_1, (void **)NULL);
  pthread_join(thread_2, (void **)NULL);
  return 0;
}
