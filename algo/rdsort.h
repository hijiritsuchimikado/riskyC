#ifndef _RD_SORT
#   define _RD_SORT

#include "../core/base.h"

// not for arrays which can't be swapped by pointers
#define rdsort(a, n)                                    \
{                                                       \
    typedef type(n) T;                                  \
    T cnt[NUM_16];                                      \
    type(a) tmp = alc(n * sizeof(a[0]));                \
    int m = sizeof(type(a[0])) << 3;                    \
    for (int i = 0; i < m; i += 16)                     \
    {                                                   \
        ms(cnt, 0, sizeof(cnt));                        \
        for (T j = 0; j < n; ++j)                       \
            ++cnt[(a[j] >> i) & 0xFFFF];                \
        for (int j = 1; j < NUM_16; ++j)                \
            cnt[j] += cnt[j - 1];                       \
        for (T j = n - 1; j >= 0; --j)                  \
            tmp[--cnt[(a[j] >> i) & 0xFFFF]] = a[j];    \
        swap(a, tmp);                                   \
    }                                                   \
}

#endif
