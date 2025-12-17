#ifndef _RDSORT_H
#   define _RDSORT_H

/*
    rdsort(a, n, stat)

    a: array
    n: number of elements
    stat: (8/16/32/64)##(u/pst/ngt/udf)

    Optimized rdsort for specific types (8/16/32/64 bits) with four different keywords:
    + u: unsigned type.
    + pst: signed type with only positive ones.
    + ngt: signed type with only negative ones.
    + udf: signed type with undefined (positive or negative) ones.

    TL;DR: Just use this macro — it handles the tricky cases for you!
*/

#include "../core/base.h"

#define rdsbk(a, n, ls, le, vol, ksz)   \
    typedef type(n) T;                  \
    T cnt[vol], pos = 0;                \
    ms(cnt, 0, sizeof(cnt));            \
    for (T i = 0; i < n; ++i)           \
        ++cnt[(ui_(ksz)) a[i]];         \
{                                       \
    ui_(ksz) i = ls;                    \
    do                                  \
    {                                   \
        for (T j = 0; j < cnt[i]; ++j)  \
            a[pos++] = i;               \
        ++i;                            \
    } while (i != (ui_(ksz)) le);       \
}
#define rdsf sizeof(cnt)
#define rdsh rdsf >> 1
#define rdkl(a, sh) cnt[(ui_(16)) a[i]]
#define rdks(a, sh) cnt[(ui_(16)) (a[i] >> sh)]
#define rdl(a, tmp, n, cs, st, kt, is, ie, sh)          \
    ms(&cnt[cs], 0, rds##st);                           \
    for (T i = 0; i < n; ++i) ++rdk##kt(tmp, sh);       \
    for (ui_(16) i = is; i != ie; ++i)                  \
        cnt[(ui_(16)) (i + (ui_(16)) 1)] += cnt[i];     \
    for (T i = n; i--;) a[--rdk##kt(tmp, sh)] = tmp[i];
#define rdi(a, n, sz)   \
    typedef type(n) T;  \
    T cnt[65536];       \
    ui_(sz) tmp[n];     \
    rdl(tmp, a, n, 0,   \
    f, l, 0, 65535, 0)
#define rds32(a, n, cs, st, is, ie) \
    rdi(a, n, 32)                   \
    rdl(a, tmp, n, cs,              \
    st, s, is, ie, 16)
#define rds64(a, n, cs, st, is, ie) \
    rdi(a, n, 64)                   \
    rdl(a, tmp, n, 0,               \
    f, s, 0, 65535, 16)             \
    rdl(tmp, a, n, 0,               \
    f, s, 0, 65535, 32)             \
    rdl(a, tmp, n, cs,              \
    st, s, is, ie, 48)

#define rds8u(a, n) rdsbk(a, n, 0, 256, 256, 8)
#define rds8pst(a, n) rdsbk(a, n, 0, 128, 128, 8)
#define rds8ngt(a, n) rdsbk(a, n, 128, 256, 256, 8)
#define rds8udf(a, n) rdsbk(a, n, 128, 128, 256, 8)

#define rds16u(a, n) rdsbk(a, n, 0, 65536, 65536, 16)
#define rds16pst(a, n) rdsbk(a, n, 0, 32768, 32768, 16)
#define rds16ngt(a, n) rdsbk(a, n, 32768, 65536, 65536, 16)
#define rds16udf(a, n) rdsbk(a, n, 32768, 32768, 65536, 16)

#define rds32u(a, n) rds32(a, n, 0, f, 0, 65535)
#define rds32pst(a, n) rds32(a, n, 0, h, 0, 32767)
#define rds32ngt(a, n) rds32(a, n, 32768, h, 32768, 65535)
#define rds32udf(a, n) rds32(a, n, 0, f, 32768, 32767)

#define rds64u(a, n) rds64(a, n, 0, f, 0, 65535)
#define rds64pst(a, n) rds64(a, n, 0, h, 0, 32767)
#define rds64ngt(a, n) rds64(a, n, 32768, h, 32768, 65535)
#define rds64udf(a, n) rds64(a, n, 0, f, 32768, 32767)

#define rdsort(a, n, stat)  \
{                           \
    rds##stat(a, n)         \
}

#endif
