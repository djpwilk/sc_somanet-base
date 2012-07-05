/* ethercat.h
 *
 * Copyright 2011, Synapticon GmbH. All rights reserved.
 * Authors: Pavan Kanajar <pkanajar@synapticon.com> & Frank Jeschke <jeschke@fjes.de>
 */

#ifndef FLASHC22_H
#define FLASHC22_H



#include <stdint.h>
#include <flash.h>
#include <flashlib.h>
#include <ethercat.h>
#include <foefs.h>



extern void flash_setup(int factory);
extern int flash_buf_end(void);
extern void chipReset(void);
extern void flash_buffer(char content[], int imageSize, unsigned address);



/* The following functions are a simple example on how to use the channel
 * abstraction to the file access system.
 * If a file is available it is read by check_file_access() and the filesystem
 * becomes formated for the next file.
 *
 * No storage is done here and only the functionality is tested.
*/

int check_file_access(chanend foe_comm, unsigned address, chanend reset_out);
void reset_cores(chanend sig_in, chanend sig_out);
void reset_last_core(chanend sig_in);

#endif /* FLASHC22_H */
