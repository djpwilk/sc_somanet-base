Firmware Update over EtherCAT Demo (slave side)
=======================
<a href="https://github.com/synapticon/sc_sncn_motorctrl_sin/blob/master/SYNAPTICON.md">
<img align="left" src="https://s3-eu-west-1.amazonaws.com/synapticon-resources/images/logos/synapticon_fullname_blackoverwhite_280x48.png"/>
</a>
<br/>
<br/>

This application provides the functionality to program our SOMANET nodes through EtherCAT (slave side).
The application runs 2 threads on the COM_TILE.

COM_TILE:

* Thread: Ethercat Communication Handler

```
	ecat_handler(coe_out, coe_in, eoe_out, eoe_in, eoe_sig, foe_out, foe_in, pdo_out, pdo_in);
```
We need to run this thread on COM_TILE since this is only tile accessing the ethercat communication module (COM).
	
* Thread: Firmware update 

```
	firmware_update_loop(p_spi_flash, foe_out, foe_in, sig_1);
```		
We need to run this thread on COM_TILE since it has access to the flash SPI ports.

Dependencies: module_fwupdate module_nodeconfig sc_sncn_ethercat/module_ethercat

Note: Just for Core C22. COM_TILE is located on TILE 0.

