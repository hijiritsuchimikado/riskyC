#ifndef _QUEUE_H
#   define _QUEUE_H

#include "base.h"

#define queue pd2

#define queue_init(x, type, num) s0i(x, type, num)
#define queue_pop(x, type) pof(x, type)
#define queue_push(x, type, y) pub(x, type, y)

#endif
