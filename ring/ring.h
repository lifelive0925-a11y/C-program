#ifndef RING_H
#define RING_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct 
{
    uint8_t *buf;
    size_t cap;
    size_t head;
    size_t tail;
    size_t count;
}ring;

void ring_init(ring *r, uint8_t *storage, size_t cap);
bool ring_push(ring *r, uint8_t num);
bool ring_pop(ring *r, uint8_t *num);
bool ring_peek(ring *r, uint8_t *num);
size_t ring_size(ring *r);
size_t ring_capacity(ring *r);
bool ring_empty(ring *r);
bool ring_full(ring *r);
void ring_clear(ring *r);

#endif