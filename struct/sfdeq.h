// This is a bit safer deque implementation, with moving the whole deque if necessary
#ifndef _SFDEQ_H
#   define _SFDEQ_H

#include "base.h"

#define sfdeq pd4

#define sfdeq_init(x, type, num) sm4(x, type, num)
#define sfdeq_pop_front(x, type) pof(x, type)
#define sfdeq_pop_back(x, type) pob(x, type)
#define sfdeq_push_front(x, type, y)    \
    if (x.str == x.ptr) {mvf(x, type);} \
    puf(x, type, y)
#define sfdeq_push_back(x, type, y)     \
    if (x.end == x.max) {mvb(x, type);} \
    pub(x, type, y)

#endif
