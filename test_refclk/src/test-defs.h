#pragma once

#include <stdio.h>

#define REFCLK_SETTING 125

#define TESTDATA(ENTRY)                                 \
    ENTRY(100,  1, REFCLK_NS(100))                      \
    ENTRY(100,  2, REFCLK_NS(100))                      \
    ENTRY(250,  3, REFCLK_NS(250))                      \
    ENTRY(250,  4, REFCLK_NS(250))                      \
    ENTRY(250,  5, REFCLK_NS(250))                      \
    ENTRY(100,  6, REFCLK_NS(100))                      \
    ENTRY(100,  7, REFCLK_NS(100))                      \
    ENTRY(100,  8, REFCLK_NS(100))                      \
    ENTRY(100,  9, REFCLK_NS(100))                      \
    ENTRY(100, 10, REFCLK_NS(100))                      \
    ENTRY(100, 11, REFCLK_NS(100))                      \
    ENTRY(250, 12, REFCLK_NS(250))                      \
    ENTRY(100,  1, REFCLK_US(100))                      \
    ENTRY(  0,  1, REFCLK_US())                         \
    ENTRY(250,  1, REFCLK_US(250))                      \
    ENTRY(100,  1, REFCLK_MS(100))                      \
    ENTRY(  0,  1, REFCLK_MS())                         \
    ENTRY(250,  1, REFCLK_MS(250))                      \
    ENTRY(REFCLK_SETTING, 1, REFCLK_US(REFCLK_SETTING))


#define PRINTDATA(REF, DELAY, UNIT)                                     \
    printf("%d\t" #UNIT "\t(%d MHz) \t==>\t%d\n", DELAY, REF, DELAY UNIT);

