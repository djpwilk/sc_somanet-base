
/**
 *
 * \file ioports.h
 *
 *
 * Copyright (c) 2013, Synapticon GmbH
 * All rights reserved.
 * Author: Martin Schwarz <mschwarz@synapticon.com>
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

#pragma once

#include "filename_macro.h"

// read node configuration from header file provided in the app using this module
#include <nodeconfig.h>

#ifndef SOMANET_CORE
#define SOMANET_CORE null
#endif

#ifndef SOMANET_COM
#define SOMANET_COM null
#endif

#ifndef SOMANET_IFM
#define SOMANET_IFM null
#endif

#define CORE_PREF core_
#define COM_PREF com_
#define IFM_PREF ifm_
#define SUFFIX_XC _xc.inc
#define SUFFIX_H _h.inc

#ifdef INCLUDE_FROM_IOPORTS_XC
#include STRFY( CONCAT3( CORE_PREF, SOMANET_CORE, SUFFIX_XC) )
#include STRFY( CONCAT3( COM_PREF, SOMANET_COM, SUFFIX_XC) )
#include STRFY( CONCAT3( IFM_PREF, SOMANET_IFM, SUFFIX_XC) )
#else
// import "extern" port declarations
#include STRFY( CONCAT3( CORE_PREF, SOMANET_CORE, SUFFIX_H) )
#include STRFY( CONCAT3( COM_PREF, SOMANET_COM, SUFFIX_H) )
#include STRFY( CONCAT3( IFM_PREF, SOMANET_IFM, SUFFIX_H) )
#endif

#undef CORE_PREF
#undef COM_PREF
#undef IFM_PREF
#undef SUFFIX_XC
#undef SUFFIX_H
