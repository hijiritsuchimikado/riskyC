#ifndef _BITSET_H
#   define _BITSET_H

#include "../core/base.h"

typedef struct {unsigned long *data;} bitset;

#define bsp(p) ((p) >> log_lbs)
#define bsv(x, p) x.data[bsp(p)]
#define bp(p) (1UL << ((p) & lbsm1))
#define bss(m) (bsp(m) + 1) << log_lsz

#define bitset_init(x, max)             \
    x.st = __builtin_alloca(bss(max));  \
    __builtin_memset(x.st, 0, bss(max))
// bitset_read != 0 <=> bit == 1
#define bitset_read(x, pos) (bsv(x, pos) & bp(pos))
#define bitset_write_1(x, pos) bsv(x, pos) |= bp(pos)
#define bitset_write_0(x, pos) bsv(x, pos) &= ~bp(pos)

#endif

