#ifndef _BASE_H
#   define _BASE_H

#include <stdint.h>

// for builtin functions
#define ctzg(x) __builtin_ctzg(x)
#define clzg(x) __builtin_clzg(x)
#define ms(x, y, z) __builtin_memset(x, y, z)
#define alc(x) __builtin_alloca(x)

// for types
#define type(x) __typeof__(x)
#define if_(x) int_fast##x##_t
#define uif_(x) uint_fast##x##_t
#define i_(x) int##x##_t
#define ui_(x) uint##x##_t

// for constants
#define NUM_16 (1 << 16)

// WARNING: Please don't mess up these with assignment operators!
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define swap(a, b)      \
{                       \
    type(a) t = (a);    \
    (a) = (b);          \
    (b) = t;            \
}

#endif
