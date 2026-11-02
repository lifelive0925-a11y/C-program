#include <stdio.h>
#include <stdlib.h>

void *my_memcpy(void *str1, const void *str2, size_t n){
    char *st1 = (char *)str1;
    char *st2 = (char *)str2;
    void *start = str1;
    while(n--){
        *st1++ = *st2++;
        }
    return start; 
}
int main(){
    char str1[] = "Hello World!";
    char str2[] = "World!";
    my_memcpy(str1, str2, 9);
    printf("%s", str1);
    return 0;
}