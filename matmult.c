#include <stdio.h>

void matrix_multiply(int *m1, int *m2, int *r, int x, int y, int z)
{
    for (int row = 0; row < x; row++)
    {
        for (int col = 0; col < z; col++)
        {
            int sum = 0;
            for (int i = 0; i < y; i++)
            {
                sum += *(m1 + row * y + i) * *(m2 + i * z + col);
            } 
            *(r + row * z + col) = sum;
        }
    }
}