#ifndef _BASE_H
#   define _BASE_H

#define lsz sizeof(long)
#define lbs (lsz << 3)
#define lbsm1 (lbs - 1)
#define log_lsz __builtin_ctz(lsz)
#define log_lbs (log_lsz + 3)

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)
#define swap(type, a, b)    \
    type tmp = a;           \
    a = b;                  \
    b = tmp
//return -1 (if signed) or 1 (if unsigned) when a < b, 0 when greater or equal, only for type with size of long
#define sml(a, b) (((a) - (b)) >> lbsm1)
#define sz(num, type) ((num) * sizeof(type))

#endif
