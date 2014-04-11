#pragma once

#include <xs1.h>
#include <platform.h>

/****************
 * COM EtherCAT
 ****************/
 
 /* ET1100 asynchronous parallel interface */
on stdcore[0]: in  port p_com_irq  = XS1_PORT_1I;
on stdcore[0]: in  port p_com_busy = XS1_PORT_1J;
on stdcore[0]: out port p_com_wr   = XS1_PORT_1K;
on stdcore[0]: out port p_com_rd   = XS1_PORT_1L;
on stdcore[0]: out port p_com_cs   = XS1_PORT_1M;
on stdcore[0]:     port p_com_data = XS1_PORT_16A;
on stdcore[0]: out port p_com_addr = XS1_PORT_16B;
