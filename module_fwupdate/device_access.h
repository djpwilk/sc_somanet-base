
/**
 * \file DeviceAccess.h
 * \brief Flash device access
 * \version 1.0
 * \date 10/04/2014
 */
/*
 * Copyright (c) 2014, Synapticon GmbH & XMOS ltd
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

#ifndef HAVE_DEVICEACCESS_H_
#define HAVE_DEVICEACCESS_H_

#include <xs1.h>
#include "flashlib.h"

#ifdef __XC__
extern out port p_ss;
extern out port p_sclk;
extern in buffered port:8 p_miso;
extern out buffered port:8 p_mosi;
extern clock b_spi;
extern out port p_rdy;
#endif


int fl_int_spiMasterInit(void);
int fl_int_spiInit( int div );
unsigned int fl_int_issueShortCommand( unsigned char cmd, unsigned int addr, unsigned int addrSize, unsigned int dummySize, unsigned int dataSize );
#ifdef __XC__
void fl_int_waitWhileWriting( const fl_DeviceSpec& flashAccess);
#else
void fl_int_waitWhileWriting( const fl_DeviceSpec* flashAccess);
#endif
#ifdef __XC__
int fl_int_programPageAsync( const fl_DeviceSpec& flashAccess, unsigned int pageAddress, const unsigned char data[] );
int fl_int_programPage( const fl_DeviceSpec& flashAccess, unsigned int pageAddress, const unsigned char data[] );
int fl_int_readPage( const fl_DeviceSpec& flashAccess, unsigned int pageAddress, unsigned char data[] );
#else
int fl_int_programPageAsync( const fl_DeviceSpec* flashAccess, unsigned int pageAddress, const unsigned char data[] );
int fl_int_programPage( const fl_DeviceSpec* flashAccess, unsigned int pageAddress, const unsigned char data[] );
int fl_int_readPage( const fl_DeviceSpec* flashAccess, unsigned int pageAddress, unsigned char data[] );
#endif

#ifdef __XC__
int fl_int_readBytes(const fl_DeviceSpec &flashAccess, unsigned address,
                     unsigned char data[], unsigned numBytes);
#else
int fl_int_readBytes(const fl_DeviceSpec *flashAccess, unsigned address,
                     unsigned char data[], unsigned numBytes);
#endif

#ifdef __XC__
int fl_int_getBusyStatus(const fl_DeviceSpec &flashAccess);
#else
int fl_int_getBusyStatus(const fl_DeviceSpec *flashAccess);
#endif

#ifdef __XC__
unsigned fl_int_getFullStatus(const fl_DeviceSpec &flashAccess);
#else
unsigned fl_int_getFullStatus(const fl_DeviceSpec *flashAccess);
#endif

#endif /* HAVE_DEVICEACCESS_H_ */
