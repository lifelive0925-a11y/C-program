#ifndef KEY_H
#define KEY_H

#include <stdint.h>

typedef enum {
    KEY_IDLE,
    KEY_PRESSED,
    KEY_LONG
}key_state_t;

typedef enum{
    KEY_EV_NONE,
    KEY_EV_SHORT,
    KEY_EV_LONG,
    KEY_EV_RELEASE
}key_event_t;

typedef struct {
    key_state_t state;
    uint8_t stable;
    uint8_t cnt;
    uint32_t press_ms;
    uint8_t long_sent;
}key_t;

void key_init(key_t *k, uint8_t raw);
key_event_t key_tick(key_t *k, uint8_t raw, uint32_t dt_ms);

#endif