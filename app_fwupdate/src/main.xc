
/**
 *
 * \file app_fwupdate main.xc
 *
 *	\brief Example application for flashing binary file over ethercat
 *
 *
 * Copyright (c) 2013, Synapticon GmbH
 * All rights reserved.
 * Author:  Pavan Kanajar <pkanajar@synapticon.com> & Frank Jeschke <jeschke@fjes.de>
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

#include <xs1.h>
#include <platform.h>
#include <print.h>
#include <stdio.h>
#include <stdint.h>
#include <flash_somanet.h>
#include <ethercat.h>


int main(void)
{
	//etherCat Comm channels
	chan coe_in;   ///< CAN from module_ethercat to consumer
	chan coe_out;  ///< CAN from consumer to module_ethercat
	chan eoe_in;   ///< Ethernet from module_ethercat to consumer
	chan eoe_out;  ///< Ethernet from consumer to module_ethercat
	chan eoe_sig;
	chan foe_in;   ///< File from module_ethercat to consumer
	chan foe_out;  ///< File from consumer to module_ethercat
	chan pdo_in;
	chan pdo_out;
	chan sig_1;

	par
	{

		on stdcore[0] : {
			ecat_init();
			ecat_handler(coe_out, coe_in, eoe_out, eoe_in, eoe_sig, foe_out, foe_in, pdo_out, pdo_in);
		}

		on stdcore[0] : {
			firmware_update(foe_out, foe_in, sig_1); // firmware update over ethercat
		}

	}

	return 0;
}


