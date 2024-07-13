#include "queue.h"
#include <assert.h>

void queueInit(Queue *q)
{
    assert(!(MAX_QUEUE_SIZE & 1));
    q->idx = 0;
    for (uint32_t i = 0; i < MAX_QUEUE_SIZE; i++)
    {
        q->array[i] = GL_NO_ERROR;
    }
}

void queuePush(Queue *q, GLenum err)
{
    q->array[q->idx] = err;
    q->idx = (q->idx + 1) & (MAX_QUEUE_SIZE - 1);
}

GLenum queuePop(Queue *q)
{

    q->idx = (q->idx - 1) & (MAX_QUEUE_SIZE - 1);
    GLenum err = q->array[q->idx];
    q->array[q->idx] = GL_NO_ERROR;
    return err;
}