#include <stdio.h>
#include <stdlib.h>

/* 手写实现 strcpy：把 src（含结尾 '\0'）复制到 dst，返回 dst 起始地址。
 * 与标准库同名函数区分开，避免和 <string.h> 里的 strcpy 冲突
 * （标准库的原型是 char *strcpy(char *dst, const char *src)，
 *  参数顺序和这里的手写版本容易混，所以统一改名。 */
char *my_strcpy(char *dst, const char *src){
    char *start = dst;
    while( *src != '\0'){
        *dst++ = *src++;
    }
    *dst = '\0';
    return start;
}

int main(void){
    char str1[] = "Hello World!";
    char str2[] = "World!";
    printf("%s\n", my_strcpy(str1, str2));
    return EXIT_SUCCESS;
}
