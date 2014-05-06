#pragma once

#include <xs1.h>
#include <platform.h>

/**********************
 * Ifm Drive BLDC 100
 **********************/

/* ADC */
on tile[3]: in buffered  port:32 p_ifm_adc_misoa = XS1_PORT_1D;
on tile[3]: in buffered  port:32 p_ifm_adc_misob = XS1_PORT_1C;
on tile[3]: buffered out port:32 p_ifm_adc_sclk_conv_mosib_mosia = XS1_PORT_4C;

/* A4935 control ports */
on tile[3]: port p_ifm_coastn = XS1_PORT_1G;
on tile[3]: out port p_ifm_esf_rstn_pwml_pwmh = XS1_PORT_4F;
on tile[3]: port p_ifm_ff1 = XS1_PORT_1H;
on tile[3]: port p_ifm_ff2 = XS1_PORT_1I;

/* BLDC Motor, default port mode */
on tile[3]:          in  port p_ifm_hall = XS1_PORT_4E;
on tile[3]:          in  port p_ifm_encoder = XS1_PORT_4A; /* Encoder and Button 2 */
on tile[3]:          in  port p_ifm_dummy_port = XS1_PORT_16B; /* any unused port */
on tile[3]: buffered out port:32 p_ifm_motor_hi[3] = { XS1_PORT_1K,   /* Hi A */
							XS1_PORT_1O,   /* Hi B */
							XS1_PORT_1M }; /* Hi C */
on tile[3]: buffered out port:32 p_ifm_motor_lo[3] = { XS1_PORT_1L,   /* Lo A */
							  XS1_PORT_1P,   /* Lo B */
							  XS1_PORT_1N }; /* Lo C */
/* BLDC Motor, alternative declaration for low-side PWM */
//on tile[3]: out port p_ifm_motor_hi[3] = { XS1_PORT_1K,   /* Hi A */
//					      XS1_PORT_1O,   /* Hi B */
//					      XS1_PORT_1M }; /* Hi C */
//on tile[3]: out port p_ifm_motor_lo[3] = { XS1_PORT_1L,   /* Lo A */
//					      XS1_PORT_1P,   /* Lo B */
//					      XS1_PORT_1N }; /* Lo C */

/* LEDs, Watchdog */
on tile[3]: out port p_ifm_shared_leds_wden = XS1_PORT_4B; /* BlueGreenRed_WDEN */
on tile[3]: out port p_ifm_wd_tick = XS1_PORT_1F; /* WatchdogTick */

/* Expansion Port */
on tile[3]: port p_ifm_ext_d[4] ={ XS1_PORT_1A,
									  XS1_PORT_1E,
									  XS1_PORT_1J,
									  XS1_PORT_1B };

