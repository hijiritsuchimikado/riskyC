#ifndef _GCD_H
#   define _GCD_H

#include "../core/base.h"

#ifndef __OPTIMIZE__
    #define GCDATTR __attribute__((optimize("O1")))
#else
    #define GCDATTR __attribute__((optimize("no-tree-vectorize")))
#endif

#define gcd(a, b)                       \
({                                      \
    typedef type(0u | (a) | (b)) T;     \
    GCDATTR inline T gcdf(T u, T v)     \
    {                                   \
        if (u < v) swap(u, v);          \
        if (!v) return u;               \
        u %= v;                         \
        if (!u) return v;               \
        int zu = ctzg(u), zv = ctzg(v), \
        sh = min(zu, zv);               \
        u >>= zu;                       \
        v >>= zv;                       \
        do                              \
        {                               \
            T u_v = u - v;              \
            if (u > v)                  \
            {                           \
                u = v;                  \
                v = u_v;                \
            } else v = -u_v;            \
            v >>= ctzg(v);              \
        } while (v);                    \
        return u << sh;                 \
    } gcdf(a, b);                       \
})
#define lcm(a, b) ((type(0u | (a) | (b))) (a) / gcd(a, b) * (b))

#endif
