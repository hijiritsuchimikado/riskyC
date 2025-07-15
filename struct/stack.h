#ifndef _STACK_H
#   define _STACK_H

#include "base.h"

#define stack pd2

#define stack_init(x, type, num) s0i(x, type, num)
#define stack_pop(x, type) pob(x, type)
#define stack_push(x, type, y) pub(x, type, y)

#endif
