
/**
 * \file SpecDefinitions.h
 * \brief Generated file for flash specs - do not edit.
 * \author Pavan Kanajar <pkanajar@synapticon.com>
 * \version 1.0
 * \date 10/04/2014
 */
/*
 *
 * Copyright (c) 2014, Synapticon GmbH & XMOS Ltd
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

#define FL_DEVICESPECS { \
  {\
    ALTERA_EPCS1,           /* id */\
    256,                    /* page size */\
    512,                    /* num pages */\
    3,                      /* address size */\
    8,                      /* log2 clock divider */\
    0xAB,                   /* SPI_RDID */\
    3,                      /* id dummy bytes */\
    1,                      /* id size in bytes */\
    0x10,                   /* device id */\
    0xD8,                   /* SPI_SE */\
    0,                      /* Sector erase is full sector */\
    0x06,                   /* SPI_WREN */\
    0x04,                   /* SPI_WRDI */\
    PROT_TYPE_NONE,         /* no protection */\
    {{0,0},{0,0}},          /* no values */\
    0x02,                   /* SPI_PP */\
    0x03,                   /* SPI_READ */\
    0,                      /* no read dummy byte */\
    SECTOR_LAYOUT_REGULAR,  /* sane sectors */\
    {32768,{0,{0}}},        /* regular sector size */\
    0x05,                   /* SPI_RDSR */\
    0x00,                   /* no SPI_WRSR */\
    0x01,                   /* SPI_WIP_BIT_MASK */\
  },\
  {\
    ATMEL_AT25DF041A,\
    256,                    /* page size */\
    2048,                   /* num pages */\
    3,                      /* address size */\
    8,                      /* log2 clock divider */\
    0x9F,                   /* SPI_RDID */\
    0,                      /* id dummy bytes */\
    3,                      /* id size in bytes */\
    0x1f4401,               /* device id */\
    0x20,                   /* SPI_BE4 */\
    4096,                   /* Sector erase is always 4KB */\
    0x06,                   /* SPI_WREN */\
    0x04,                   /* SPI_WRDI */\
    PROT_TYPE_SECS,         /* no protection */\
    {{0,0},{0x36,0x39}},    /* SPI_SP, SPI_SU */\
    0x02,                   /* SPI_PP */\
    0x0B,                   /* SPI_READ_FAST */\
    1,                      /* 1 read dummy byte */\
    SECTOR_LAYOUT_IRREGULAR,  /* mad sectors */\
    {0,{11,{8,8,8,8,8,8,8,7,5,5,6}}},  /* regular sector sizes */\
    0x05,                   /* SPI_RDSR */\
    0x01,                   /* SPI_WRSR */\
    0x01,                   /* SPI_WIP_BIT_MASK */\
  },\
  {\
    ATMEL_AT25FS010,\
    256,                    /* page size */\
    512,                    /* num pages */\
    3,                      /* address size */\
    8,                      /* log2 clock divider */\
    0x9F,                   /* SPI_RDID */\
    0,                      /* id dummy bytes */\
    3,                      /* id size in bytes */\
    0x1f6601,               /* device id */\
    0xD7,                   /* SPI_SE */\
    0,                      /* erase is full sector */\
    0x06,                   /* SPI_WREN */\
    0x04,                   /* SPI_WRDI */\
    PROT_TYPE_SR_2X,        /* SR based protection (need double write) */\
    {{0x0c,0x0},{0,0}},     /* SR values for protection */\
    0x02,                   /* SPI_PP */\
    0x0B,                   /* SPI_READ_FAST */\
    1,                      /* 1 read dummy byte*/\
    SECTOR_LAYOUT_REGULAR,  /* sane sectors */\
    {4096,{0,{0}}},         /* regular sector sizes */\
    0x05,                   /* SPI_RDSR */\
    0x01,                   /* SPI_WRSR */\
    0x01,                   /* SPI_WIP_BIT_MASK */\
  },\
  {\
    ST_M25PE10,\
    256,                    /* page size */\
    512,                    /* num pages */\
    3,                      /* address size */\
    8,                      /* log2 clock divider */\
    0x9f,                   /* SPI_RDID */\
    0,                      /* id dummy bytes */\
    3,                      /* id size in bytes */\
    0x208011,               /* device id */\
    0x20,                   /* SPI_SSE */\
    0,                      /* full sector erase */\
    0x06,                   /* SPI_WREN */\
    0x04,                   /* SPI_WRDI */\
    PROT_TYPE_NONE,         /* no protection */\
    {{0,0},{0,0}},          /* no values */\
    0x02,                   /* SPI_PP */\
    0x0b,                   /* SPI_READFAST */\
    1,                      /* 1 read dummy byte */\
    SECTOR_LAYOUT_REGULAR,  /* sane sectors */\
    {4096,{0,{0}}},         /* regular sector size */\
    0x05,                   /* SPI_RDSR */\
    0x00,                   /* no SPI_WRSR */\
    0x01,                   /* SPI_WIP_BIT_MASK */\
  },\
  {\
    ST_M25PE20,\
    256,                    /* page size */\
    1024,                   /* num pages */\
    3,                      /* address size */\
    8,                      /* log2 clock divider */\
    0x9f,                   /* SPI_RDID */\
    0,                      /* id dummy bytes */\
    3,                      /* id size in bytes */\
    0x208012,               /* device id */\
    0x20,                   /* SPI_SSE */\
    0,                      /* full sector erase */\
    0x06,                   /* SPI_WREN */\
    0x04,                   /* SPI_WRDI */\
    PROT_TYPE_NONE,         /* no protection */\
    {{0,0},{0,0}},          /* no values */\
    0x02,                   /* SPI_PP */\
    0x0b,                   /* SPI_READFAST */\
    1,                      /* 1 read dummy byte */\
    SECTOR_LAYOUT_REGULAR,  /* sane sectors */\
    {4096,{0,{0}}},         /* regular sector size */\
    0x05,                   /* SPI_RDSR */\
    0x00,                   /* no SPI_WRSR */\
    0x01,                   /* SPI_WIP_BIT_MASK */\
  },\
  {\
    WINBOND_W25X40,\
    256,                    /* page size */\
    2048,                   /* num pages */\
    3,                      /* address size */\
    8,                      /* log2 clock divider */\
    0x9f,                   /* SPI_RDID */\
    0,                      /* id dummy bytes */\
    3,                      /* id size in bytes */\
    0xef3013,               /* device id */\
    0x20,                   /* SPI_SSE */\
    0,                      /* full sector erase */\
    0x06,                   /* SPI_WREN */\
    0x04,                   /* SPI_WRDI */\
    PROT_TYPE_SR,           /* protection through status reg */\
    {{0x1c,0x00},{0,0}},    /* no values */\
    0x02,                   /* SPI_PP */\
    0x0b,                   /* SPI_READFAST */\
    1,                      /* 1 read dummy byte */\
    SECTOR_LAYOUT_REGULAR,  /* sane sectors */\
    {4096,{0,{0}}},         /* regular sector size */\
    0x05,                   /* SPI_RDSR */\
    0x01,                   /* SPI_WRSR */\
    0x01,                   /* SPI_WIP_BIT_MASK */\
  },\
};
