#pragma once

#include <xs1.h>
#include <platform.h>

/************
 * Core C22
 ************/

/* RGB LED */
on stdcore[1]: out port p_core_leds[3] = { XS1_PORT_1M,   /* Red */
					   XS1_PORT_1L,   /* Green */
					   XS1_PORT_1K }; /* Blue */
