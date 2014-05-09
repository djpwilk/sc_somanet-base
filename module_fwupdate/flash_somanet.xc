
/**
 * \file flash_somanet.xc
 * \brief Somanet Firmware Update implementation
 * \brief Flash device access
 * \author Pavan Kanajar <pkanajar@synapticon.com>
 * \author Frank Jeschke <jeschke@fjes.de>
 * \version 1.0
 * \date 10/04/2014
 */

#include <platform.h>
#include <stdio.h>
#include <flash_somanet.h>
#include <print.h>

#define START_FLASH     12
#define END_FLASH       26
#define FLASH           1
#define IDLE            0
#define READY_TO_FLASH  20
#define START_UPDATE    0x34
#define END_UPDATE      0x99

int write_state = IDLE;
int start_flash = START_FLASH;
int end_flash = END_FLASH;
int flash1 = FLASH;


/* open SPI connection routine called in flash_write routine */
int flash_connect(fl_SPIPorts &SPI) {
  int res;
  res = fl_connect(SPI);
  if( res != 0 ) {
    return(0);
  }
  return 1;
}

int flash_buf_end(void);

void flash_buffer(char content[], int imageSize, unsigned address);

extern void flash_setup(int factory, fl_SPIPorts &SPI);

extern void connect_to_flash(fl_SPIPorts &SPI);

/*
 * If a file is available it is read by check_file_access() and the filesystem
 * becomes formated for the next file.
 */
unsigned check_file_access(fl_SPIPorts &SPI, chanend foe_comm, chanend c_nodes[], unsigned address, chanend reset_out);

void core_reset(void)				//	auto reset from software
{
	unsigned x;
	read_sswitch_reg(get_local_tile_id(), 6, x); // TODO verify operation
	write_sswitch_reg(get_local_tile_id(), 6, x);
}

/*
 * Note: this implementation allows firmware update for only upto 18 nodes connected over DX COM.
 */
unsigned check_file_access(fl_SPIPorts &SPI, chanend foe_comm, chanend c_nodes[], unsigned address, chanend reset_out)
{
	char buffer[BUFFER_SIZE];
	unsigned i = 0;
	int ctmp;
	unsigned size;
	int command;
	int start_end_token;
	int flag_node = 0;
	int status;
	foe_comm <: FOE_FILE_READ;
	foe_comm <: BUFFER_SIZE;
	foe_comm :> ctmp;

	switch (ctmp)
	{
		case FOE_FILE_DATA:
			foe_comm :> ctmp;
			size = (unsigned int)ctmp;
			if(size == 2)
			{
			    foe_comm :> ctmp;
			    start_end_token = ctmp;
			    foe_comm :> ctmp;
			    command = ctmp;
				if(command == 1) // node 1
                {
                    if(start_end_token == START_UPDATE)
                    {
                        write_state = start_flash;
                    }
                    else if(start_end_token == END_UPDATE)
                    {
                        write_state = IDLE;
                        flash_buf_end();
                      //reset_out <: 1;
                    }
                }
                else if(command >= 2 && command < 18) // nodes 2 to 18
                {
                    if(start_end_token == START_UPDATE)
                    {
                        c_nodes[command-2] <: command;
                        c_nodes[command-2] <: start_end_token;
                    }
                    else if(start_end_token == END_UPDATE)
                    {
                        c_nodes[command-2] <: 100;
                        c_nodes[command-2] <: 0;
                        flag_node = 0;
                        command  = 0;
                    }
                }
			}
			else if(size >= 100)
			{
                if(command == 1)
                {
                    if(write_state == start_flash)
                    {
                        flash_setup(1, SPI);
                        address = 0;
                        write_state = flash1;
                    }
                    for (i = 0; i < size; i++)
                    {
                        foe_comm :> ctmp;
                        buffer[i] = ctmp;
                    }
                    flash_buffer(buffer, size, address);
                    address += size;
                }
                else if(command >= 2 && command < 18 )
                {
                    for (i = 0; i < size; i++)
                    {
                        foe_comm :> ctmp;
                        buffer[i] = ctmp;
                    }
                    c_nodes[command-2] <: 10;
                    c_nodes[command-2] :> status;
                    if(status == READY_TO_FLASH)
                    {
                        c_nodes[command-2] <: size;
                        for (i = 0; i < size; i++)
                        {
                            c_nodes[command-2] <: buffer[i];
                        }
                    }
                }
			}
			else
			{
			    for (i = 0; i < size; i++)
                {
                    foe_comm :> ctmp; // discard data
                }
			}
			break;

		case FOE_FILE_ERROR:
			//printstr("\nfoe error\n");
			break;

		default:
				break;
	}

	/* clean up file system to permit next foe transfer */

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
			//printstr("[check_file_access()] unknown return value\n");
			break;
	}
	return address;
}

int __write_data_flash(fl_SPIPorts &SPI, unsigned char data[256], int data_length, int page)
{
    /* Array to store the data to be written to the flash */
    unsigned char data_page[256];

    /* Variables for buffering, counting iterations, etc */
    unsigned int temp, i;
    int status = 1;

    /* Initialise the my_page array */
    for ( i = 0; i < 256 ; i++ )
    {
        if(i < data_length)
        {
            data_page[i] = data[i];
        }
        else
        {
            data_page[i] = 0x0;
        }
    }

    connect_to_flash(SPI);

    // Get the FLASH data partition size
    temp = fl_getDataPartitionSize();
    printstr( "FLASH data partition size: " );
    printuint(temp);
    printstrln( " bytes." );

    if(page == 0)
    {
        if ( 0 != fl_eraseAllDataSectors() )
        {
            printstrln( "Could not erase the data partition" );
            status = 0;
        }
    }
    // Write to the data partition
    if ( 0 !=  fl_writeDataPage(page, data_page) )
    {
        printstrln( "Could not write the data partition" );
        status = 0;
    }

    // Read from the data partition and Verify
    if ( 0 !=  fl_readDataPage(page, data_page) )
    {
        printstrln( "Could not read the data partition" );
        status = 0;
    }
    for ( i = 0; i < 256; i++ )
    {
        if(i < data_length)
        {
            if(data_page[i] != data[i])
            {
                status = 0;
                break;
            }
        }
       // printhexln(data_page[i]);
    }
    return status;
}

int __read_data_flash(fl_SPIPorts &SPI, int page, unsigned char data[256])
{
    /* Variables for buffering, counting iterations, etc */
    unsigned int temp, i;
    int status = 1;

    /* Initialise the data_page array */
    for ( i = 0; i < 256 ; i++ )
    {
        data[i] = 0x0;
    }

    connect_to_flash(SPI);

    // Get the FLASH data partition size
    temp = fl_getDataPartitionSize();
    printstr( "FLASH data partition size: " );
    printuint(temp);
    printstrln( " bytes." );


    // Read from the data partition and Verify
    if ( 0 !=  fl_readDataPage(page, data) )
    {
        printstrln( "Could not read the data partition" );
        status = 0;
    }
//    for ( i = 0; i < 256; i++ )
//    {
//        printhexln(data[i]);
//        //send data routine;
//    }
    return status;
}

int read_data_flash(chanend c_flash_data, unsigned page, unsigned char data[256], unsigned data_length)
{
    int i, status;
    c_flash_data <: 1;
    c_flash_data <: data_length;
    c_flash_data <: page;
    c_flash_data :> status;
    if(status == 1)
    {
        for (i = 0; i < data_length; i++)
        {
            c_flash_data :> data[i];
        }
    }

    return status;
}

int write_data_to_flash(chanend c_flash_data, unsigned page, unsigned char data[256], unsigned data_length)
{
    int i, status;
    c_flash_data <: 3;
    c_flash_data <: data_length;
    c_flash_data <: page;

    for (i = 0; i < data_length; i++)
    {
        c_flash_data <: data[i];
    }
    c_flash_data :> status;
    return status;
}

void firmware_update_dx(fl_SPIPorts &SPI, chanend c_node, int node_number)
{
    int write_state = 0;
    int start_flash = 12;
    int end_flash = 26;
    int flash1 = 1;

    char buffer[BUFFER_SIZE];
    unsigned address  = 0;
    int command;
    int data;
    int flag = 0;
    int end_flag = 0;
    int cmd;
    int size = 0;
    int i = 0;

    int page;        /* page exceeds error, no data partition found error */
    int data_length;
    int status;      /* erase all pages atleast once if status is always 0 even if data partition is found */

    while (1)
    {
        select
        {
            /* Firmware update over DX (signaled over c_node) / Read Permanent Config */
            case c_node :> node_number:
                c_node :> command;
                address = 0;
                if(command == 0x34)
                {
                    flash_setup(1, SPI);
                    //indicate ready to fw_update
                    while(1)
                    {
                        select
                        {
                            case c_node :> cmd:
                                if(cmd == 10)
                                {
                                    c_node <: READY_TO_FLASH;
                                    end_flag = 0;
                                    while(1)
                                    {
                                        select
                                        {
                                            case c_node :> size:
                                                for (i = 0; i < size; i++)
                                                {
                                                    c_node :> buffer[i];
                                                }
                                                flash_buffer(buffer, size, address);
                                                address += size;
                                                end_flag = 1;
                                                break;
                                        }
                                        if(end_flag == 1)
                                            break;
                                    }
                                }
                                else if(cmd == 100)
                                {
                                    c_node :> cmd;
                                    flash_buf_end();
                                    flag = 3;
                                }
                                break;
                        }
                        if(flag == 3)
                        {
                            flag = 1;
                            break;
                        }
                    }
                }
                break;
        }
        //printstrln("out of loop");
    }
}


void firmware_update_loop(fl_SPIPorts &SPI, chanend foe_comm, chanend foe_signal, chanend c_flash_data,\
        chanend c_nodes[], chanend reset)
{
	timer t;
	unsigned time = 0;
	unsigned delay = 100000;
	char name[] = "test";
	unsigned i = 0;
	int ctmp = 0;
	int notification = 0;
	int command;
	unsigned address = 0;
	int data_length; /* data length exceeds page length error */
    int page;        /* page exceeds error, no data partition found error */
    unsigned char data[256];
    int status;      /* erase all pages atleast once if status is always 0 even if data partition is found */

	/* Select ensures all COM handler are ready */
	while (1)
	{
	    select
	    {
            /* Firmware update over EtherCAT (signaled over foe_signal) */
            case foe_signal :> notification:

                if (notification != FOE_FILE_READY)
                {
                    t :> time;
                    t when timerafter(time+delay) :> void;
                    continue;
                }

                /* check if a file is present, FIXME: this could be realized by the signaling channel! */
                foe_comm <: FOE_FILE_OPEN;
                i = -1;
                do
                {
                    i++;
                    foe_comm <: (int)name[i];
                } while (name[i] != '\0');

                foe_comm :> ctmp;
                switch (ctmp)
                {
                    case FOE_FILE_ERROR:
                        //printstr("Error file is not ready\n");
                        break;

                    case FOE_FILE_ACK:
                        /* If file is ready read it and flash to device */
                        address = check_file_access(SPI, foe_comm, c_nodes, address, reset);//check_file_access(SPI, foe_comm, address, reset);
                        //printintln(address);
                        break;

                    default:
                        //printstr("Unknown state returned\n");
                        break;
                }
                // delay = 100;
                // t :> time;
                //t when timerafter(time+delay) :> void;
                break;

            //TODO Firmware update over any other Comm interfaces

            /* Data Field update */
            case c_flash_data :> command:  //read/write
                if(command == 1)  //read
                {
                    c_flash_data :> data_length;
                    c_flash_data :> page;
                    status = __read_data_flash(SPI, page, data);

                    c_flash_data <: status;

                    //send stream of data upto specified data_length (if status is OK)
                    if(status == 1)
                    {
                        for (i = 0; i < data_length; i++)
                        {
                            c_flash_data <: data[i];
                        }
                    }
                }
                else if(command == 3) //write
                {
                    c_flash_data :> data_length;
                    c_flash_data :> page;
                    // read stream of data page

                    for (i = 0; i < data_length; i++)
                    {
                        c_flash_data :> data[i];
                    }
                    status = __write_data_flash(SPI, data, data_length, page);
                    c_flash_data <: status;
                }
                break;
	    }
	}
}

/*
 * example for storing/retrieving motor parameters to/from the data array
 */
void config_to_array()
{
    unsigned char data_array[256] = {0};
    int param = 0xf1f2f3f4;
    int param_read;
    int i, k, no_of_data = 4;

    // store data and update flag bit at 5th byte
    for(i = 0, k = 0; i < 5*no_of_data; i = i + 5, k++)
    {
        store_data_array(i, param, data_array);
        data_array[4 + 5*(k/8)] = data_array[4 + 5*(k/8)] | 1<<(k%8);
    }

    // read data
    for(int i = 0, k= 0; i < 5*no_of_data; i = i + 5, k++)
    {
        param_read = read_data_array(i, data_array);
        if( (data_array[4 + 5*(k/8)] & 1<<(k%8)) >> (k%8) ) // updated
            printhexln(param_read);
    }
}

/*
 * example shows how to store/retreive data array to/from flash memory
 */
void store_and_read_data(chanend c_flash_data)
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
}

void store_data_array(int offset, int param, char data_array[])
{
    int j = 0;
    for(int i = offset; i < offset+4; i++)
    {
        data_array[i] = (param >> (j*8)) & 0xff;
        j++;
    }
}

int read_data_array(int offset, char data_array[])
{
    return ((data_array[3+offset] << 24) | ~(0xff<<24) ) & ((data_array[2+offset] << 16) | ~(0xff<<16))\
            & ((data_array[1+offset] << 8) | ~(0xff<<8)) & (  data_array[offset] | (0xffffffff<<8));
}

void reset_cores(chanend sig_in, chanend sig_out)
{
	int read;
	timer tmr1;
	unsigned time = 0;
	unsigned delay = 100000;

	while(1)
	{
		sig_in :> read;
		if(read == 1)
		{
			sig_out <: read;
			tmr1 :> time;
			tmr1 when timerafter(time + delay) :> void;
			core_reset();
			break;
		}
	}
}

void reset_last_core(chanend sig_in)
{
	int read;
	timer tmr1;
	unsigned time = 0;
	unsigned delay = 100000;
	while(1)
	{
		sig_in :> read;
		if(read == 1)
		{
			tmr1 :> time;
			tmr1 when timerafter(time + delay) :> void;
			core_reset();
			break;
		}
	}
}
