#ifndef _DEQUE_H
#   define _DEQUE_H

#include "base.h"

#define deque pd2

#define deque_init(x, type, num) smi(x, type, num)
#define deque_pop_front(x, type) pof(x, type)
#define deque_pop_back(x, type) pob(x, type)
#define deque_push_front(x, type, y) puf(x, type, y)
#define deque_push_back(x, type, y) pub(x, type, y)

#endif
