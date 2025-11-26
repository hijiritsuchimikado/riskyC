#ifndef _RDSORT_H
#   define _RDSORT_H

#include "../core/base.h"

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
/* works with an array of only positive or negative elements */
// only for sizeof(a[0]) % 4 == 1 or 2
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
// only for sizeof(a[0]) % 4 == 1 or 2 and a is a pointer
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
// fastest one but only for sizeof(a[0]) % 4 == 0 or 3
#define rdsort_unmixed_32(a, n) \
    rdinit(a, n)                \
    type(a[0]) tmp[n];          \
    do                          \
    {                           \
        rdloop(a, tmp, n)       \
        rdloop(tmp, a, n)       \
    } while (i < m);
/*  if an array has both positive and negative elements,
    the positive ones will be sorted at the beginning of the array
    while the negative ones will be sorted at the end of the array. */
// with mixed type, there must exist at least one negative element, or the program crashes
#define rdcheck(a, n)       \
    i = 0;                  \
    while (a[i] >= 0) ++i;  \
    int k = n - i;
// only for sizeof(a[0]) % 4 == 0 or 3 
#define rdsort_mixed_arr(a, n)          \
    rdsort_unmixed_32(a, n);            \
    rdcheck(a, n)                       \
    mcp(tmp, a, i * sizeof(a[0]));      \
    mcp(a, &a[i], k * sizeof(a[0]));    \
    mcp(&a[k], tmp, i * sizeof(a[0]));  \
// only for sizeof(a[0]) % 4 == 0 or 3 and a is a pointer
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
// only for sizeof(a[0]) % 4 == 1 or 2
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
#define rdsort_unmixed(type, a, n)                          \
    if ((sizeof(a[0]) & 1) == ((sizeof(a[0]) >> 1) & 1))    \
        {rdsort_unmixed_32(a, n)}                           \
    else {rdsort_unmixed_##type(a, n)}
#define rdsort_mixed(type, a, n)                            \
    if ((sizeof(a[0]) & 1) == ((sizeof(a[0]) >> 1) & 1))    \
        {rdsort_mixed_##type(a, n)}                         \
    else {rdsort_mixed_n32(a, n)}

// type = arr or ptr, mix_or = mixed or unmixed. only use this
#define rdsort(type, mix_or, a, n) rdsort_##mix_or(type, a, n)

#endif
