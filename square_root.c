#include <stdio.h>
#include <stdlib.h>

int main()
{
    float new_guess, last_guess, num;
    printf("Enter a number: ");
    scanf("%f", &num);
    if(num < 0)
    {
        printf("Error: Cannot compute the square root of a negative number.\n");
        return EXIT_FAILURE;
    }
    new_guess = 1;
    do
    {
        last_guess = new_guess;
        new_guess = (last_guess + num / last_guess) / 2;

    }
    while (new_guess != last_guess);
    printf("The square root of %f is %f\n", num, new_guess);
    return EXIT_SUCCESS;
}