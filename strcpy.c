#include <stdio.h>
#include <stdlib.h>

char *strcpy(char *str1, const char *str2){
    char *start = str1;
    while( *str2 != '\0'){
        *str1++ = *str2++;
    }
    *str1 = '\0';
    return start;
}
int main(){
    char str1[] = "Hello World!";
    char str2[] = "World!";
    printf("%s", strcpy(str1, str2));
    return 0;
}