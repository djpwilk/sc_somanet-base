
/*
 * Flash_fac_upgrade.xc
 *
 *  Jun 15, 2012
 *  Author: Pavan Kanajar <pkanajar@synapticon.com>
 */


#include <platform.h>
#include <flash.h>
#include <stdio.h>
#include <flashlib.h>
#include <flash_C22.h>
#include <foefs.h>

/* initializers defined in XN file
* and available via platform .h */
// SPI port definitions

fl_SPIPorts SPI = { PORT_SPI_MISO,
			 		PORT_SPI_SS,
					PORT_SPI_CLK,
					PORT_SPI_MOSI,
					XS1_CLKBLK_1 };


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

void chipReset(void)
{
	unsigned x;
	read_sswitch_reg(get_core_id(), 6, x);
	write_sswitch_reg(get_core_id(), 6, x);
}



#define BUFFER_SIZE 7400

int check_file_access(chanend foe_comm, unsigned address, chanend reset_out)
{
	char buffer[7400];
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

			if(size==2)
			{

				for (i=0; i<size; i++) {
					foe_comm :> ctmp;
					if(i==0)
					{
						if(ctmp==0x34)
						{
							flash_setup(1);
							address=0;
						}
						else if(ctmp==0x99)
						{
							flash_buf_end();
							reset_out <: 1;
						}
					}
				}
			}
			else
			{
				for (i=0; i<size; i++)
				{
					foe_comm :> ctmp;
					buffer[i]=ctmp;
				}
				flash_buffer(buffer, size, address);
				address+=size;
			}
			break;

		case FOE_FILE_ERROR:
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


