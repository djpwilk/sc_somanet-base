<<<<<<< HEAD:module_nodeconfig/README.md
Node Configuration Module
=======================
<a href="https://github.com/synapticon/sc_sncn_motorctrl_sin/blob/master/SYNAPTICON.md">
<img align="left" src="https://s3-eu-west-1.amazonaws.com/synapticon-resources/images/logos/synapticon_fullname_blackoverwhite_280x48.png"/>
</a>
<br/>
<br/>

It carries out the code parameterization necessary for the various hardware configurations possible with SOMANET. Define here your COM, Core and IFM boards.

- Create nodeconfig.h in your app's top level source directory and configure the nodestack, e.g.:

~~~~~~~~~~~~~~~{.c}
#define SOMANET_CORE c22
#define SOMANET_COM ecat
#define SOMANET_IFM dc100-rev-a
~~~~~~~~~~~~~~~

- Refer to the *.inc files included within this module to get a list of supported boards
- Include ioports.h in every source file that needs to access I/O ports

=======

/**

\page mods
\section module_nodeconfig

It carries out the code parameterization necessary for the various hardware configurations possible with SOMANET. Define here your COM, Core and IFM boards.

- Create nodeconfig.h in your app's top level source directory and configure the nodestack, e.g.:

~~~~~~~~~~~~~~~{.c}
#define SOMANET_CORE c22
#define SOMANET_COM ecat
#define SOMANET_IFM dc100-rev-a
~~~~~~~~~~~~~~~

- Refer to the *.inc files included within this module to get a list of supported boards
- Include ioports.h in every source file that needs to access I/O ports

*/

>>>>>>> 15996aaad80109e15acc3fa11f9c16ff94531ca8:module_nodeconfig/README.dox
