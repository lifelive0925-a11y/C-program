#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "ring.h"

static int fails = 0;

#define CHECK(cond) do { \
    if (!(cond)) { \
        printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond); \
        fails++; \
    } \
} while (0)

static void test_init(void) {
    uint8_t storage[4];
    ring r;
    ring_init(&r, storage, 4);
    CHECK(ring_size(&r) == 0);
    CHECK(ring_capacity(&r) == 4);
    CHECK(ring_empty(&r));
    CHECK(!ring_full(&r));
}

static void test_push_pop(void) {
    uint8_t storage[4];
    ring r;
    ring_init(&r, storage, 4);

    CHECK(ring_push(&r, 0xAA));
    CHECK(ring_size(&r) == 1);

    uint8_t v = 0;
    CHECK(ring_pop(&r, &v));
    CHECK(v == 0xAA);
    CHECK(ring_empty(&r));
}

static void test_empty(void) {
    uint8_t storage[4];
    ring r;
    ring_init(&r, storage, 4);

    uint8_t v = 0;
    CHECK(!ring_pop(&r, &v));
    CHECK(!ring_peek(&r, &v));
    CHECK(ring_size(&r) == 0);
}

static void test_full(void) {
    uint8_t storage[4];
    ring r;
    ring_init(&r, storage, 4);

    CHECK(ring_push(&r, 1));
    CHECK(ring_push(&r, 2));
    CHECK(ring_push(&r, 3));
    CHECK(ring_push(&r, 4));
    CHECK(ring_full(&r));
    CHECK(!ring_push(&r, 5));
    CHECK(ring_size(&r) == 4);
}

static void test_wrap(void) {
    uint8_t storage[4];
    ring r;
    ring_init(&r, storage, 4);

    CHECK(ring_push(&r, 1));
    CHECK(ring_push(&r, 2));
    CHECK(ring_push(&r, 3));

    uint8_t v = 0;
    CHECK(ring_pop(&r, &v)); CHECK(v == 1);
    CHECK(ring_pop(&r, &v)); CHECK(v == 2);

    CHECK(ring_push(&r, 4));
    CHECK(ring_push(&r, 5));
    CHECK(ring_push(&r, 6));
    CHECK(ring_full(&r));

    uint8_t expect[] = {3, 4, 5, 6};
    for (int i = 0; i < 4; i++) {
        CHECK(ring_pop(&r, &v));
        CHECK(v == expect[i]);
    }
    CHECK(ring_empty(&r));
}

static void test_peek(void) {
    uint8_t storage[4];
    ring r;
    ring_init(&r, storage, 4);

    CHECK(ring_push(&r, 7));
    uint8_t v = 0;
    CHECK(ring_peek(&r, &v));
    CHECK(v == 7);
    CHECK(ring_size(&r) == 1);

    CHECK(ring_pop(&r, &v));
    CHECK(v == 7);
}

static void test_clear(void) {
    uint8_t storage[4];
    ring r;
    ring_init(&r, storage, 4);

    CHECK(ring_push(&r, 1));
    CHECK(ring_push(&r, 2));
    ring_clear(&r);

    CHECK(ring_empty(&r));
    CHECK(ring_size(&r) == 0);

    uint8_t v = 0;
    CHECK(!ring_pop(&r, &v));
}

static void test_cap_zero(void) {
    uint8_t dummy[1];
    ring r;
    ring_init(&r, dummy, 0);

    CHECK(ring_capacity(&r) == 0);
    CHECK(ring_empty(&r));
    CHECK(!ring_full(&r));
    CHECK(!ring_push(&r, 1));

    uint8_t v = 0;
    CHECK(!ring_pop(&r, &v));
}

static void test_null(void) {
    uint8_t v = 0;
    CHECK(!ring_push(NULL, 1));
    CHECK(!ring_pop(NULL, &v));
    CHECK(!ring_peek(NULL, &v));
    CHECK(ring_size(NULL) == 0);
    CHECK(ring_empty(NULL));
}

int main(void) {
    test_init();
    test_push_pop();
    test_empty();
    test_full();
    test_wrap();
    test_peek();
    test_clear();
    test_cap_zero();
    test_null();

    if (fails) {
        printf("%d test(s) failed\n", fails);
        return 1;
    }
    puts("all tests passed");
    return 0;
}