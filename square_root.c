#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 用牛顿迭代法求平方根：x(n+1) = (x(n) + num / x(n)) / 2
 * x(0) 取 1，收敛后与真实值的误差在 1e-6 以内。 */
double square_root(double num)
{
    double guess = 1.0;
    double next;
    int i;

    if (num < 0) {
        return -1.0;   /* 负数由调用者拦截，这里做个保险 */
    }
    if (num == 0) {
        return 0.0;    /* 0 要单独处理，否则 num / guess 会出现 0 / 0 = NaN */
    }

    /* 用「误差小于 1e-6」作为退出条件，而不是「两次结果完全相等」。
     * 浮点数很难恰好相等，用 != 比较既可能提前退出也可能死循环。
     * 再加一个最大迭代次数兜底。 */
    for (i = 0; i < 1000; i++) {
        next = (guess + num / guess) / 2.0;
        if (fabs(next - guess) < 1e-6) {
            return next;
        }
        guess = next;
    }
    return guess;
}

int main(void)
{
    double num;

    printf("Enter a number: ");
    if (scanf("%lf", &num) != 1) {
        printf("Error: invalid input.\n");
        return EXIT_FAILURE;
    }
    if (num < 0) {
        printf("Error: Cannot compute the square root of a negative number.\n");
        return EXIT_FAILURE;
    }

    printf("The square root of %f is %f\n", num, square_root(num));
    return EXIT_SUCCESS;
}
