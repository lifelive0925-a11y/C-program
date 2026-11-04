#include <stdio.h>
#include <stdlib.h>

void reverse_string(char *str)
{
    char *last_str = str;
    for(; *last_str != '\0'; last_str++)
        ;
    last_str--;
    while(str < last_str)
    {
        char temp = *str;
        *str++ = *last_str;
        *last_str-- = temp;
    }
    return;
}

int main()
{
    char str[] = "Hello, World!";
    reverse_string(str);
    printf("%s\n", str);
    return 0;
}