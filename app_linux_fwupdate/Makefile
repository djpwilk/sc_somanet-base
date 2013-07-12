
CC = gcc
TARGET = fw
EXEC = ethercatconfig
ex1= ethercatcoe
ex2= ethercatfoe
ex3=ethercatmain
ex4=ethercatconfiglist
ex5= ethercatprint
ex6= ethercatbase
ex7=ethercattype
ex8=nicdrv
ex9=fw_update
ex10=ethercatsoe
ex11=slaveinfo
ex12=ethercatdc
CFLAGS = -O2 -Wall -g
LFLAGS = -O2 -lpthread -lm -lrt -lc -Wall -g



LINKER   = gcc -o



# The default rule - compiling our main program:
all:	fw_update slaveinfo
	rm src/*.o 
	mv slaveinfo bin
	mv fw_update bin


fw_update:  src/$(ex9).o src/$(ex8).o src/$(ex5).o src/$(ex10).o src/$(ex3).o src/$(ex6).o src/$(ex2).o src/$(ex1).o src/$(EXEC).o
	$(CC) -o $@ $+ $(LFLAGS)
 
slaveinfo:  src/$(ex11).o src/$(ex8).o src/$(ex5).o src/$(ex10).o src/$(ex3).o src/$(ex6).o src/$(ex12).o src/$(ex1).o src/$(EXEC).o
	$(CC) -o $@ $+ $(LFLAGS)
# Tell make how to build .o files from .c files:
obj/%.o:src/%.c
	$(CC) $(CFLAGS) -c $+
	
	
	
# Removing the executable and the object files
clean: 
	rm bin/slaveinfo bin/fw_update		
	echo clean: make complete
