#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *print_message_function(void *ptr) {
  printf("%s \n", (char *)ptr);
  return 0;
}

int main() {
  const char *message1 = "Thread 1";
  const char *message2 = "Thread 2";
  
  pthread_t thread1, thread2;

  pthread_create(&thread1, NULL, print_message_function, (void *)message1);
  pthread_create(&thread2, NULL, print_message_function, (void *)message2);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  exit(0);
}
