#ifndef _STRUCT_BASE_H
#   define _STRUCT_BASE_H

#include "../core/base.h"

// two-pointer, four-pointer and one-pointer unsigned long data
typedef struct {void *str, *end;} pd2;
typedef struct {void *str, *end, *max, *ptr;} pd4;
typedef struct {unsigned long *data;} ul1;

#define al(x) __builtin_alloca(x)
// alloc one element and n elements
#define al1(type) al(sizeof(type))
#define aln(num, type) al(sz(num, type))
// memset, only works with val == 0 || -1
#define ms(x, val, size) __builtin_memset(x, val, size)
// memcpy and memmove from y to x
#define mcp(x, y, size) __builtin_memcpy(x, y, size)
#define mmv(x, y, size) __builtin_memmove(x, y, size)

#define dc(x) sml(x.str, x.end)

// start and end from 0
#define s0i(x, type, num)   \
    pd2 x;                  \
    x.end = x.str = aln(num, type)
// WARNING: You shouldn't change the value of num here: ++, +=, ...
// _________________________________________________________________
// start and end from middle
#define smi(x, type, num)   \
    pd2 x;                  \
    x.end = x.str = (type*) aln(num, type) + ((num) >> 1)
// start, end and pointer from 0, max at last
#define s04(x, type, num)           \
    pd4 x;                          \
    x.ptr = al(sz(num, type) + 1);  \
    x.max = (type*) (x.str = x.end = x.ptr) + (num)
// start and end from middle, pointer from 0 and max at last
#define sm4(x, type, num)           \
    pd4 x;                          \
    x.ptr = al(sz(num, type) + 1);  \
    x.max = (type*) x.ptr + (num);  \
    x.str = x.end = (type*) x.ptr + ((num) >> 1)
// _________________________________________________________________
// move to the position 0 to push back
#define mv0(x)                          \
    mcp(x.ptr, x.str, x.end - x.str);   \
    x.end -= x.str - x.ptr;             \
    x.str = x.ptr
// move front/back to be able to push front/back
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

// pop front, pop back, push front and push back
#define pof(x, type) x.str -= dc(x) * sizeof(type)
#define pob(x, type) x.end += dc(x) * sizeof(type)
#define puf(x, type, y)     \
    x.str -= sizeof(type);  \
    *(type*) x.str = (y)
#define pub(x, type, y)     \
    *(type*) x.end = (y);   \
    x.end += sizeof(type)

#endif
