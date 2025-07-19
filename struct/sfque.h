// This is a bit safer queue implementation, with moving the whole queue to initialized address if necessary
#ifndef _SFQUE_H
#   define _SFQUE_H

#include "base.h"

#define sfque pd4

#define sfque_init(x, type, num) s04(x, type, num)
#define sfque_pop(x, type) pof(x, type)
#define sfque_push(x, type, y)      \
    if (x.end == x.max) {mv0(x);}   \
    pub(x, type, y)

#endif
