#ifndef _RD_SORT
#   define _RD_SORT

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
// only for sizeof(a[0]) % 4 != 0
#define rdsort_arr(a, n)                    \
{                                           \
    rdinit(a, n)                            \
    type(a[0]) tmp[n];                      \
    do                                      \
    {                                       \
        rdloop(a, tmp, n)                   \
        if (i >= m) {                       \
            mcp(a, tmp, n * sizeof(a[0]));  \
            break;                          \
        }                                   \
        rdloop(tmp, a, n)                   \
    } while (1);                            \
}
// only for sizeof(a[0]) % 4 != 0 and a is a pointer
#define rdsort_ptr(a, n)                    \
{                                           \
    rdinit(a, n)                            \
    type(a) tmp = alc(n * sizeof(a[0]));    \
    do                                      \
    {                                       \
        rdloop(a, tmp, n)                   \
        if (i >= m) {                       \
            a = tmp;                        \
            break;                          \
        }                                   \
        rdloop(tmp, a, n)                   \
    } while (1);                            \
}
// fastest one but only for sizeof(a[0]) % 4 == 0
#define rdsort_32(a, n)     \
{                           \
    rdinit(a, n)            \
    type(a[0]) tmp[n];      \
    do                      \
    {                       \
        rdloop(a, tmp, n)   \
        rdloop(tmp, a, n)   \
    } while (i < m);        \
}
// only works with an array of only positive or negative values 
#define rdsort(type, a, n)                      \
{                                               \
    if (!(sizeof(a[0]) & 3)) rdsort_32(a, n)    \
    else rdsort_##type(a, n)                    \
}

#endif
