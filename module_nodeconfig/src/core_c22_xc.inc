#pragma once

#include <xs1.h>
#include <platform.h>
#include <flash.h>
/************
 * Core C22
 ************/
 /* SPI port definitions */
on stdcore[1]: fl_SPIPorts p_spi_flash = { PORT_SPI_MISO,
 								PORT_SPI_SS,
 								PORT_SPI_CLK,
 								PORT_SPI_MOSI,
 								XS1_CLKBLK_2 };
/* RGB LED */
on stdcore[1]: out port p_core_leds[3] = { XS1_PORT_1M,   /* Red */
					   XS1_PORT_1L,   /* Green */
					   XS1_PORT_1K }; /* Blue */
