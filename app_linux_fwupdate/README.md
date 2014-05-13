Firmware Update over EtherCAT Demo (Host side)
=======================
<a href="https://github.com/synapticon/sc_sncn_motorctrl_sin/blob/master/SYNAPTICON.md">
<img align="left" src="https://s3-eu-west-1.amazonaws.com/synapticon-resources/images/logos/synapticon_fullname_blackoverwhite_280x48.png"/>
</a>
<br/>
<br/>

This application provides the functionality to program our SOMANET nodes through EtherCAT (host side).\n

Firmware Update Client for Synapticon SOMANET over Ethercat

 Usage : fw_update eth0 Options ID filepath
	
	Options:
		-s     specify serial number for the ethercat slave
		-seq   specify slave number in EtherCAT order 1..n
		-all   update all slaves connected to the system
    	        -scan  scan the slave/slaves connected and display their serial numbers

specify the ID number after options -s & -seq followed by /path/to/your/file

