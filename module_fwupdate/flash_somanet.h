
/**
 * \file flash_somanet.h
 * \brief Somanet Firmware Update Implemtation
 * \author Pavan Kanajar <pkanajar@synapticon.com>
 * \author Frank Jeschke <jeschke@fjes.de>
 * \version 1.0
 * \date 10/04/2014
 */

#ifndef FLASHSOMANET_H
#define FLASHSOMANET_H

#include <stdint.h>
#include <flashlib.h>
#include <ethercat.h>
#include <foefs.h>

#define BUFFER_SIZE     2400	//  minimum buffer size for firmware image
#define READY_TO_FLASH  20

/**
 *  \brief Firmware update function
 *    This thread must be on CORE 0 only
 *
 */
void firmware_update_loop(fl_SPIPorts &SPI, chanend foe_comm, chanend foe_signal,\
        chanend c_flash_data, chanend c_nodes[], chanend reset);

void firmware_update_dx(fl_SPIPorts &SPI, chanend c_node, int node_number);

int read_data_flash(chanend c_flash_data, unsigned page, unsigned char data[256],\
        unsigned data_length);

int write_data_to_flash(chanend c_flash_data, unsigned page, unsigned char data[256],\
        unsigned data_length);

// int_32 split into 4 bytes for data storage
void store_data_array(int offset, int param, char data_array[]);

// pack data bytes into int_32
int read_data_array(int offset, char data_array[]);

/* software auto reset functions */
void reset_cores(chanend sig_in, chanend sig_out);

void reset_last_core(chanend sig_in);

int flash_buf_end(void);

void flash_buffer(char content[], int imageSize, unsigned address);

extern void flash_setup(int factory, fl_SPIPorts &SPI);

extern void connect_to_flash(fl_SPIPorts &SPI);

#endif /* FLASHSOMANET_H */
