/**
 * \file fw_update.c
 *
 * \brief Firmware Update for Synapticon SOMANET (modified from Example code for
 *   Simple Open EtherCAT master)
 *
 * Usage: fw_update eth0 OPTION id filepath 
 *    OPTION:
 *   -s     specify serial number for the ethercat slave
 *   -seq   specify slave number in EtherCAT order 1..n
 *   -all   use all slaves connected to the system
 *   -scan  scan the slave/slaves connected and display their serial number
 *
 *   specify the ID number after options for these options -s & -seq followed by  /path/to/your/file
 *
 * SOEM is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation.
 *
 * SOEM is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * As a special exception, if other files instantiate templates or use macros
 * or inline functions from this file, or you compile this file and link it
 * with other works to produce a work based on this file, this file does not
 * by itself cause the resulting work to be covered by the GNU General Public
 * License. However the source code for this file must still be made available
 * in accordance with section (3) of the GNU General Public License.
 *
 * This exception does not invalidate any other reasons why a work based on
 * this file might be covered by the GNU General Public License.
 *
 * The EtherCAT Technology, the trade name and logo “EtherCAT” are the intellectual
 * property of, and protected by Beckhoff Automation GmbH. You can use SOEM for
 * the sole purpose of creating, using and/or selling or otherwise distributing
 * an EtherCAT network master provided that an EtherCAT Master License is obtained
 * from Beckhoff Automation GmbH.
 *
 * In case you did not receive a copy of the EtherCAT Master License along with
 * SOEM write to Beckhoff Automation GmbH, Eiserstraße 5, D-33415 Verl, Germany
 * (www.beckhoff.com).
 * 
 * Copyright 2013, Synapticon GmbH. All rights reserved
 * (c) Authors : Arthur Ketels 2010 - 2011 (original simpletest)
 * (c) Authors : Frank Jeschke <jeschke@fjes.de> & Pavan Kanajar <pkanajar@synapticon.com>
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>
#include "ethercattype.h"
#include "nicdrv.h"
#include "ethercatbase.h"
#include "ethercatmain.h"
#include "ethercatcoe.h"
#include "ethercatfoe.h"
#include "ethercatconfig.h"
#include "ethercatprint.h"

#define MBX_VOE_TYPE  0xF
#define READDUMMYTEST   0
#define MAX_MBXDATALENGTH  0x200 /* this size is copied from ethercatcoe.c */
#define MODE_NONE	0
#define MODE_SERIAL	1
#define MODE_SEQUENTIAL	2
#define MODE_ALL	3
#define MODE_SCAN	4

typedef struct __attribute__((__packed__)) {
	ec_mbxheadert header;
	uint8_t data[MAX_MBXDATALENGTH]; /* max length of data foo */
} ec_VOEmbx_t;

char IOmap[4096];

int send_mbx(uint16_t slave, uint8_t *data, size_t length)
{
	//ec_mbxbuft mbxIn;
	ec_mbxbuft mbxOut;

	//ec_clearmbx(&mbxIn);
	ec_clearmbx(&mbxOut);

	//ec_VOEmbx_t *voeMbxIn = (ec_VOEmbx_t *)mbxIn;
	ec_VOEmbx_t *voeMbxOut = (ec_VOEmbx_t *)mbxOut;

	voeMbxOut->header.length = htoes(0x000a);
	voeMbxOut->header.address = 0x0000;
	voeMbxOut->header.priority = 0x00;
	voeMbxOut->header.mbxtype = ECT_MBXT_VOE; /* + (cnt<<4) */
	memset(voeMbxOut->data, 0, MAX_MBXDATALENGTH);
	memmove(voeMbxOut->data, data, length);
	int ret = ec_mbxsend(slave, &mbxOut, EC_TIMEOUTTXM);
	return ret;
}

int start_file(uint16 slave)
{
	int psize = 2; 
	unsigned char *p = (unsigned char *)malloc(psize * sizeof(unsigned char));
	p[0] = 0x34; //Start code
	p[1] = 0xff;
	return ec_FOEwrite(slave, "test", 0, psize, (void *)p, 5000000/*EC_TIMEOUTTXM+1000*/);
}

int end_file(uint16 slave)
{
	int psize = 2; 
	unsigned char *p = (unsigned char *)malloc(psize * sizeof(unsigned char));
	p[0] = 0x99; //End code
	p[1] = 0xff;
	return ec_FOEwrite(slave, "test", 0, psize, (void *)p, 5000000/*EC_TIMEOUTTXM+1000*/);
}

int slave_testfoe(uint16 slave, char *filename)
{	
	FILE *f;
	int psize = 2097152; /* exact size of EC_MACFOEDATA, which is not exported... */
	unsigned char *p = (unsigned char *)malloc(psize * sizeof(unsigned char));	
	int imageSize;

	f = fopen(filename, "r");		// "//home//pavan//Desktop//test"
	if (f==NULL) {
		printf("Error, couldn't open file for reading\n");
		return 1;
	}

	if(0 != fseek(f, 0, SEEK_END)) {
	    printf("Error, couldn't open file for reading\n");	   
	    exit(1);
	  }

	imageSize = (int)ftell(f);
	//setting back the pointer to begining
	if(0 != fseek(f, 0, SEEK_SET)) {
	    printf("Error, couldn't open file for reading\n");
            exit(1);
	}
		
	/* Attention, psize has side effects, give max size, receive received things */
	//printf("Writing FOE file request\n");
	int ret = 0;	
	while(ret!=1)
	{
	     ret=start_file(slave);
	     usleep(350000);
	}

 	int index;
	int chunk_size = 256*8; 		// chunk_size = 256*8 also works
	//char content[chunk_size];
	int num_chunks = imageSize/chunk_size;
	float k = imageSize/chunk_size;
	for(index = 0; index < num_chunks; index++)
	{
	      	int sizeread = fread(p, 1,chunk_size , f);
		ret = 0;int co = 0;
		while(ret != 1)
		{
			ret = ec_FOEwrite(slave, "test", 0, sizeread, (void *)p, 5000000/*EC_TIMEOUTTXM+1000*/);
			if(ret == 1)
			printf(".");
			else
			printf("*");
			co++;
			usleep(25000);
		}  
		if(ret == 1)
		printf(".");
		else
		printf("*");  	      	     
	}

	if(k>0)
	{
	      	int rem = imageSize - num_chunks*chunk_size;  
	        fread(p, 1, rem , f);
	        ret=0;
                while(ret != 1)
	        {
			 ret = ec_FOEwrite(slave, "test", 0, rem, (void *)p, 5000000/*EC_TIMEOUTTXM+1000*/);
	                 usleep(10000);
		}  
		if(ret == 1)
		printf(".");
		else
		printf("*");  
	 }

	ret=0;
	while(ret != 1)
	{
		ret = end_file(slave);
		usleep(7000);
	}
	if(ret == 1)
	printf(".");
	else
	printf("*"); 
#if 1
	memset(p, 0, psize);	
#endif
	free(p);
	return 0;
}

int slave_operation(int oloop, int iloop, boolean needlf)
{
	int i; int j, wkc;
	int ret = 0;
	uint8_t db1[] = { 0xde, 0xad, 0xbe, 0xef }; // test data
	uint8_t db2[] = { 0xAA, 0xAA, 0x66, 0x66 }; // test data
	int cycleCount = 0;
	
	printf("Operational state reached for all slaves.\n");

	/* check mailbox settings of device: */
	for (i=1; i<=ec_slavecount; i++) {
		if (ec_slave[i].state == EC_STATE_OPERATIONAL) {
			printf("[%s] ec_slave[%d].mbx_l = %d\n", __func__, i, ec_slave[i].mbx_l);
		}
	}
	/* end check */

	/* here the work on processdata is done */
	for (i=0, cycleCount=1; i<10; i++, cycleCount++) {
		//printf("Processdata cycle (%d):\n", cycleCount);

		/* load output buffer according to even or uneven state of cycle */
		for (j=0; j<oloop && j<4; j++) {
			if (cycleCount%2 == 0) {
				*(ec_slave[1].outputs + j) = db1[j];
			} else {
				*(ec_slave[1].outputs + j) = db2[j];
			}
		}

		/* Debug output */
		//printf("O:");
		for (j = 0; j < oloop; j++) {
			printf(" %2.2x", *(ec_slave[1].outputs + j));
		}

		//printf("\nI:");
		for (j = 0; j < iloop; j++) {
			printf(" %2.2x", *(ec_slave[1].inputs + j));
		}
		//printf("\n\r");
		needlf = TRUE;
		/* end debug output */

		usleep(10000);

		/* send process data and check operation success */
		ret = ec_send_processdata();
		wkc = ec_receive_processdata(EC_TIMEOUTRET*4);
		if ((wkc < ec_group[0].expectedWKC) || ec_group[0].docheckstate) {
			printf("wkc not reached\n");
		}

		/* debug output */
		printf("O:");
		for (j = 0; j < oloop; j++) {
			printf(" %2.2x", *(ec_slave[0].outputs + j));
		}

		printf("\nI:");
		for (j = 0; j < iloop; j++) {
			printf(" %2.2x", *(ec_slave[0].inputs + j));
		}
		printf("\n\r");
		/* end debug output */

		if (ret == 0) {
			fprintf(stderr, " error sending processdata\n");
			return -1;
		}
	}
	return 0;
}

#define MAXBUF 32768
uint8 ebuf[MAXBUF];
int eeprom_read(int slave, int start, int length)
{
	int i, wkc, ainc = 4;
    	uint16 estat, aiadr;
	uint32 b4;
	uint64 b8;
	uint8 eepctl;
	
	if((ec_slavecount >= slave) && (slave > 0) && ((start + length) <= MAXBUF))
	{
		aiadr = 1 - slave;
		eepctl = 2;
		wkc = ec_APWR(aiadr, ECT_REG_EEPCFG, sizeof(eepctl), &eepctl , EC_TIMEOUTRET); /* force Eeprom from PDI */
		eepctl = 0;
		wkc = ec_APWR(aiadr, ECT_REG_EEPCFG, sizeof(eepctl), &eepctl , EC_TIMEOUTRET); /* set Eeprom to master */
		estat = 0x0000;
		aiadr = 1 - slave;
		wkc=ec_APRD(aiadr, ECT_REG_EEPSTAT, sizeof(estat), &estat, EC_TIMEOUTRET); /* read eeprom status */
		estat = etohs(estat);
		if (estat & EC_ESTAT_R64)
		{
			ainc = 8;
			for (i = start ; i < (start + length) ; i+=ainc)
			{
				b8 = ec_readeepromAP(aiadr, i >> 1 , EC_TIMEOUTEEP);
				ebuf[i] = b8;
				ebuf[i+1] = b8 >> 8;
				ebuf[i+2] = b8 >> 16;
				ebuf[i+3] = b8 >> 24;
				ebuf[i+4] = b8 >> 32;
				ebuf[i+5] = b8 >> 40;
				ebuf[i+6] = b8 >> 48;
				ebuf[i+7] = b8 >> 56;
			}
		}
		else
		{
			for (i = start ; i < (start + length) ; i+=ainc)
			{
				b4 = ec_readeepromAP(aiadr, i >> 1 , EC_TIMEOUTEEP);
				ebuf[i] = b4;
				ebuf[i+1] = b4 >> 8;
				ebuf[i+2] = b4 >> 16;
				ebuf[i+3] = b4 >> 24;
			}
		}
		return 1;
	}
	return 0;
}

/* This function is mostly the original simpletest function modified as Firmware update function for SOMANET C22
 * Here is the basic setup of the ethercat master.
 */
void firmware_update(char *ifname, char *filename, int *ser_no, int mode, int seq_id)
{
	int i, oloop, iloop, err; // j, wkc, wkc_count, slave,
	boolean needlf;
	int ind=0, slave_id = 0, found_id=-1;;
	needlf = FALSE;
	//printf("Starting process data  test\n");
	
	/* initialise SOEM, bind socket to ifname */
	if (ec_init(ifname))
	{
		printf("ec_init on %s succeeded.\n", ifname);

		/* find and auto-config slaves */
		if (ec_config_init(FALSE) > 0) {
			printf("%d slaves found and configured.\n", ec_slavecount);
			/*printf("Checking device configuration from EEPROM:\n");
			printf(" Man = %4.4X, ID = %x, Name %s, dtype=%d, Ibits= %d, Obits= %d\n",
					ec_slave[1].eep_man,
					ec_slave[1].eep_id,
					ec_slave[1].name,
					ec_slave[1].Dtype,
					ec_slave[1].Ibits,
					ec_slave[1].Obits);*/
			if(mode == 1)
			{		
				for(ind = 1 ; ind <= ec_slavecount; ind++)
				{
					eeprom_read(ind, 0x0000, 32);
					if( ebuf[28] ==ser_no[0] &&  ebuf[29] == ser_no[1] &&  ebuf[30] == ser_no[2] &&  ebuf[31] == ser_no[3])
					{	slave_id = ind; found_id = 1; break;	}				
				}
				if(found_id==-1)
				{	
					printf("\n Slave serial id not found\n"); return ;
				}
			}
			else if(mode == 2)
			{
				if(seq_id <= ec_slavecount && seq_id >0)
				slave_id = seq_id;
				else
				{
					printf("\nSlave sequence number %d not found\n", seq_id);
					return;
				}	
			}
			else if(mode == 4)
			{	
				printf("\nSlaves found with serial numbers\n");
				for(ind = 1 ; ind <= ec_slavecount; ind++)
				{
					eeprom_read(ind, 0x0000, 32);
					printf("\n  %.2x%.2x%.2x%.2x\n",ebuf[31], ebuf[30], ebuf[29], ebuf[28]);
				}
				printf("\n");
				return;
			}
				
			ec_config_map(&IOmap);
			printf("Slaves mapped, state to SAFE_OP.\n");
			/* wait for all slaves to reach SAFE_OP state */
			ec_statecheck(0, EC_STATE_SAFE_OP, EC_TIMEOUTSTATE * 4);
			oloop = ec_slave[0].Obytes;
			if ((oloop == 0) && (ec_slave[0].Obits > 0))
				oloop = 1;
			if (oloop > 8)
				oloop = 8;
				iloop = ec_slave[0].Ibytes;
			if ((iloop == 0) && (ec_slave[0].Ibits > 0))
				iloop = 1;
			if (iloop > 8)
				iloop = 8;

			/*printf("segments : %d : %d %d %d %d\n",
			       ec_group[0].nsegments, ec_group[0].IOsegment[0],
			       ec_group[0].IOsegment[1],
			       ec_group[0].IOsegment[2],
			       ec_group[0].IOsegment[3]);

			printf("Request operational state for all slaves\n");
			printf("Calculated workcounter %d\n",
					ec_group[0].expectedWKC);*/

			ec_slave[0].state = EC_STATE_OPERATIONAL;
			/* send one valid process data to make outputs in slaves happy */
			ec_send_processdata();
			ec_receive_processdata(EC_TIMEOUTRET*4);
			/* request OP state for all slaves */
			ec_writestate(0);
			/* wait for all slaves to reach OP state */
			ec_statecheck(0, EC_STATE_OPERATIONAL, EC_TIMEOUTSTATE * 4);

			/* here is the first difference to the original simpletest, the function slave_operation()
			 * will send data to the EtherCAT slave
			 */
			if (ec_slave[0].state == EC_STATE_OPERATIONAL)
			{
				/* testing foe package transfer */
				//printf("[%s] firmware package transfer\n", __func__);
//
				if(mode == 1 || mode == 2){
					printf("[%s] requesting SOMANET slave: %d\n", __func__, slave_id);
					err = slave_testfoe(slave_id, filename);
					if (err) {
						printf("\n[%s] SOMANET slave returned error: %d\n", __func__, err);
					}
					else{
						printf("\n Firmware Update succeeded\n");
					}								
				}				
				else if(mode == 3){					
					for (i = 1; i <= ec_slavecount; i++) {
						printf("[%s] requesting SOMANET slave: %d\n", __func__, i);
						err = slave_testfoe(i, filename);
						if (err) {
							printf("\n[%s] SOMANET slave (%d) returned error: %d\n", __func__, i, err);
						}
						else{
							printf("\n Firmware Update succeeded for SOMANET slave %d \n",i);
						}
					}
				}
			} else {
				printf("Not all SOMANET slaves reached operational state.\n");
				ec_readstate();
				for (i = 1; i <= ec_slavecount; i++) {
					if (ec_slave[i].state != EC_STATE_OPERATIONAL) {
						printf ("Slave %d State=0x%2.2x StatusCode=0x%4.4x : %s\n",
							i,
							ec_slave[i].state,
							ec_slave[i].ALstatuscode,
							ec_ALstatuscode2string(ec_slave[i].ALstatuscode));
					}
				}
			}
			
			/* request INIT state for all slaves */
			ec_slave[0].state = EC_STATE_INIT;
			ec_writestate(0);
			ec_statecheck(0, EC_STATE_INIT, EC_TIMEOUTSTATE*4);
			if (ec_slave[0].state == EC_STATE_INIT) {
				printf("Slave reached init state\n");
			} else {
				printf("Slave doesn't respond to init state, current state: %d\n",ec_slave[0].state);
			}
		} else {
			printf("No SOMANET Slaves found!\n");
		}

		/* stop SOEM, close socket */		
		ec_close();
	} else {
		printf("No socket connection on %s\nExcecute as root\n", ifname);
	}
}

int main(int argc, char *argv[])
{
	printf("\n Synapticon SOMANET Firmware Update \n");
	
	int mode, seq_id = 0;
	int *s_id = malloc(4);	
	int id_len, ind = 0, i = 0, len;
	
	//argv[1] .. eth0
	//argv[2] .. mode
	//argv[3] .. serial no/seq no.
	//argv[4] .. filepath
	
	if (argc > 1) 
	{
		mode = MODE_NONE;

		if ((strncmp(argv[1], "-h", sizeof("-h")) == 0))
		{
			printf("Usage: fw_update eth0 OPTION id filepath\n");
			printf("   -s     specify serial number for the ethercat slave\n");
			printf("   -seq   specify slave number in EtherCAT order 1..n\n");
			printf("   -all   use all slaves connected to the system\n");
			printf("   -scan  scan the slave/slaves connected and display their serial number\n");
			printf("   specify the number after options for these options -s & -seq followed by filepath\n\n");
			return 0;
		}
		else if((strncmp(argv[1], "-help", sizeof("-help")) == 0))
		{
			printf("Usage: fw_update eth0 OPTION id filepath\n");
			printf("   -s     specify serial number for the ethercat slave\n");
			printf("   -seq   specify slave number in EtherCAT order 1..n\n");
			printf("   -all   use all slaves connected to the system\n");
			printf("   -scan  scan the slave/slaves connected and display their serial number\n");
			printf("   specify the number after options for these options -s & -seq followed by filepath\n\n");
			return 0;
		}

		if ((strncmp(argv[2], "-s", sizeof("-s")) == 0))  mode = MODE_SERIAL; 
		if ((strncmp(argv[2], "-all", sizeof("-all")) == 0)) mode = MODE_ALL;
		if ((strncmp(argv[2], "-seq", sizeof("-seq")) == 0))  mode = MODE_SEQUENTIAL;
		if ((strncmp(argv[2], "-scan", sizeof("-scan")) == 0)) mode = MODE_SCAN;
		
		if(mode == 3)
		{
			printf("\n Updating Firmware of all connected Somanet Slaves\n");
			firmware_update(argv[1], argv[3], s_id, mode, seq_id);
		}
		else if(mode == 2)
		{
			printf("\n Updating Firmware of Somanet Slave with the specified sequential no.\n");
			seq_id = atoi(argv[3]);
			if(seq_id <= 0)
			{
				printf("\n Invalid Sequential no. please check the Somanet Slave sequential no.\n");
				return 0;
			}
			firmware_update(argv[1], argv[4], s_id, mode, seq_id);
		}
		else if(mode == 4)
		{
			printf("\n Showing all connected Somanet Slaves Ethercat Modules\n");
			firmware_update(argv[1], NULL, s_id, mode, seq_id);
		}
		else if(mode == 1)
		{
			printf("\n Updating Firmware of Somanet Slave with the specified serial no.\n");
			id_len = strlen(argv[3]);  
			char *a = malloc(id_len + 1);
			strcpy(a, argv[3]);
			int a1,a2, valid = -1;
			len = id_len;
			
			if(len <= 8)
				for(i=0 ; i<len;i++)
				{
					a1 = a[i];
					if( a1>=0x30 && a1 <=0x39)
					{valid = 1;
					}
					else if(a1>='A' && a1<='F')
					{valid = 1;
					}			
					else if(a1>='a' && a1<='f')
					{valid = 1;
					}
					else
					{valid = -1;
					}
				}
			else if(len > 8){ valid = -1;}
			

			if(valid == -1)
			{
				printf("\n Invalid Serial no. please check the Somanet Slave serial no.\n");
				return 0;
			}	
			else if(valid == 1)
			{
				for(i=0; i < 4; i++)
				{
					ind = 0;
					if(len >=2 )
					{
						len--; a1 = a[len];  
						if(a1>='A' && a1<='F')
							a1 = a1 - 'A' + 10;
						else if(a1>='a' && a1<='f')
							a1 = a1 - 'a' + 10;
						else if(a1>=0x30 && a1<=0x39)
							a1 = a1 - '0'; 		
	
						len--;a2 = a[len];
						if(a2>='A' && a2<='F')
						{	a2 = a2 - 'A' + 10; }
						else if(a2>='a' && a2<='f')
						{	a2 = a2 - 'a' + 10; }
						else if(a2>=0x30 && a2<=0x39)
						{	a2 = a2 - '0'; 	}
						a2 = a2*16;			
						a2 = a2 + a1;
						s_id[i] = a2;				
					}
					else if(len > 0 && len < 2)
					{
						len--; a1 = a[len];  
						if(a1>='A' && a1<='F')
							a1 = a1 - 'A' + 10;
						else if(a1>='a' && a1<='f')
							a1 = a1 - 'a' + 10;
						else if(a1>=0x30 && a1<=0x39)
							a1 = a1 - '0'; 
						s_id[i] = a1;				
					}			
				}

				firmware_update(argv[1], argv[4], s_id, mode, seq_id);
			}

			/*for(i=0; i<4; i++)	// debug
			{	
				printf("\n   val  %d ",s_id[i]);				
			}	*/	
		 }

		 
//		 firmware_update("eth0", argv[3], s_id, mode, seq_id);
	} 

//simpletest(argv[1], argv[4], s_id, mode);
	 else {
		printf("Usage: fw_update eth0 OPTION id filepath\n");  
		printf("   -s     specify serial number for the ethercat slave\n");
		printf("   -seq   specify slave number in EtherCAT order 1..n\n");
		printf("   -all   use all slaves connected to the system\n");
		printf("   -scan  scan the slave/slaves connected and display their serial number\n");
		printf("   specify the number after options for these options -s & -seq followed by filepath\n\n");
	}
	return (0);
}
