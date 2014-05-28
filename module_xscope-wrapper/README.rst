XScope wrapper
==============

:scope: General Use
:description: An XScope wrapper with a possibility to disable all probes
:keywords: SOMANET, xSCOPE
:boards: SOMANET

Key Features
------------

  * Enabling and disabling XScope without removing XScope functions from the code 

Description
-----------

The module allows easily enabling or disabling all XScope functions without removing them from the code.

To enable the xSCOPE use: ::

      #define USE_XSCOPE

To disable the xSCOPE remove the define. All xSCOPE functions will be replaced with NOPs

This may be added to CFLAGS in your project's Makefile: ::

   CFLAGS += -DUSE_XSCOPE
