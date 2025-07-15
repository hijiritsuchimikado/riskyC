#ifndef _GCD_H
#   define _GCD_H

#define gcd(type, a, b) ({  \
    type _a = a, _b = b;    \
    for (; _b;) {           \
        _a %= _b;           \
        if (!_a) break;     \
        _b %= _a;           \
    }                       \
    _a + _b;                \
})
#define lcm(type, a, b) ((type) (a) * (b) / gcd(type, a, b))

#endif
