
/**
 * \file flash_Somanet.h
 *
 * Copyright 2013, Synapticon GmbH. All rights reserved.
 * Authors: Pavan Kanajar <pkanajar@synapticon.com> & Frank Jeschke <jeschke@fjes.de>
 *
 * In the case where this code is a modification of existing code
 * under a separate license, the separate license terms are shown
 * below. The modifications to the code are still covered by the
 * copyright notice above.
 *
 **/

#ifndef FLASHSOMANET_H
#define FLASHSOMANET_H
#endif


#include <stdint.h>
#include <flash.h>
#include <flashlib.h>
#include <ethercat.h>
#include <foefs.h>

#define BUFFER_SIZE 2400	//   flash requirement

extern void flash_setup(int factory);
extern int 	flash_buf_end(void);
extern void chipReset(void);
extern void flash_buffer(char content[], int imageSize, unsigned address);

/**
 *  \brief
 *   Firmware update function (should be on CORE 0)
 *
 */
extern void firmware_update(chanend foe_comm, chanend foe_signal, chanend reset);


extern void get_file(chanend foe_out, char filename[]);


/* If a file is available it is read by check_file_access() and the filesystem
 * becomes formated for the next file.
 */

int check_file_access(chanend foe_comm, unsigned address, chanend reset_out);

/* software auto reset functions*/
void reset_cores(chanend sig_in, chanend sig_out);
void reset_last_core(chanend sig_in);

/* FLASHSOMANET_H */
