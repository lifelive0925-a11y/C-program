#include <stdio.h>
#include <stdlib.h>

void my_copy(char dst[], const char src[], int n)
{
    int i;
    int j = 0;
    for(i = 0; i < n; i++)
    {
        dst[i] = src[j];
        if(src[j] != '\0')
        {
            j++;
        }
    }
    return;
}

int main()
{
    char src[] = "Hello, World!";
    char dst[20] = "Hello, Hello!";

    my_copy(dst, src, 10);

    printf("Source: %s\n", src);
    printf("Destination: %s\n", dst);

    return EXIT_SUCCESS;
}