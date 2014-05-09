
/**
 * \file main.xc
 * \brief Example application for flashing binary file over ethercat
 * \author Pavan Kanajar <pkanajar@synapticon.com>
 * \author Frank Jeschke <jeschke@fjes.de>
 * \version 1.0
 * \date 10/04/2014
 */

#include <xs1.h>
#include <platform.h>
#include <print.h>
#include <stdio.h>
#include <stdint.h>
#include <flash_somanet.h>
#include <ethercat.h>
#include <ioports.h>

#define COM_TILE 0

int main(void)
{
	/* EtherCat Communication channels */
	chan coe_in;  	 	// CAN from module_ethercat to consumer
	chan coe_out;  		// CAN from consumer to module_ethercat
	chan eoe_in;   		// Ethernet from module_ethercat to consumer
	chan eoe_out;  		// Ethernet from consumer to module_ethercat
	chan eoe_sig;
	chan foe_in;   		// File from module_ethercat to consumer
	chan foe_out;  		// File from consumer to module_ethercat
	chan pdo_in;
	chan pdo_out;
	chan sig_1;
	chan c_flash_data;
	chan c_nodes[2];   // only upto 17 nodes on dx can have firmware updated - with current implementation structure

	par
	{
		/* Ethercat Communication Handler Loop */
		on tile[COM_TILE] :
		{
			ecat_init();
			ecat_handler(coe_out, coe_in, eoe_out, eoe_in, eoe_sig, foe_out, foe_in, pdo_out, pdo_in);
		}

		/* Firmware Update Loop */
		on tile[COM_TILE] :
		{
			firmware_update_loop(p_spi_flash, foe_out, foe_in, c_flash_data, c_nodes, sig_1); // firmware update over ethercat
		}

		on tile[1]:
		{
		    // Set LED to green
		    p_core_leds[0] <: 1;
		    p_core_leds[1] <: 0;
		    p_core_leds[2] <: 1;
		    while(1);
		}
	}
	return 0;
}


