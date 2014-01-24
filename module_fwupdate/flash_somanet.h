
/**
 *
 * \file flash_somanet.h
 *
 * \brief Somanet Firmware Update implemtation
 *
 *
 * Copyright (c) 2014, Synapticon GmbH
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

#ifndef FLASHSOMANET_H
#define FLASHSOMANET_H

#include <stdint.h>
#include <flash.h>
#include <flashlib.h>
#include <ethercat.h>
#include <foefs.h>

#define BUFFER_SIZE 2400	//   flash requirement



/**
 *  \brief Firmware update function
 *    This thread must be on CORE 0 only
 *
 */
extern void firmware_update(chanend foe_comm, chanend foe_signal, chanend reset);



/* Internal Functions*/
extern void flash_setup(int factory);

extern int 	flash_buf_end(void);

extern void chipReset(void);

extern void flash_buffer(char content[], int imageSize, unsigned address);

extern void get_file(chanend foe_out, char filename[]);

/*
 * If a file is available it is read by check_file_access() and the filesystem
 * becomes formated for the next file.
 */
int check_file_access(chanend foe_comm, unsigned address, chanend reset_out);

/* software auto reset functions*/
void reset_cores(chanend sig_in, chanend sig_out);

void reset_last_core(chanend sig_in);

#endif /* FLASHSOMANET_H */
