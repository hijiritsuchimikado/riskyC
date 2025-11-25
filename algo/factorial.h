#ifndef _FACTORIAL_H
#   define _FACTORIAL_H

#include "../core/base.h"

static const inline ui_(64) factorial(int x)
{
    static const ui_(64) table[] =
    {
        0x1,              0x1,               0x2,
        0x6,              0x18,              0x78,
        0x2d0,            0x13b0,            0x9d80,
        0x58980,          0x375f00,          0x2611500,
        0x1c8cfc00,       0x17328cc00,       0x144c3b2800,
        0x13077775800,    0x130777758000,    0x1437eeecd8000,
        0x16beecca730000, 0x1b02b9306890000, 0x21c3677c82b40000
    };
    return table[x];
}

#endif
