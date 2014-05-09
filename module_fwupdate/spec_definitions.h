
/**
 * \file SpecDefinitions.h
 * \brief Generated file for flash specs - do not edit.
 * \author Pavan Kanajar <pkanajar@synapticon.com>
 * \version 1.0
 * \date 10/04/2014
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
