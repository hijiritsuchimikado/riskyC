#ifndef _STRUCT_BASE_H
#   define _STRUCT_BASE_H

#include "../core/base.h"

typedef struct {void *str, *end;} pd2;
typedef struct {void *str, *end, *max, *ptr;} pd4;

#define dc(x) sml(x.str, x.end)

#define s0i(x, type, num) x.end = x.str = __builtin_alloca(sz(num, type));
// WARNING: You shouldn't change the value of num here: ++, +=, ...
#define smi(x, type, num) x.end = x.str = (type*) __builtin_alloca(sz(num, type)) + ((num) >> 1)
#define s04(x, type, num)                           \
    x.ptr = __builtin_alloca(sz(num, type) + 1);    \
    x.max = (type*) (x.str = x.end = x.ptr) + (num)
    
#define mv0(x)                                      \
    __builtin_memcpy(x.ptr, x.str, x.end - x.str);  \
    x.end -= x.str - x.ptr;                         \
    x.str = x.ptr

#define pof(x, type) x.str -= dc(x) * sizeof(type)
#define pob(x, type) x.end += dc(x) * sizeof(type)
#define puf(x, type, y)     \
    x.str -= sizeof(type);  \
    *(type*) x.str = (y)
#define pub(x, type, y)     \
    *(type*) x.end = (y);   \
    x.end += sizeof(type)

#endif
