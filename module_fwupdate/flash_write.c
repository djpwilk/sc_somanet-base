
/*
 * flash_write.c
 *
 *  Created on: May 2, 2012
 *      Author: pkanajar @ Synapticon
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


// flash connect defined in upgrade xc file
extern int flash_connect();


void flash_setup(int factory)  //FIXME could have arguments to specify the upgarde image
{
	 fl_BootImageInfo bii;  // struct to hold image info

	 //communicate with spi flash
	 if( 0 == flash_connect() )
	 {
		 printf("could not connect flash\n" );
		 exit(1);  //FIXME needs handling
	 }

	 // get Factory details into bootinfo struct bii
	 if(0 != fl_getFirstBootImage(&bii))
	 {
		  //printf("%s\n", "No factory image found, erase not required");
	 }
	 else
	 {
		 if(factory == 1)
		 {


		 }
	 }
	 fl_setProtection(0);
	 flash_erase();
	 // Disable flash protection for writing image

}

void flash_buffer(char content[], int imageSize, unsigned address)
{
	int  i = 0;
	unsigned pageSize=256;
	unsigned char buf[256];

	unsigned bufcnt=0,index=0,cur=0;
	for(i=0;i<imageSize/pageSize;i++)
	{
  		bufcnt=0;
		for (index=cur; index<cur+pageSize; index++)
		{
			buf[bufcnt++]=content[index];
		}
		fl_writePage(address, buf);
		cur += pageSize;
		address += pageSize;
	}
}


int flash_buf_end(void)
{
	fl_endWriteImage();
	return 12;
}


// example function showing how to use the Flash_module
//void re_file_to_flash(char file_name[], unsigned int factory)
//{


 	 // flash section
	 //flash_setup(1);
	// flash_buf(content, imageSize);
	 //flash_buf_end();

/*	  if(factory == 0) // upgrade image boot file info setup
	  {
		  nbii.size = imageSize;
		  nbii.factory = 0; //not factory upgarde
		  nbii.version = 1;
		  nbii.startAddress = 65536;
	  }


	  if(factory == 1) // routine to add factory image (based on requested operation Factory as 1)
	  {
		 /* if(0 != flash_addFactoryImage(0, imageSize, &supplyData, (void*)inFile)) {
			  fprintf(stderr,"Error: failed to add new boot image.\n");
			  fclose(inFile);
			  fl_disconnect();
			  exit(1);
		  }*/
		 // printf("Factory boot image added.\n");
	 // }
	/*  else if(factory == 0) // routine to add upgarde image  (based on requested operation Factory as 0)
	  {
		  /*if(0 != fl_addBootImage(&nbii, nbii.size, &supplyData, (void*)inFile)) {
			  fprintf(stderr,"Error: failed to add new boot image.\n");
			  fclose(inFile);
			  fl_disconnect();
			  exit(1);
		  }*/
		//  printf("Upgarde boot image added.\n");
	 /* }

	  fl_setProtection(1); // protect image
	  fl_disconnect();	   // suspend spi flash communication
*/

//}


