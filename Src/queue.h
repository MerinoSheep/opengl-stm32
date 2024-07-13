#include <stdint.h>
#include "gl.h"

#define MAX_QUEUE_SIZE 16
typedef struct
{
    uint32_t idx;
    uint32_t array[MAX_QUEUE_SIZE];
} Queue;

void queueInit(Queue *q);
void queuePush(Queue *q, GLenum err);

GLenum queuePop(Queue *q);