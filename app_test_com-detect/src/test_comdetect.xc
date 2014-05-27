#include "com_detect.h"

#include <stdio.h>
#include "platform.h"



//#define COM_DETECT_TEST_MODULE



#ifdef COM_DETECT_TEST_MODULE

#define array_len 7
on stdcore[0]: port p_array[] = { XS1_PORT_1N,   /* unused */
                                  XS1_PORT_1M,   /* 100p */
                                  XS1_PORT_1L,   /* 220p */
                                  XS1_PORT_1K,   /* 470p */
                                  XS1_PORT_1I,   /*   1n */
                                  XS1_PORT_1G,   /*  2n2 */
                                  XS1_PORT_1H }; /* 100n */

#else

on stdcore[0]: port p_com_detect = XS1_PORT_1M;

#endif



int main(void)
{
    par {
        on stdcore[0]: {
            com_module_type_t type;
            const char com_module_names[][15] = {
                "No COM module",
                "RESERVED0",
                "COM EtherCAT",
                "RESERVED2",
                "RESERVED3",
                "RESERVED4",
                "RESERVED5",
                "RESERVED6",
                "RESERVED7",
                "RESERVED8",
                "RESERVED9",
                "RESERVED10",
                "RESERVED11",
                "Unknown module" };
#ifdef COM_DETECT_TEST_MODULE
            for (int i=0; i<array_len; i++) {
                type = com_detect(p_array[i]);

                printf("%d - %s\n\n", type , com_module_names[type]);
            }
#else
            type = com_detect(p_com_detect);
            printf("%d - %s\n\n", type , com_module_names[type]);
#endif
        }
    }
    return 0;
}
