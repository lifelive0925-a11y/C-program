#include <stdio.h>
#include <stdlib.h>

/* 类似 strncpy 的拷贝：最多往 dst 写 n 个字符。
 * 如果 src 短于 n，剩余位置用 '\0' 填充；
 * 如果 src 不短于 n，则不会补 '\0'，需要调用者自己处理。
 * 注意 j 在遇到 '\0' 之后就不再自增，所以后面的位置会被 '\0' 填满。 */
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

int main(void)
{
    char src[] = "Hello, World!";
    char dst[20] = "Hello, Hello!";

    /* 只拷前 10 个字符（不含 '\0'），所以 dst 里原本第 11 位的 'l' 被覆盖成 'o'。
     * 想让 dst 成为完整的字符串，应该传 sizeof(dst) 或 n >= strlen(src) + 1。 */
    my_copy(dst, src, 10);

    printf("Source: %s\n", src);
    printf("Destination: %s\n", dst);

    return EXIT_SUCCESS;
}
