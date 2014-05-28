SOMANET NODE CONFIGURATION module
=================================

:scope: General Use
:description: the NODE CONFIGURATION is used to define various hardware configurations possible with different SOMANET modules
:keywords: SOMANET
:boards: SOMANET

Key Features
------------

   * Code parameterization necessary for the various hardware configurations possible with SOMANET
 
Description
-----------

The module carries out the code parameterization necessary for the various hardware configurations possible with SOMANET. Define here your COM, Core and IFM boards. Create *nodeconfig.h* in your app's top level source directory and configure the nodestack, e.g. ::

   #define SOMANET_CORE c22
   #define SOMANET_COM ecat
   #define SOMANET_IFM dc100-rev-a

Refer to the *.inc* files included within this module to get a list of supported boards

Include ioports.h in every source file that needs to access I/O ports

