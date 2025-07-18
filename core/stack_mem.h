#ifndef _STACK_MEM_H
#   define _STACK_MEM_H

#include <sys/resource.h>

// return 0 <=> succeed in changing available stack memory size
#define stack_mem(mb) ({                    \
    struct rlimit rl;                       \
    getrlimit(RLIMIT_STACK, &rl);           \
    rl.rlim_cur = (unsigned long) mb << 20; \
    setrlimit(RLIMIT_STACK, &rl);           \
})

#endif
