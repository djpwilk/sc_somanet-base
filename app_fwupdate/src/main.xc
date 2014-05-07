
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
	chan c_nodes[17];   // only upto 17 nodes on dx can have firmware updated - with current implementation structure

	par
	{
		/* Ethercat Communication Handler Loop */
		/*on stdcore[COM_TILE] :
		{
			ecat_init();
			ecat_handler(coe_out, coe_in, eoe_out, eoe_in, eoe_sig, foe_out, foe_in, pdo_out, pdo_in);
		}

		 Firmware Update Loop
		on stdcore[COM_TILE] :
		{
			firmware_update_loop(p_spi_flash, foe_out, foe_in, c_flash_data, c_nodes, sig_1); // firmware update over ethercat
		}

		on stdcore[1]:
		{
		    timer t;
		    int time;
		    int i = 7;
		    // Set LED to green
		    p_core_leds[0] <: 1;
		    p_core_leds[1] <: 0;
		    p_core_leds[2] <: 1;
		    while(1);
		}

		on stdcore[COM_TILE] :
		{
		    int data_length = 256;
		    int page = 0, i;
		    unsigned char data[256];
		    int status;
		    for(i = 0; i < data_length; i++)
		    {
		        data[i] = 0x19;
		    }

		    // Store data on to flash
		    status = write_data_to_flash(c_flash_data, page, data, data_length);
		    printintln(status);
		    for ( i = 0; i < 256; i++ )
            {
                data[i] = 0;
            }

		    // Retrieve data from flash
		    status = read_data_flash(c_flash_data, page, data, data_length);
		    for ( i = 0; i < 256; i++ )
		    {
		        printhexln(data[i]);
		    }
		}*/

	    on stdcore[1]:
	    {
	        unsigned char data_array[256] = {0};
	        int param = 0xf1f2f3f3;
	        int param_read;
	        int i, k, no_of_data = 2;


	        // store data and update flag bit at 5th byte
	        for(i = 0, k = 0; i < 5*no_of_data; i = i + 5, k++)
	        {
	            store_data_array(i, param, data_array);
	            data_array[4 + 5*(k/8)] = data_array[4 + 5*(k/8)] | 1<<(k%8);
	        }


	        // read data
	        for(int i = 0, k= 0; i < 40; i = i + 5, k++)
	        {
	            param_read = read_data_array(i, data_array);
	            if( (data_array[4 + 5*(k/8)] & 1<<(k%8)) >> (k%8) ) // updated
	                printhexln(param_read);
	        }

	    }

	}

	return 0;
}


