#include "ring.h"
#include <stdio.h>

void ring_init(ring *r, uint8_t *storage, size_t cap)
{
    if (!r) return;
    r->buf = storage;
    r->cap = cap;
    r->head = 0;
    r->tail = 0;
    r->count = 0;
}

bool ring_push(ring *r, uint8_t num)
{
    if (!r || !r->buf || r->cap == 0 || r->cap == r->count) return false;
    r->buf[r->head] = num;
    r->head = (r->head + 1) % r->cap;
    r->count++;
    return true;
}

bool ring_pop(ring *r, uint8_t *num)
{
    if (!r || !r->buf || r->cap == 0 || r->count == 0) return false;
    *num = r->buf[r->tail]; 
    r->tail = (r->tail + 1) % r->cap;
    r->count--;
    return true;
}

bool ring_peek(ring *r, uint8_t *num)
{
    if (!r || !r->buf || r->cap == 0 || r->count == 0) return false;
    *num = r->buf[r->tail]; 
    return true;
}

size_t ring_size(ring *r)
{
    return r ? r->count : 0;
}

size_t ring_capacity(ring *r)
{
    return r ? r->cap : 0;
}

bool ring_empty(ring *r)
{
    return !r || r->count == 0;
}

bool ring_full(ring *r)
{
    return r && r->cap > 0 && r->count == r->cap;
}

void ring_clear(ring *r)
{
    if (!r) return;
    r->head = 0;
    r->tail = 0;
    r->count = 0;
}
