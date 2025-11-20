#ifndef _GCD_H
#   define _GCD_H

#include "../core/base.h"

#define gcd(a, b) ({        \
    typeof(0u | (a) | (b))  \
    u = (a), v = (b), res;  \
    if (!u) res = v;        \
    else {                  \
        res = ctzg(u | v);  \
        u >>= ctzg(u);      \
        while (v) {         \
            v >>= ctzg(v);  \
            if (u > v)      \
                swap(u, v); \
            v %= u;         \
        } res = u << res;   \
    } res;                  \
})
#define lcm(a, b) ((typeof(0u | (a) | (b))) (a) / gcd(a, b) * (b))

#endif
