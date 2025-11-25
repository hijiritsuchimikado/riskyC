#ifndef _FIBONACCI_H
#   define _FIBONACCI_H

#include "logint.h"

static const inline ui_(64) fibonacci(int x)
{
    static const ui_(64) table[] =
    {
        0x0,                0x1,                0x1,                0x2,                0x3,
        0x5,                0x8,                0xd,                0x15,               0x22,
        0x37,               0x59,               0x90,               0xe9,               0x179,
        0x262,              0x3db,              0x63d,              0xa18,              0x1055,
        0x1a6d,             0x2ac2,             0x452f,             0x6ff1,             0xb520,
        0x12511,            0x1da31,            0x2ff42,            0x4d973,            0x7d8b5,
        0xcb228,            0x148add,           0x213d05,           0x35c7e2,           0x5704e7,
        0x8cccc9,           0xe3d1b0,           0x1709e79,          0x2547029,          0x3c50ea2,
        0x6197ecb,          0x9de8d6d,          0xff80c38,          0x19d699a5,         0x29cea5dd,
        0x43a53f82,         0x6d73e55f,         0xb11924e1,         0x11e8d0a40,        0x1cfa62f21,
        0x2ee333961,        0x4bdd96882,        0x7ac0ca1e3,        0xc69e60a65,        0x1415f2ac48,
        0x207fd8b6ad,       0x3495cb62f5,       0x5515a419a2,       0x89ab6f7c97,       0xdec1139639,
        0x1686c8312d0,      0x2472d96a909,      0x3af9a19bbd9,      0x5f6c7b064e2,      0x9a661ca20bb,
        0xf9d297a859d,      0x19438b44a658,     0x28e0b4bf2bf5,     0x42244003d24d,     0x6b04f4c2fe42,
        0xad2934c6d08f,     0x1182e2989ced1,    0x1c5575e509f60,    0x2dd8587da6e31,    0x4a2dce62b0d91,
        0x780626e057bc2,    0xc233f54308953,    0x13a3a1c2360515,   0x1fc6e116668e68,   0x336a82d89c937d,
        0x533163ef0321e5,   0x869be6c79fb562,   0xd9cd4ab6a2d747,   0x16069317e428ca9,  0x23a367c34e563f0,
        0x39a9fadb327f099,  0x5d4d629e80d5489,  0x96f75d79b354522,  0xf444c01834299ab,  0x18b3c1d91e77decd,
        0x27f80ddaa1ba7878, 0x40abcfb3c0325745, 0x68a3dd8e61eccfbd, 0xa94fad42221f2702
    };
    return table[x];
}
#define fibonacci_1(x)              \
({                                  \
    uintptr_t a = 0, b = 1, tmp;    \
    unsigned int y = x;             \
    int n = 1 << log2_floor(y);     \
    for (; n; n >>= 1) {            \
        tmp = ((b << 1) - a) * a;   \
        b = b * b + a * a;          \
        if (y & n) {                \
            b += tmp;               \
            tmp = b - tmp;          \
        } a = tmp;                  \
    } a;                            \
})

#endif
