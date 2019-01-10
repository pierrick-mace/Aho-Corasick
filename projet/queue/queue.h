#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdlib.h>
#include <stdbool.h>

typedef struct queue {
  size_t capacity;
  size_t head;
  size_t tail;
  void **queue;
} *Queue;

Queue newQueue(size_t capacity);
bool isQueueEmpty(Queue q);
void enQueue(Queue q, void *element);
void *deQueue(Queue q);
void freeQueue(Queue q);

#endif
