#pragma once

/*******************************************
 * Ifm Drive BLDC 100 Rev B dual node setup
 *******************************************/

/* ADC */
extern in buffered  port:32 p_ifm_adc_misoa_node_0;
extern in buffered  port:32 p_ifm_adc_misob_node_0;
extern buffered out port:32 p_ifm_adc_sclk_conv_mosib_mosia_node_0;

extern in buffered  port:32 p_ifm_adc_misoa_node_1;
extern in buffered  port:32 p_ifm_adc_misob_node_1;
extern buffered out port:32 p_ifm_adc_sclk_conv_mosib_mosia_node_1;


/* A4935 control ports */
extern out port p_ifm_coastn_node_0;
extern out port p_ifm_esf_rstn_pwml_pwmh_node_0;
extern     port p_ifm_ff1_node_0;
extern     port p_ifm_ff2_node_0;

extern out port p_ifm_coastn_node_1;
extern out port p_ifm_esf_rstn_pwml_pwmh_node_1;
extern     port p_ifm_ff1_node_1;
extern     port p_ifm_ff2_node_1;


/* BLDC Motor, default port mode */
extern           in  port p_ifm_hall_node_0;
extern           in  port p_ifm_encoder_node_0;
extern           in  port p_ifm_dummy_port_node_0; /* needed for PWM ADC-trigger timing */
extern  buffered out port:32 p_ifm_motor_hi_node_0[3]; /* = { Hi A, Hi B, Hi C } */
extern  buffered out port:32 p_ifm_motor_lo_node_0[3]; /* = { Hi A, Hi B, Hi C } */

extern           in  port p_ifm_hall_node_1;
extern           in  port p_ifm_encoder_node_1;
extern           in  port p_ifm_dummy_port_node_1; /* needed for PWM ADC-trigger timing */
extern  buffered out port:32 p_ifm_motor_hi_node_1[3]; /* = { Hi A, Hi B, Hi C } */
extern  buffered out port:32 p_ifm_motor_lo_node_1[3]; /* = { Hi A, Hi B, Hi C } */


/* LEDs, Watchdog */
extern out port p_ifm_shared_leds_wden_node_0; /* BlueGreenRed_WDEN */
extern out port p_ifm_wd_tick_node_0;

extern out port p_ifm_shared_leds_wden_node_1; /* BlueGreenRed_WDEN */
extern out port p_ifm_wd_tick_node_1;


/* Expansion Port */
extern port p_ifm_ext_d0_node_0;
extern port p_ifm_ext_d1_node_0;
extern port p_ifm_ext_d2_node_0;
extern port p_ifm_ext_d3_node_0;

extern port p_ifm_ext_d0_node_1;
extern port p_ifm_ext_d1_node_1;
extern port p_ifm_ext_d2_node_1;
extern port p_ifm_ext_d3_node_1;
