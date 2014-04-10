
/**
 * \file flash_write.c
 * \brief Flash device access
 * \author Pavan Kanajar <pkanajar@synapticon.com>
 * \version 1.0
 * \date 10/04/2014
 */
/*
 * Copyright (c) 2014, Synapticon GmbH
 * All rights reserved.
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
	 //fl_BootImageInfo bii;  // struct to hold image info

	 //communicate with spi flash
	 if( 0 == flash_connect(SPI) )
	 {
		 printf("could not connect flash\n" );
		 exit(1);
	 }

	 // get Factory details into bootinfo struct bii
	 /*if(0 != fl_getFirstBootImage(&bii))
	 {
		  printf("%s\n", "No factory image found, erase not required");
	 }
	 else
	 {	printf("%s\n", " factory image found");
		 if(factory == 1)
		 {


		 }
	 }*/
	 fl_setProtection(0);
	 flash_erase();
	 // Disable flash protection for writing image

}

void flash_buffer(char content[], int image_size, unsigned address)
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







/* example function showing how to use the Flash_module
//void re_file_to_flash(char file_name[], unsigned int factory)
//{


 	 // flash section
	 //flash_setup(1);
	// flash_buf(content, imageSize);
	 //flash_buf_end();

	  if(factory == 0) // upgrade image boot file info setup
	  {
		  nbii.size = imageSize;
		  nbii.factory = 0; //not factory upgarde
		  nbii.version = 1;
		  nbii.startAddress = 65536;
	  }


	  if(factory == 1) // routine to add factory image (based on requested operation Factory as 1)
	  {
		 // if(0 != flash_addFactoryImage(0, imageSize, &supplyData, (void*)inFile)) {
			//  fprintf(stderr,"Error: failed to add new boot image.\n");
			//  fclose(inFile);
			// fl_disconnect();
			//  exit(1);
		 // }
		 // printf("Factory boot image added.\n");
	 // }
	//  else if(factory == 0) // routine to add upgarde image  (based on requested operation Factory as 0)
	  {
		  //if(0 != fl_addBootImage(&nbii, nbii.size, &supplyData, (void*)inFile)) {
			//  fprintf(stderr,"Error: failed to add new boot image.\n");
			//  fclose(inFile);
			//  fl_disconnect();
			//  exit(1);
		  //}
		//  printf("Upgarde boot image added.\n");
	 // }

	  fl_setProtection(1); // protect image
	  fl_disconnect();	   // suspend spi flash communication


}
*/

