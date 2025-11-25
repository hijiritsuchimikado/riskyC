#ifndef _STACK_MEM_H
#   define _STACK_MEM_H

#include <sys/resource.h>

#define stack_mem(mb)                   \
{                                       \
    struct rlimit rl;                   \
    getrlimit(RLIMIT_STACK, &rl);       \
    rl.rlim_cur = (rlim_t) mb << 20;    \
    setrlimit(RLIMIT_STACK, &rl);       \
}

#endif
