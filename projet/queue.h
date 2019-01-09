#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdlib.h>
#include <stdbool.h>

struct queue {
  size_t capacity;
  size_t head;
  size_t tail;
  void **queue;
};

typedef struct queue *Queue;

Queue newQueue(size_t capacity);
bool isEmpty(Queue q);
void addQueue(Queue q, void *element);
void *popQueue(Queue q);
void disposeQueue(Queue *q);

#endif
