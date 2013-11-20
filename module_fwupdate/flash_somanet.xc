
/**
 *
 * \file flash_somanet.xc
 *
 * \brief Somanet Firmware Update implemtation
 *
 *
 * Copyright (c) 2013, Synapticon GmbH
 * All rights reserved.
 * Author: Frank Jeschke <jeschke@fjes.de> & Pavan Kanajar <pkanajar@synapticon.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Execution of this software or parts of it exclusively takes place on hardware
 *    produced by Synapticon GmbH.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the Synapticon GmbH.
 *
 */

#include <platform.h>
#include <stdio.h>
#include <flash_somanet.h>

#define START_FLASH 12;
#define END_FLASH 26;
#define FLASH 1;
#define IDLE 0;


/* initializers defined in XN file
* and available via somanet header files */
// SPI port definitions

on stdcore[0]:fl_SPIPorts SPI = { PORT_SPI_MISO,
 					PORT_SPI_SS,
 					PORT_SPI_CLK,
 					PORT_SPI_MOSI,
 					XS1_CLKBLK_2 };

int write_state = IDLE;
int start_flash = START_FLASH;
int end_flash = END_FLASH;
int flash1 = FLASH;


//open SPI connection routine called in flash_write routine

int flash_connect() {
  int res;
  res = fl_connect(SPI);
  if( res != 0 ) {
    return(0);
  }
  return 1;
}

extern void flash_setup(int factory);// with params as file path & name

void chipReset(void)				//	auto reset from software
{
	unsigned x;
	read_sswitch_reg(get_core_id(), 6, x);
	write_sswitch_reg(get_core_id(), 6, x);
}



int check_file_access(chanend foe_comm, unsigned address, chanend reset_out)
{
	char buffer[BUFFER_SIZE];
	unsigned i=0;
	int ctmp;
	unsigned size;

	foe_comm <: FOE_FILE_READ;
	foe_comm <: BUFFER_SIZE;
	foe_comm :> ctmp;

	switch (ctmp)
	{
		case FOE_FILE_DATA:
			foe_comm :> ctmp;
			size = (unsigned int)ctmp;
		//	printhexln(ctmp);
			if(size==2)
			{
				for (i=0; i<size; i++) {
					foe_comm :> ctmp;
					if(i==0)
					{
						if(ctmp == 0x34)
						{
							write_state = start_flash;
							//flash_setup(1);
							//address=0;
						}
						else if(ctmp == 0x99)
						{
							write_state = IDLE;
							flash_buf_end();
							//reset_out <: 1;
						}
					}
				}
			}
			else if(size>=100)
			{

				if(write_state == start_flash)
				{
					flash_setup(1);
					address=0;
					write_state = flash1;
				}

				for (i=0; i<size; i++)
				{
					foe_comm :> ctmp;
					buffer[i]=ctmp;
				}
				//printhex(ctmp);
				flash_buffer(buffer, size, address);
				address+=size;
			}
			break;

		case FOE_FILE_ERROR:
			//printstr("\nfoe error\n");
			//FIXME needs handling
			break;

		default:
				break;
	}

	/* clean up file system to permit next foe transfere*/

	foe_comm <: FOE_FILE_FREE;
	foe_comm :> ctmp;

	switch (ctmp)
	{
		case FOE_FILE_ACK:
			//printstr("[check_file_access()] filesystem is clear again\n");
			break;
		case FOE_FILE_ERROR:
			//printstr("[check_file_access()] error during filesystem clean up\n"); //FIXME needs handling
			break;
		default:
			//printstr("[check_file_access()] unknon return value\n");
			break;
	}
	return (int)address;
}


extern void firmware_update(chanend foe_comm, chanend foe_signal, chanend reset)
{
	timer t;
	unsigned time = 0;
	unsigned delay = 100000;
	char name[] = "test";
	unsigned i=0;
	int ctmp=0;
	int notification=0;
	unsigned address=0;

	/* wait some time until ethercat handler is ready */
	t :> time;
	t when timerafter(time+delay) :> void;

	while (1)
	{
		foe_signal :> notification;

		if (notification != FOE_FILE_READY) {
			t :> time;
			t when timerafter(time+delay) :> void;
			continue;
		}

		/* check if a file is present, FIXME: this could be realized by the signaling channel! */
		foe_comm <: FOE_FILE_OPEN;
		i=-1;
		do {
			i++;
			foe_comm <: (int)name[i];
		} while (name[i] != '\0');

		foe_comm :> ctmp;
		switch (ctmp) {
		case FOE_FILE_ERROR:
			//printstr("Error file is not ready\n");
			break;

		case FOE_FILE_ACK:
			/* File is ready read it and print to std. out */
			address = check_file_access(foe_comm, address, reset);
			break;

		default:
			//printstr("Unknown state returned\n");
			break;
		}

		//t :> time;
		//t when timerafter(time+delay) :> void;
	}
}



/* request a file from the master */   /// firmware update ///
extern void get_file(chanend foe_out, char filename[])
{
	unsigned i, pos=0;
	//unsigned outBuffer[20];
	//outBuffer[1] = REQUEST_FILE;p

	for (i=0, pos=2; filename[i] != '\n'; i++, pos++) {
		//outBuffer[pos++] = filename[i];p
	}

	//outBuffer[0] = pos;p

	for (i=0; i<pos; i++) {
		//foe_out <: outBuffer[i];p
	}
}



void reset_cores(chanend sig_in, chanend sig_out)
{
	int read;
	timer tmr1;
	unsigned time=0, delay=100000;

	while(1)
	{
		sig_in:>read;
		if(read==1)
		{
			sig_out <: read;
			tmr1 :> time;
			tmr1 when timerafter(time+delay) :> void;
			chipReset();
			break;
		}
	}
}

void reset_last_core(chanend sig_in)
{
	int read;
	timer tmr1;
	unsigned time=0, delay=100000;
	while(1)
	{
		sig_in:>read;
		if(read==1)
		{
			tmr1 :> time;
			tmr1 when timerafter(time+delay) :> void;
			chipReset();
			break;
		}
	}
}


