# Defining the compiler:
CC=gcc

# Defining compiler flags:
CFLAGS=-O2 -Wall -g

# Defining linker flags:

LFLAGS=-O2 -lpthread -lm -lrt -lc -Wall -g

# Defining the object files:

info_o   = slaveinfo.o \
          ethercatconfig.o \
          ethercatcoe.o \
          ethercatdc.o \
          ethercatmain.o \
          ethercatbase.o \
          ethercatprint.o \
          ethercatsoe.o \
          nicdrv.o

fw_update_o   = fw_update.o \
          ethercatconfig.o \
          ethercatcoe.o \
          ethercatfoe.o \
          ethercatmain.o \
          ethercatbase.o \
          ethercatprint.o \
          ethercatsoe.o \
          nicdrv.o



# The default rule - compiling our main program:
all:	slaveinfo fw_update 
	echo all: make complete

slaveinfo: $(info_o)
	$(CC) -o $@ $+ $(LFLAGS)

fw_update: $(fw_update_o)
	$(CC) -o $@ $+ $(LFLAGS)



# Tell make how to build .o files from .c files:
%.o:%.c
	$(CC) $(CFLAGS) -c $+
	
# Removing the executable and the object files
clean: 
	rm slaveinfo fw_update *.o
	echo clean: make complete
