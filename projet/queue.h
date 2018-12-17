#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdbool.h>

#define QUEUE(TYPE)                                                  \
                                                                     \
typedef struct _##TYPE##_queue* TYPE##Queue;                         \
                                                                     \
TYPE##Queue new##TYPE##Queue(size_t capacity);                       \
bool isEmpty##TYPE##Queue(TYPE##Queue q);                            \
void add##TYPE##Queue(TYPE##Queue q, TYPE elem);                     \
TYPE pop##TYPE##Queue(TYPE##Queue q);                                \
void dispose##TYPE##Queue(TYPE##Queue *q);                           \
                                                                     \
/* file(a1, a2, ..., an)                                             \
 * <=> (queue[head], queue[head+1], ..., queue[tail-1]) modulo capacity\
 * head == tail => file vide                                         \
 * tail == head - 1 modulo capacity => file pleine                   \
 * capacity == quantité d'éléments que peut contenir la file + 1     \
 */                                                                  \
struct _##TYPE##_queue {                                             \
    size_t capacity;                                                 \
    size_t head;                                                     \
    size_t tail;                                                     \
    TYPE* queue;                                                     \
};                                                                   \
                                                                     \
TYPE##Queue new##TYPE##Queue(size_t capacity) {                      \
    struct _##TYPE##_queue * q = malloc(sizeof (struct _##TYPE##_queue));\
    if (q == NULL) {                                                 \
        return NULL;                                                 \
    }                                                                \
                                                                     \
    q -> capacity = capacity + 1;                                    \
    q -> head = 0;                                                   \
    q -> tail = 0;                                                   \
    q -> queue = malloc(q -> capacity * sizeof (TYPE));              \
    if (q -> queue == NULL) {                                        \
        dispose##TYPE##Queue(&q);                                    \
    }                                                                \
                                                                     \
    return q;                                                        \
}                                                                    \
                                                                     \
bool isEmpty##TYPE##Queue(TYPE##Queue q) {                           \
    return q -> head == q -> tail;                                   \
}                                                                    \
                                                                     \
void add##TYPE##Queue(TYPE##Queue q, TYPE elem) {                    \
    if ((q -> tail + 1) % q -> capacity != q -> head) {              \
        q -> queue[q -> tail] = elem;                                \
        q -> tail = (q -> tail + 1) % q -> capacity;                 \
    }                                                                \
}                                                                    \
                                                                     \
TYPE pop##TYPE##Queue(TYPE##Queue q) {                               \
    TYPE ret = q -> queue[q -> head];                                \
    if (q -> head != q -> tail) {                                    \
        q -> head = (q -> head + 1) % q -> capacity;                 \
    }                                                                \
    return ret;                                                      \
}                                                                    \
                                                                     \
void dispose##TYPE##Queue(TYPE##Queue *q) {                          \
    if ((*q) -> queue != NULL) {                                     \
        free((*q) -> queue);                                         \
    }                                                                \
    free(*q);                                                        \
    *q = NULL;                                                       \
}

#endif //QUEUE_H