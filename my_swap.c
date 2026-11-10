#include <stdio.h>

void my_swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int x = 5;
    int y = 10;

    printf("Before swap: x = %d, y = %d\n", x, y);
    my_swap(&x, &y);
    printf("After swap: x = %d, y = %d\n", x, y);

    return 0;
}