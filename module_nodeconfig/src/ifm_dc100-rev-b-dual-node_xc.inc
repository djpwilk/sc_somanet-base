#pragma once

#include <xs1.h>
#include <platform.h>

/***************************************
 * Ifm Drive BLDC 100 B dual node setup
 **************************************/

/* ADC */
on stdcore[3]: in buffered  port:32 p_ifm_adc_misoa_node_0 = XS1_PORT_1D;
on stdcore[3]: in buffered  port:32 p_ifm_adc_misob_node_0 = XS1_PORT_1C;
on stdcore[3]: buffered out port:32 p_ifm_adc_sclk_conv_mosib_mosia_node_0 = XS1_PORT_4C;

on stdcore[7]: in buffered  port:32 p_ifm_adc_misoa_node_1 = XS1_PORT_1D;
on stdcore[7]: in buffered  port:32 p_ifm_adc_misob_node_1 = XS1_PORT_1C;
on stdcore[7]: buffered out port:32 p_ifm_adc_sclk_conv_mosib_mosia_node_1 = XS1_PORT_4C;


/* A4935 control ports */
on stdcore[3]: out port p_ifm_coastn_node_0 = XS1_PORT_1G;
on stdcore[3]: out port p_ifm_esf_rstn_pwml_pwmh_node_0 = XS1_PORT_4F;
on stdcore[3]: port p_ifm_ff1_node_0 = XS1_PORT_1H;
on stdcore[3]: port p_ifm_ff2_node_0 = XS1_PORT_1I;

on stdcore[7]: out port p_ifm_coastn_node_1 = XS1_PORT_1G;
on stdcore[7]: out port p_ifm_esf_rstn_pwml_pwmh_node_1 = XS1_PORT_4F;
on stdcore[7]: port p_ifm_ff1_node_1 = XS1_PORT_1H;
on stdcore[7]: port p_ifm_ff2_node_1 = XS1_PORT_1I;


/* BLDC Motor, default port mode */
on stdcore[3]:          in  port p_ifm_hall_node_0 = XS1_PORT_4E;
on stdcore[3]:          in  port p_ifm_encoder_node_0 = XS1_PORT_4A; /* Encoder and Button 2 */
on stdcore[3]:          in  port p_ifm_dummy_port_node_0 = XS1_PORT_16A; /* any unused port */
on stdcore[3]: buffered out port:32 p_ifm_motor_hi_node_0[3] = { XS1_PORT_1K,   /* Hi A */
							XS1_PORT_1O,   /* Hi B */
							XS1_PORT_1M }; /* Hi C */
on stdcore[3]: buffered out port:32 p_ifm_motor_lo_node_0[3] = { XS1_PORT_1L,   /* Lo A */
							  XS1_PORT_1P,   /* Lo B */
							  XS1_PORT_1N }; /* Lo C */
							  
on stdcore[7]:          in  port p_ifm_hall_node_1 = XS1_PORT_4E;
on stdcore[7]:          in  port p_ifm_encoder_node_1 = XS1_PORT_4A; /* Encoder and Button 2 */
on stdcore[7]:          in  port p_ifm_dummy_port_node_1 = XS1_PORT_16A; /* any unused port */
on stdcore[7]: buffered out port:32 p_ifm_motor_hi_node_1[3] = { XS1_PORT_1K,   /* Hi A */
							XS1_PORT_1O,   /* Hi B */
							XS1_PORT_1M }; /* Hi C */
on stdcore[7]: buffered out port:32 p_ifm_motor_lo_node_1[3] = { XS1_PORT_1L,   /* Lo A */
							  XS1_PORT_1P,   /* Lo B */
							  XS1_PORT_1N }; /* Lo C */							  


/* LEDs, Watchdog */
on stdcore[3]: out port p_ifm_shared_leds_wden_node_0 = XS1_PORT_4B; /* BlueGreenRed_WDEN */
on stdcore[7]: out port p_ifm_shared_leds_wden_node_1 = XS1_PORT_4B; /* BlueGreenRed_WDEN */


/* Expansion Port */
on stdcore[3]: port p_ifm_ext_d0_node_0 = XS1_PORT_1A;
on stdcore[3]: port p_ifm_ext_d1_node_0 = XS1_PORT_1E;
on stdcore[3]: port p_ifm_ext_d2_node_0 = XS1_PORT_1J;
on stdcore[3]: port p_ifm_ext_d3_node_0 = XS1_PORT_1B;

on stdcore[7]: port p_ifm_ext_d0_node_1 = XS1_PORT_1A;
on stdcore[7]: port p_ifm_ext_d1_node_1 = XS1_PORT_1E;
on stdcore[7]: port p_ifm_ext_d2_node_1 = XS1_PORT_1J;
on stdcore[7]: port p_ifm_ext_d3_node_1 = XS1_PORT_1B;
