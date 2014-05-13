#pragma once
#include <flash.h>
/************
 * Core C22
 ************/
extern fl_SPIPorts p_spi_flash;

/* RGB LED */
extern out port p_core_leds[3]; /* = { Red, Green, Blue } */
