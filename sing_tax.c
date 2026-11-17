#include <stdio.h>
#include <float.h>

static const float Income[] = {0, 23350, 56550, 117950, 256500, FLT_MAX};
static const float tax[] = {0, 3502.5, 12798.5, 31832.5, 81710.5};
static const float per[] = {0.15, 0.28, 0.31, 0.36, 0.396};

float single_tax(float income)
{
    int level = 0;
    for (level; income > Income[level]; level++);
    level--;
    return tax[level] + (income - Income[level]) * per[level];
}