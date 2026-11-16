#include "key.h"

void key_init(key_t *k, uint8_t raw)
{
    k->state = KEY_IDLE;
    k->stable = raw;
    k->cnt = 0;
    k->press_ms = 0;
    k->long_sent = 0;
}

key_event_t key_tick(key_t *k, uint8_t raw, uint32_t dt_ms)
{
    if (k->stable != raw)
    {
        if (++k->cnt >= 3)
        {
            k->stable = raw;
            k->cnt = 0;
        }
    }else
    {
        k->cnt = 0;
    }
    switch (k->state)
    {
        case KEY_IDLE :
            if (k->stable)
            {
                k->state = KEY_PRESSED;
            }
            break;
        case KEY_PRESSED :
            k->press_ms += dt_ms;
            if (!k->stable)
            {
                k->state = KEY_IDLE;
                return KEY_EV_SHORT;
            }
            if (k->press_ms >= 1000 && !k->long_sent)
            {
                k->state = KEY_LONG;
                k->long_sent = 1;
                return KEY_EV_LONG;
            }
            break;
        case KEY_LONG :
            if(!k->stable)
            {
                k->state = KEY_IDLE;
                return KEY_EV_RELEASE;
            }
            break;
    }
    return KEY_EV_NONE;
}