#ifndef _DEQUE_H
#   define _DEQUE_H

#include "base.h"

#define deque pd2

#define deque_init(x, type, num) smi(x)
#define deque_pop_front(x, type) pof(x)
#define deque_pop_back(x, type) pob(x)
#define deque_push_front(x, type, y) puf(x)
#define deque_push_back(x, type, y) pub(x)

#endif
