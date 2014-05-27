XScope wrapper
==============

:scope: General Use
:description: An XScope wrapper with a possibility to disable all probes
:keywords: XScope
:boards: SOMANET

Key Features
------------

  * Enabling and disabling XScope without removing XScope functions from the code 

Description
-----------

The module allows easily enabling or disabling all XScope functions without removing them from the code.

- To enable the XScope use: ::

  #define USE_XSCOPE

- To desable the XScope remove the define. All XScope functions will be replaced with NOPs

- This may be added to CFLAGS in your project's Makefile: ::

  CFLAGS += -DUSE_XSCOPE
