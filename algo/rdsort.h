#ifndef _RD_SORT
#   define _RD_SORT

#include "../core/base.h"

#define rdloop(a, tmp)                              \
    ms(cnt, 0, sizeof(cnt));                        \
    for (T j = 0; j < n; ++j)                       \
        ++cnt[(a[j] >> i) & 0xFFFF];                \
    for (int j = 1; j < NUM_16; ++j)                \
        cnt[j] += cnt[j - 1];                       \
    for (T j = n - 1; j >= 0; --j)                  \
        tmp[--cnt[(a[j] >> i) & 0xFFFF]] = a[j];    \
// for pointer arrays only
#define rdsort_ptr(a, n)                    \
{                                           \
    typedef type(n) T;                      \
    T cnt[NUM_16];                          \
    int m = sizeof(a[0]) << 3;              \
    type(a) tmp = alc(n * sizeof(a[0]));    \
    for (int i = 0; i < m; i += 16)         \
    {                                       \
        rdloop(a, tmp);                     \
        swap(a, tmp);                       \
    }                                       \
}
// for arrays in general, but slower
#define rdsort_arr(a, n)                    \
{                                           \
    typedef type(n) T;                      \
    T cnt[NUM_16];                          \
    int m = sizeof(a[0]) << 3;              \
    type(a[0]) tmp[n];                      \
    int i = 0;                              \
    while (1)                               \
    {                                       \
        rdloop(a, tmp);                     \
        i += 16;                            \
        if (i >= m) {                       \
            mcp(a, tmp, n * sizeof(a[0]));  \
            break;                          \
        }                                   \
        rdloop(tmp, a);                     \
        i += 16;                            \
        if (i >= m) break;                  \
    }                                       \
}
// type = ptr or arr
#define rdsort(type, a, n) rdsort_##type(a, n)

#endif
