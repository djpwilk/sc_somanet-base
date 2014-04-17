/**
   \file com_detect.xc
   \brief Detect connected SOMANET COM module
   \author Martin Schwarz <mschwarz@synapticon.com>

   Detect the connected SOMANET COM module by measuring the discharge time of a capacitor.

   Note: This is a pretty inaccurate measurement one should not rely upon in
         productive environments. It is merely meant as convenience feature
         for initial firmware update.
*/

#include "com_detect.h"

#include <stdint.h>
#include <xclib.h>
#include <xs1.h>

//#define DEBUG_COMDETECT

#ifdef DEBUG_COMDETECT
#include <print.h>
#include <stdio.h>
#endif



/* XS1 clock settings (defined as constants for now - FIXME: read cpu regs instead */
#define REFCLK_MHZ 100

/* maximum RC time constant in ns (R = 10k, C_max = 1u) */
#define MAX_RC_DELAY_NS ( 10000 * (1000000000 / 1000000) )



/* Derived constants
   Timers are clocked from the reference clock. So we need convert nanoseconds
   to "ticks" using the reference clock speed */
#define T_REFCLK_NS    ( 1000 / REFCLK_MHZ )
#define CHARGING_DELAY ( 5 * (MAX_RC_DELAY_NS / T_REFCLK_NS) )



/* divide all delay times so that even the longest delay value fits in an uint16 */
#define DETECTION_TIMEOUT 4400000  /* equals the delay time for a 220n cap */
//#define DETECTION_TIMEOUT 9400000  /* equals the delay time for a 470n cap */
//#define DETECTION_TIMEOUT 20000000 /* equals the delay time for a 1u cap */

#define PACKING_FACTOR ((DETECTION_TIMEOUT / 65535) + 1)

#define PACK_NS(X)         ( (X) /  PACKING_FACTOR )
// #define PACK_TICKS(X)      ( (T_REFCLK_NS * X) / PACKING_FACTOR )

#define UNPACK_TO_TICKS(X) ( ((X) * PACKING_FACTOR) / T_REFCLK_NS )
// #define UNPACK_TO_NS(X)    ( (X) * PACKING_FACTOR )

typedef struct {
    uint16_t specific_delay;
    /* save a few bytes and use uint16_t instead of 32-bit enum com_module_type_t */
    uint16_t module_type;
} rc_delay_t;

static const rc_delay_t com_detect_rc_delays[] = {
    /* Nominal values in nanoseconds
       This list must be sorted in ascending order!
       Longest delay (last entry) will be used as timeout */
    { PACK_NS(     1000 ), COM_DETECT_IS_UNKNOWN },    /* C =  47p -- lower detection limit */
    { PACK_NS(     2500 ), COM_DETECT_IS_RESERVED0 },  /* C = 100p */
    { PACK_NS(     5100 ), COM_DETECT_IS_ETHERCAT },   /* C = 220p */
    { PACK_NS(    10000 ), COM_DETECT_IS_RESERVED2 },  /* C = 470p */
    { PACK_NS(    20000 ), COM_DETECT_IS_RESERVED3 },  /* C = 1n   */
    { PACK_NS(    44000 ), COM_DETECT_IS_RESERVED4 },  /* C = 2n2  */
    { PACK_NS(    94000 ), COM_DETECT_IS_RESERVED5 },  /* C = 4n7  */
    { PACK_NS(   200000 ), COM_DETECT_IS_RESERVED6 },  /* C = 10n  */
    { PACK_NS(   440000 ), COM_DETECT_IS_RESERVED7 },  /* C = 22n  */
    { PACK_NS(   940000 ), COM_DETECT_IS_RESERVED8 },  /* C = 47n  */
    { PACK_NS(  2000000 ), COM_DETECT_IS_RESERVED9 },  /* C = 100n */
    { PACK_NS( DETECTION_TIMEOUT ), COM_DETECT_IS_NONE }

//    { PACK_NS(  4400000 ), COM_DETECT_IS_RESERVED10 }, /* C = 220n */
//    { PACK_NS(  9400000 ), COM_DETECT_IS_RESERVED11 }, /* C = 470n */
//    { PACK_NS( DETECTION_TIMEOUT ), COM_DETECT_IS_NONE }  /* upper limit (timeout) */
};



/* Calculate deviations of the measured value from the next smaller and bigger values.
   -> How much bigger would the smaller nominal value have to be to match the measurement?
   -> And how much smaller would the bigger nominal value have to be? */
{ unsigned, unsigned } static inline calculate_deviations(unsigned lower_limit,
                                                          unsigned measurement,
                                                          unsigned upper_limit)
{
    /* leading zeros of the biggest number */
    uint8_t leading_zeros = clz(upper_limit);

    /* differences between measurement and between measurement and closest nominal values */
    unsigned delta_lower;
    unsigned delta_upper;

#ifdef DEBUG_COMDETECT
    printf("lts:\t%u\t\t%u\t\t%u\n", lower_limit, measurement, upper_limit);
#endif

    delta_lower = (measurement - lower_limit) << leading_zeros;
    delta_upper = (upper_limit - measurement) << leading_zeros;

    delta_lower /= lower_limit;
    delta_upper /= upper_limit;

    delta_lower = (delta_lower * 100) >> leading_zeros;
    delta_upper = (delta_upper * 100) >> leading_zeros;
#ifdef DEBUG_COMDETECT
    printf("dev:\t-----> +%u%%\t\t-%u%% <-----\n", delta_lower, delta_upper);

    if (delta_upper <= delta_lower)
        printstr("\t\t\t\t");
#endif

    return { delta_lower, delta_upper };
}


com_module_type_t com_detect(port p)
{
    const uint8_t array_len = sizeof(com_detect_rc_delays) / sizeof(com_detect_rc_delays[0]);
    const uint32_t detection_timeout =
        UNPACK_TO_TICKS ( com_detect_rc_delays[array_len - 1].specific_delay);

    timer t;
    unsigned ts_start, ts_end;
    unsigned t_result;

    /* Charge capacitor */
    p <: 1;
    t :> ts_start;
    t when timerafter (ts_start + CHARGING_DELAY) :> void;

    /* switch port to input mode (hi-z) */
    p :> void;

    /* discharge using internal port pull-down resistor */
    set_port_pull_down(p);
    t :> ts_start;

    /* Wait until capacitor voltage has dropped below high->low transition threshold voltage */
    select {
    case p when pinseq(0) :> void:
        t :> ts_end;
        break;
    case t when timerafter ( ts_start + detection_timeout ) :> ts_end:
        break;
    }

    t_result = ts_end - ts_start;

    /* reset port */
    //set_port_pull_none(p);
    stop_port(p);

    if (t_result <= UNPACK_TO_TICKS ( com_detect_rc_delays[0].specific_delay )) {
        return COM_DETECT_IS_NONE;
    }

    /* omit first element, which just sets the lower detection limit */
    uint8_t i = 1;

    while (i < array_len) {
        unsigned ticks_current_element;

        ticks_current_element = UNPACK_TO_TICKS ( com_detect_rc_delays[i].specific_delay );

        if (ticks_current_element > t_result) {
            unsigned deviation_lower;
            unsigned deviation_upper;

            { deviation_lower, deviation_upper } =
                calculate_deviations(UNPACK_TO_TICKS(com_detect_rc_delays[i-1].specific_delay),
                                     t_result,
                                     ticks_current_element);
                
            if (deviation_lower < deviation_upper) {
                return com_detect_rc_delays[i-1].module_type;
            } else {
                return com_detect_rc_delays[i].module_type;
            }
        }

       i++;
    }

    return COM_DETECT_IS_UNKNOWN;
}



