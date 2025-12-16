#ifndef _RDSORT_H
#   define _RDSORT_H

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
#define rdks(a, sh) cnt[(ui_(16)) a[i]]
#define rdkm(a, sh) cnt[(ui_(16)) (a[i] >> sh)]
#define rdke(a, sh) cnt[a[i] >> sh]
#define rdl(a, tmp, n, cs, cz, rdk, is, ie, sh)     \
    ms(&cnt[cs], 0, cz);                            \
    for (T i = 0; i < n; ++i) ++rdk(tmp, sh);       \
    for (ui_(16) i = is; i != ie; ++i)              \
        cnt[(ui_(16)) (i + (ui_(16)) 1)] += cnt[i]; \
    for (T i = n; i--;) a[--rdk(tmp, sh)] = tmp[i];
#define rdi(a, n, sz)       \
    typedef type(n) T;      \
    T cnt[65536];           \
    ui_(sz) tmp[n];         \
    rdl(tmp, a, n, 0, rdsf  \
    , rdks, 0, 65535, 0)
#define rdi8(a, n)          \
    rdi(a, n, 64)           \
    rdl(a, tmp, n, 0, rdsf  \
    , rdkm, 0, 65535, 16)   \
    rdl(tmp, a, n, 0, rdsf  \
    , rdkm, 0, 65535, 32)   \

#define rdsu8(a, n) rdsbk(a, n, 0, 256, 256, 8)
#define rds8pst(a, n) rdsbk(a, n, 0, 128, 128, 8)
#define rds8ngt(a, n) rdsbk(a, n, 128, 256, 256, 8)
#define rds8udf(a, n) rdsbk(a, n, 128, 128, 256, 8)

#define rdsu16(a, n) rdsbk(a, n, 0, 65536, 65536, 16)
#define rds16pst(a, n) rdsbk(a, n, 0, 32768, 32768, 16)
#define rds16ngt(a, n) rdsbk(a, n, 32768, 65536, 65536, 16)
#define rds16udf(a, n) rdsbk(a, n, 32768, 32768, 65536, 16)

#define rdsu32(a, n)        \
    rdi(a, n, 32)           \
    rdl(a, tmp, n, 0, rdsf  \
    , rdke, 0, 65535, 16)
#define rds32pst(a, n)      \
    rdi(a, n, 32)           \
    rdl(a, tmp, n, 0, rdsh  \
    , rdke, 0, 32767, 16)
#define rds32ngt(a, n)          \
    rdi(a, n, 32)               \
    rdl(a, tmp, n, 32768, rdsh  \
    , rdke, 32768, 65535, 16)
#define rds32udf(a, n)      \
    rdi(a, n, 32)           \
    rdl(a, tmp, n, 0, rdsf, \
    rdke, 32768, 32767, 16)

#define rdsu64(a, n)        \
    rdi8(a, n)              \
    rdl(a, tmp, n, 0, rdsf  \
    , rdke, 0, 65535, 48)
#define rds64pst(a, n)      \
    rdi8(a, n)              \
    rdl(a, tmp, n, 0, rdsh  \
    , rdke, 0, 32767, 48)
#define rds64ngt(a, n)          \
    rdi8(a, n)                  \
    rdl(a, tmp, n, 32768, rdsh  \
    , rdke, 32768, 65535, 48)
#define rds64udf(a, n)      \
    rdi8(a, n)              \
    rdl(a, tmp, n, 0, rdsf, \
    rdke, 32768, 32767, 48)

#define rdsort(a, n, stat)  \
{                           \
    rds##stat(a, n)         \
}

#endif
