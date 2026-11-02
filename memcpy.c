#include <stdio.h>
#include <stdlib.h>

/* 手写实现 memcpy：把 src 开头的 n 个字节复制到 dst。
 * 注意：这里按字节复制，不处理内存重叠，重叠请用 memmove。 */
void *my_memcpy(void *dst, const void *src, size_t n){
    char *d = (char *)dst;
    const char *s = (const char *)src;
    void *start = dst;
    while(n--){
        *d++ = *s++;
    }
    return start;
}

int main(void){
    char str1[] = "Hello World!";
    char str2[] = "World!";
    /* 只复制 src 的长度 + 1（含结尾 '\0'）。
     * 之前写死 9 会越过 str2 的 7 字节边界，属于越界读取。 */
    size_t n = sizeof(str2);
    my_memcpy(str1, str2, n);
    printf("%s\n", str1);
    return EXIT_SUCCESS;
}
