
/**
 * \file flash_write.c
 * \brief Flash device access
 * \author Pavan Kanajar <pkanajar@synapticon.com>
 * \version 1.0
 * \date 10/04/2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <flashlib.h>
#include <platform.h>
#include <flash.h>

void flash_erase()
{
	fl_eraseAll();
}

extern int flash_connect(fl_SPIPorts *SPI);

void flash_setup(int factory, fl_SPIPorts *SPI)  // could have arguments to specify the upgarde image
{
	 //communicate with spi flash
	 if( 0 == flash_connect(SPI) )
	 {
		 printf("could not connect flash\n" );
		 exit(1);
	 }

	 fl_setProtection(0);
	 flash_erase();
	 // Disable flash protection for writing image
}

void connect_to_flash(fl_SPIPorts *SPI)
{
    if( 0 == flash_connect(SPI) )
    {
        printf("could not connect flash\n" );
        exit(1);
    }
}

void flash_buffer(char content[2400], int image_size, unsigned address)
{
	int  i = 0;
	unsigned page_size = 256;
	unsigned char buffer[256];

	unsigned buffer_count = 0;
	unsigned index = 0;
	unsigned current_page = 0;
	for(i = 0; i < image_size/page_size; i++)
	{
		buffer_count = 0;
		for (index = current_page; index < current_page+page_size; index++)
		{
			buffer[buffer_count++] = content[index];
		}
		fl_writePage(address, buffer);
		current_page += page_size;
		address += page_size;
	}
}

int flash_buf_end(void)
{
	fl_endWriteImage();
	return 12;
}
