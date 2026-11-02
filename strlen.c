#include <stdio.h>
#include <stdlib.h>

int strlen(char *str){
    int len = 0;
    while(str[len] != '\0'){
        len++;
    }
    return len;
}
int main(){
    char str[] = "Hello, World!";
    printf("Length of the string: %d\n", strlen(str));
    return 0;
}