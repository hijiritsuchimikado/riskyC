#ifndef _BITSET_H
#   define _BITSET_H

#include "base.h"

#define bitset ul1

#define bsp(p) ((p) >> log_lbs)
#define bsv(p) x.data[bsp(p)]
#define bp(p) (1UL << ((p) & lbsm1))
#define bss(m) (bsp(m) + 1) << log_lsz

#define bitset_init(x, max) \
    bitset x;               \
    x.data = al(bss(max));  \
    ms(x.data, 0, bss(max))
// bitset_read != 0 <=> bit == 1
#define bitset_read(x, pos) (bsv(pos) & bp(pos))
#define bitset_write_1(x, pos) bsv(pos) |= bp(pos)
#define bitset_write_0(x, pos) bsv(pos) &= ~bp(pos)

#endif

