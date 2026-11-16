#include <stdio.h>
#include "key.h"

static const char *ev_name(key_event_t e)
{
    switch (e)
    {
        case KEY_EV_NONE : return "NONE";
        case KEY_EV_SHORT : return "SHORT";
        case KEY_EV_LONG : return "LONG";
        case KEY_EV_RELEASE : return "RELEASE";
        default : return "?";
    }
}

/* 连续喂 ticks 次同一电平，返回最后一次非 NONE 事件 */
static key_event_t feed(key_t *k, uint8_t raw, int ticks)
{
    key_event_t last = KEY_EV_NONE;
    for (int i = 0; i < ticks; i++)
    {
        key_event_t e = key_tick(k, raw, 10);
        if (e != KEY_EV_NONE) last = e;
    }
    return last;
}

int main(void)
{
    key_t k;

    /* 1. 短按：按下消抖 3 tick，保持 50 tick（0.5s），释放 3 tick */
    key_init(&k, 0);
    feed(&k, 1, 3);
    feed(&k, 1, 50);
    printf("short   : %s\n", ev_name(feed(&k, 0, 3)));

    /* 2. 长按：按下消抖 3 tick，保持 120 tick（1.2s），再释放 */
    key_init(&k, 0);
    feed(&k, 1, 3);
    printf("long    : %s\n", ev_name(feed(&k, 1, 120)));
    printf("release : %s\n", ev_name(feed(&k, 0, 3)));

    /* 3. 抖动：1/0 交替 2 次，不够 3 次，不应触发任何事件 */
    key_init(&k, 0);
    key_event_t be = KEY_EV_NONE;
    for (int i = 0; i < 2; i++)
    {
        key_event_t x = key_tick(&k, 1, 10);
        if (x != KEY_EV_NONE) be = x;
        x = key_tick(&k, 0, 10);
        if (x != KEY_EV_NONE) be = x;
    }
    printf("bounce  : %s\n", ev_name(be));

    return 0;
}