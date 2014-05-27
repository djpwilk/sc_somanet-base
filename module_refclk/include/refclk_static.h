/**
 * \file refclk-static.h
 * \brief Static definitions of time units
 * \author Martin Schwarz <mschwarz@synapticon.com>
 */

#pragma once

#include <xs1.h>

//#ifdef PLATFORM_REFERENCE_MHZ
//#define REFCLK_DEFAULT_MHZ PLATFORM_REFERENCE_MHZ
//#else

#ifndef REFCLK_DEFAULT_MHZ
/**
   This will be used as fallback when no parameter is given to the
   REFCLK_UNIT functions. By default this is set to XS1_TIMER_MHZ.
   This value can be overriden.
*/
#define REFCLK_DEFAULT_MHZ XS1_TIMER_MHZ
#endif

//#endif



/* Preprocessor implementation of a Boolean IF statement */
#define PP_PASTE2(A,B) PP_PASTE2_(A,B)
#define PP_PASTE2_(A,B) A ## B
#define PP_IF_0(CMD_TRUE, CMD_FALSE) CMD_FALSE
#define PP_IF_1(CMD_TRUE, CMD_FALSE) CMD_TRUE
#define PP_IF(COND) PP_PASTE2(PP_IF_, COND)

/* Check if a symbol is the empty token.
   Mode of operation: INSERT_SEPARATOR() will insert "," if there is
   nothing (or only the "empty token") between the macro name and the
   "()". Counting the number of arguments tells whether the symbol is
   the empty token (there will be an additional argument in that
   case). */
#define HAS_TWO_ARGS_(A, B, C, ...) C
#define HAS_TWO_ARGS(...) HAS_TWO_ARGS_(__VA_ARGS__, 1, 0)
#define INSERT_SEPARATOR(X) ,
#define IS_EMPTY_TOKEN(T) HAS_TWO_ARGS(INSERT_SEPARATOR T ())



/* Returns default reference clock frequency in MHz (REFCLK_DEFAULT_MHZ)
   if called without parameter (T is the "empty token") or T otherwise */
#define GET_REFCLK(T) PP_IF(IS_EMPTY_TOKEN(T)) (REFCLK_DEFAULT_MHZ,T)

#define REFCLK_NS_PER_TICK(T) (1000 / GET_REFCLK(T))
#define REFCLK_PS_PER_TICK(T) (1000000 / GET_REFCLK(T))


/*
  Definitions of time units
  Usage examples:
  t when timerafter (ts + ( 100 REFCLK_US()) )
  or
  REFCLK_US(100), REFCLK_NS(REFCLK_CORE3), etc.
*/
#define REFCLK_NS(OPT_REFCLK_MHZ) / (REFCLK_NS_PER_TICK(GET_REFCLK(OPT_REFCLK_MHZ)))
#define REFCLK_US(OPT_REFCLK_MHZ) * (GET_REFCLK(OPT_REFCLK_MHZ))
#define REFCLK_MS(OPT_REFCLK_MHZ) * (1000 * GET_REFCLK(OPT_REFCLK_MHZ))
#define REFCLK_S(OPT_REFCLK_MHZ)  * (1000000 * GET_REFCLK(OPT_REFCLK_MHZ))


