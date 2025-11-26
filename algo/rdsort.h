#ifndef _RDSORT_H
#   define _RDSORT_H

#include "../core/base.h"

/*
    rdsort(type, mix_or, a, n)
    
    type: arr or ptr
    mix_or: unmixed or mixed
    a: array
    n: number of elements (must be signed)
    
    (1) When an array contains both positive and negative elements, the positive elements
    will be sorted at the beginning of the array and the negative elements will be sorted
    at the end. To solve this, the array is divided into two groups: unmixed and mixed.
    
    The unmixed group uses a two-step loop where the elements are swapped between the
    array and a temporary one. If the modulo of the size of each element by 4 is 0 or 3
    (subgroup 32), the loop will continue until the final transition from the temporary
    variable to the array. If not (subgroup ptr), use a pointer for a to avoid the need
    to write the entire temporary array back to a, but a must be a pointer. This division
    also ensures that each for-loop only has one branch.
    
    In the mixed group, it is important to note that there must be at least one negative
    element present, otherwise the program will crash. While there may be ways to manipulate
    a to avoid this issue, it is not the focus of this work. The problem (1) is addressed by
    using two memset operations for n32, one more assignment operator for ptr(32), and three memset operations for arr(32).

    TL;DR: Just use this macro!
*/

#define rdinit(a, n)            \
    typedef type(n) T;          \
    T cnt[NUM_16];              \
    int m = sizeof(a[0]) << 3,  \
    i = 0;
#define rdloop(a, tmp, n)                           \
    ms(cnt, 0, sizeof(cnt));                        \
    for (T j = 0; j < n; ++j)                       \
        ++cnt[(a[j] >> i) & 0xFFFF];                \
    for (int j = 1; j < NUM_16; ++j)                \
        cnt[j] += cnt[j - 1];                       \
    for (T j = n - 1; j >= 0; --j)                  \
        tmp[--cnt[(a[j] >> i) & 0xFFFF]] = a[j];    \
    i += 16;
#define rdcheck(a, n)       \
    i = 0;                  \
    while (a[i] >= 0) ++i;  \
    int k = n - i;
#define rdsort_unmixed_arr(a, n)            \
    rdinit(a, n)                            \
    type(a[0]) tmp[n];                      \
    do                                      \
    {                                       \
        rdloop(a, tmp, n)                   \
        if (i >= m)                         \
        {                                   \
            mcp(a, tmp, n * sizeof(a[0]));  \
            break;                          \
        } rdloop(tmp, a, n)                 \
    } while (1);
#define rdsort_unmixed_ptr(a, n)            \
    rdinit(a, n)                            \
    type(a) tmp = alc(n * sizeof(a[0]));    \
    do                                      \
    {                                       \
        rdloop(a, tmp, n)                   \
        if (i >= m)                         \
        {                                   \
            a = tmp;                        \
            break;                          \
        } rdloop(tmp, a, n)                 \
    } while (1);
#define rdsort_unmixed_32(a, n) \
    rdinit(a, n)                \
    type(a[0]) tmp[n];          \
    do                          \
    {                           \
        rdloop(a, tmp, n)       \
        rdloop(tmp, a, n)       \
    } while (i < m);
#define rdsort_mixed_arr(a, n)          \
    rdsort_unmixed_32(a, n);            \
    rdcheck(a, n)                       \
    mcp(tmp, a, i * sizeof(a[0]));      \
    mcp(a, &a[i], k * sizeof(a[0]));    \
    mcp(&a[k], tmp, i * sizeof(a[0]));
#define rdsort_mixed_ptr(a, n)              \
    rdinit(a, n)                            \
    type(a) tmp = alc(n * sizeof(a[0]));    \
    do                                      \
    {                                       \
        rdloop(a, tmp, n)                   \
        rdloop(tmp, a, n)                   \
    } while (i < m);                        \
    rdcheck(a, n)                           \
    mcp(&tmp[k], a, i * sizeof(a[0]));      \
    mcp(tmp, &a[i], k * sizeof(a[0]));      \
    a = tmp;
#define rdsort_mixed_n32(a, n)                  \
    rdinit(a, n)                                \
    type(a[0]) tmp[n];                          \
    do                                          \
    {                                           \
        rdloop(a, tmp, n)                       \
        if (i >= m)                             \
        {                                       \
            rdcheck(tmp, n)                     \
            mcp(a, &tmp[i], k * sizeof(a[0]));  \
            mcp(&a[k], tmp, i * sizeof(a[0]));  \
            break;                              \
        }                                       \
        rdloop(tmp, a, n)                       \
    } while (1);
#define rdsort_unmixed(type, a, n)                              \
    cepr((sizeof(a[0]) & 1) == ((sizeof(a[0]) >> 1) & 1),       \
    {rdsort_unmixed_32(a, n)}, {rdsort_unmixed_##type(a, n)})
#define rdsort_mixed(type, a, n)                            \
    cepr((sizeof(a[0]) & 1) == ((sizeof(a[0]) >> 1) & 1),   \
    {rdsort_mixed_##type(a, n)}, {rdsort_mixed_n32(a, n)})
    
#define rdsort(type, mix_or, a, n) rdsort_##mix_or(type, a, n)

#endif
