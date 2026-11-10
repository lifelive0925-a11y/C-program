#include <stdio.h>

int ascii_to_integer(char *string)
{
    int result = 0;
    while (*string >= '0' && *string <= '9')
    {
        result = result * 10 + (*string - '0');
        string++;
    }
    if (*string != '\0') {
        // Handle error: non-digit character encountered
        return -1; // or some error code
    }
    return result;
}

int main() {
    char str[] = "12345";
    int num = ascii_to_integer(str);
    if (num != -1) {
        printf("The integer value is: %d\n", num);
    } else {
        printf("Error: Non-digit character encountered in the string.\n");
    }
    return 0;
}