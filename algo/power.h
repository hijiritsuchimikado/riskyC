#ifndef _POWER_H
#   define _POWER_H

#define power(type, base, power)    \
({                                  \
    type a = base, res = 1;         \
    for (int b = power; b; b >>= 1) \
    {                               \
        if (b & 1) res *= a;        \
        a *= a;                     \
    } res;                          \
})
#define power_mod(type, base, power, mod)   \
({                                          \
    type a = base % mod, res = 1;           \
    for (int b = power; b; b >>= 1)         \
    {                                       \
        if (b & 1) res = res * a % mod;     \
        a = a * a % mod;                    \
    } res;                                  \
})

#endif
