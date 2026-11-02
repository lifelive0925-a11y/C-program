#include <stdio.h>
#include <stdlib.h>

/* 手写实现 strlen：返回字符串长度（不含结尾的 '\0'）。
 * 标准库的签名是 size_t strlen(const char *s)，这里保持一致，
 * 否则 gcc 会报 -Wbuiltin-declaration-mismatch 警告。 */
size_t my_strlen(const char *str){
    size_t len = 0;
    while(str[len] != '\0'){
        len++;
    }
    return len;
}

int main(void){
    char str[] = "Hello, World!";
    printf("Length of the string: %zu\n", my_strlen(str));
    return EXIT_SUCCESS;
}
