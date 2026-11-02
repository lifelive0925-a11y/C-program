#include <stdio.h>

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
    }
    return result;
}

int main()
{
    unsigned int value = 25;
    printf("%u\n", reverse_bits(value));
    return 0;
}