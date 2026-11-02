#include <stdio.h>
#include <stdlib.h>

/* 把 32 位无符号整数的二进制位倒序。
 * 以 i 的移位次数控制循环，一共 32 次，与 int 的位宽无关。 */
unsigned int reverse_bits(unsigned int value)
{
    unsigned int result = 0;
    unsigned int i;
    for(i = 1; i != 0; i<<=1)
    {
        result <<= 1;
        if(value & 1)
        {
            result |= 1;
        }
        value >>= 1;
    }
    return result;
}

int main(void)
{
    unsigned int value = 25;
    printf("%u\n", reverse_bits(value));
    return EXIT_SUCCESS;
}
