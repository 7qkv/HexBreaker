/*
 * MIT License
 * Copyright (c) 2025 qn
 */

#ifndef HEXBREAKER_HPP
#define HEXBREAKER_HPP

#if defined(_MSC_VER) && defined(_WIN64)
#include <intrin.h>

namespace hxb {
    constexpr unsigned long long hash(const char* s, unsigned long long h = 0xcbf29ce484222325ULL) {
        return *s ? hash(s + 1, (h ^ *s) * 0x100000001b3ULL) : h;
    }
    
    constexpr unsigned __int8 rnd(int c, int o) {
        unsigned long long h = hash(__DATE__ __TIME__) + c * 0x9e3779b9;
        return (unsigned __int8)((h >> (o * 8)) ^ (h >> 16));
    }
}

#define HXB_S1(C) \
{ \
    constexpr unsigned __int8 s[] = { \
        0xEB, 0x0C, \
        0x48, 0x8B, 0x84, 0x24, \
        hxb::rnd(C, 0), hxb::rnd(C, 1), hxb::rnd(C, 2), hxb::rnd(C, 3), \
        0x48, 0x31, 0xC0, \
        0xC3 \
    }; \
    if (!_AddressOfReturnAddress()) ((void(*)())(uintptr_t)s)(); \
}

#define HXB_S2(C) \
{ \
    constexpr unsigned __int8 s[] = { \
        0xEB, 0x0A, \
        0x48, 0x89, 0x8C, 0x24, \
        hxb::rnd(C+1, 0), hxb::rnd(C+1, 1), hxb::rnd(C+1, 2), hxb::rnd(C+1, 3), \
        0xC3, 0x90 \
    }; \
    if (!_AddressOfReturnAddress()) { \
        ((void(*)())(uintptr_t)s)(); \
        ((void(*)())0)(); \
    } \
}

#define HXB_S3(C) \
{ \
    constexpr unsigned __int8 s[] = { \
        0xEB, 0x0E, \
        0x48, 0x8D, 0x8C, 0x24, \
        hxb::rnd(C+2, 0), hxb::rnd(C+2, 1), hxb::rnd(C+2, 2), hxb::rnd(C+2, 3), \
        0xFF, 0x15, 0x00, 0x00, 0x00, 0x00, \
        0xC3 \
    }; \
    volatile auto p = _AddressOfReturnAddress(); \
    if (!p) ((void(*)())(uintptr_t)s)(); \
}

#define HXB_S4(C) \
{ \
    constexpr unsigned __int8 s[] = { \
        0xEB, 0x10, \
        0x48, 0x83, 0xEC, 0x28, \
        0xE8, \
        hxb::rnd(C+3, 0), hxb::rnd(C+3, 1), hxb::rnd(C+3, 2), hxb::rnd(C+3, 3), \
        0x48, 0x83, 0xC4, 0x28, \
        0xC3, 0xCC, 0xCC \
    }; \
    if (!_AddressOfReturnAddress()) ((void(*)())(uintptr_t)s)(); \
}

#define HEXBREAKER \
    do { \
        constexpr int v = __COUNTER__ % 4; \
        if constexpr (v == 0) { HXB_S1(__COUNTER__) } \
        else if constexpr (v == 1) { HXB_S2(__COUNTER__) } \
        else if constexpr (v == 2) { HXB_S3(__COUNTER__) } \
        else { HXB_S4(__COUNTER__) } \
    } while(0)

#define HXB_MAX \
    HEXBREAKER; \
    if constexpr ((__COUNTER__ & 1) == 0) { \
        volatile int x = __COUNTER__; \
        if (x == -1) ((void(*)())0)(); \
    } \
    HEXBREAKER

#define HXB_MIN \
    if (!_AddressOfReturnAddress()) __assume(0)

#else
    #define HEXBREAKER
    #define HXB_MAX
    #define HXB_MIN
#endif

#endif