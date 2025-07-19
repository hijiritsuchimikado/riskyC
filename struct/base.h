#ifndef _STRUCT_BASE_H
#   define _STRUCT_BASE_H

#include "../core/base.h"

typedef struct {void *str, *end;} pd2;
typedef struct {void *str, *end, *max, *ptr;} pd4;
typedef struct {unsigned long *data;} ul1;

#define al(x) __builtin_alloca(x)
#define al1(type) al(sizeof(type))
#define aln(num, type) al(sz(num, type))
// only works with num == 0 || -1
#define ms(x, num, type) __builtin_memset(x, num, sz(num, type))
#define mcp(x, y, size) __builtin_memcpy(x, y, size)
#define mmv(x, y, size) __builtin_memmove(x, y, size)

#define dc(x) sml(x.str, x.end)

#define s0i(x, type, num) x.end = x.str = aln(num, type)
// WARNING: You shouldn't change the value of num here: ++, +=, ...
// _____________________________________________________________________________
#define smi(x, type, num) x.end = x.str = (type*) aln(num, type) + ((num) >> 1)
#define s04(x, type, num)                           \
    x.ptr = al(sz(num, type) + 1);                  \
    x.max = (type*) (x.str = x.end = x.ptr) + (num)
#define sm4(x, type, num)                           \
    x.ptr = al(sz(num, type) + 1);                  \
    x.max = (type*) x.ptr + (num);                  \
    x.str = x.end = (type*) x.ptr + ((num) >> 1)
// ______________________________________________________________________________________________
#define mv0(x)                          \
    mcp(x.ptr, x.str, x.end - x.str);   \
    x.end -= x.str - x.ptr;             \
    x.str = x.ptr
#define mvf(x, type)                                                        \
    void *k = (type*) x.str + (((type*) x.max - (type*) x.end + 1) >> 1);   \
    mmv(k, x.str, x.end - x.str);                                           \
    x.end += k - x.str;                                                     \
    x.str = k
#define mvb(x, type)                                                    \
    void *k = (type*) x.ptr + (((type*) x.str - (type*) x.ptr) >> 1);   \
    mcp(k, x.str, x.end - x.str);                                       \
    x.end += k - x.str;                                                 \
    x.str = k

#define pof(x, type) x.str -= dc(x) * sizeof(type)
#define pob(x, type) x.end += dc(x) * sizeof(type)
#define puf(x, type, y)     \
    x.str -= sizeof(type);  \
    *(type*) x.str = (y)
#define pub(x, type, y)     \
    *(type*) x.end = (y);   \
    x.end += sizeof(type)

#endif
