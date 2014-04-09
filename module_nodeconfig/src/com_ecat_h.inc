#pragma once

/****************
 * COM EtherCAT
 ****************/
 
 /* ET1100 asynchronous parallel interface */
 extern in  port p_com_irq;
 extern in  port p_com_busy;
 extern out port p_com_wr;
 extern out port p_com_rd;
 extern out port p_com_cs;
 extern     port p_com_data;
 extern out port p_com_addr;
 
