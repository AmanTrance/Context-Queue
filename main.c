#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned char  current_size; 
  unsigned char  bitmap;
  void**         initial;
} Queue;

Queue* new() {
  Queue* queue = (Queue*)malloc(sizeof(Queue));
  queue->initial = (void**)malloc(sizeof(void*) * 15);
  queue->bitmap = 0;

  return queue;
}

int push(Queue* queue, void* value) {
  if (queue->current_size == 15) {
    return -1;
  }

  if ((queue->bitmap >> 4) == 15) {
    queue->initial[0] = value;
    queue->bitmap = 16 | (queue->bitmap & 15);
  } else {
    queue->initial[(queue->bitmap >> 4)] = value;
    queue->bitmap = ((queue->bitmap & 15) | (((queue->bitmap >> 4) + 1) << 4));
  }

  queue->current_size++;

  return 0;
}

void* pop(Queue* queue) {
  if (queue->current_size == 0) {
    return NULL;
  }

  void* value;

  if ((queue->bitmap & 15) == 14) {
    value = queue->initial[14];
    queue->bitmap = (queue->bitmap & 240);
  } else {
    value = queue->initial[(queue->bitmap & 15)];
    queue->bitmap = ((queue->bitmap & 240) | ((queue->bitmap & 15) + 1));
  }

  queue->current_size--;

  return value;
}

int main() {
  Queue* queue = new();

  int* values = (int*)malloc(sizeof(int) * 20);

  for (int i = 0; i < 25; i++) {
    values[i] = i + 1;
  }

  push(queue, &values[0]);
  push(queue, &values[1]);
  push(queue, &values[2]);
  push(queue, &values[3]);
  push(queue, &values[4]);
  push(queue, &values[5]);
  push(queue, &values[6]);
  push(queue, &values[7]);
  push(queue, &values[8]);
  push(queue, &values[9]);
  push(queue, &values[10]);
  push(queue, &values[11]);
  push(queue, &values[12]);
  push(queue, &values[13]);
  push(queue, &values[14]);

  printf("%d\n", *(int*)pop(queue));
  printf("%d\n", *(int*)pop(queue));
  printf("%d\n", *(int*)pop(queue));

  push(queue, &values[15]);
  push(queue, &values[16]);

  printf("%d\n", *(int*)pop(queue));
  printf("%d\n", *(int*)pop(queue));
  printf("%d\n", *(int*)pop(queue));
  printf("%d\n", *(int*)pop(queue));
  printf("%d\n", *(int*)pop(queue));
  printf("%d\n", *(int*)pop(queue));
  printf("%d\n", *(int*)pop(queue));
  printf("%d\n", *(int*)pop(queue));
  printf("%d\n", *(int*)pop(queue));
  printf("%d\n", *(int*)pop(queue));
  printf("%d\n", *(int*)pop(queue));
  printf("%d\n", *(int*)pop(queue));

  printf("%d\n", queue->current_size);

  push(queue, &values[17]);
  push(queue, &values[18]);

  printf("%d\n", *(int*)pop(queue));
  printf("%d\n", *(int*)pop(queue));

  printf("%d\n", queue->current_size);

  free(values);
  free(queue->initial);
  free(queue);

  return 0;
}