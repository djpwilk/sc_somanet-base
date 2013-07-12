
CC = gcc
obj1 = ethercatcoe
obj2 = ethercatfoe
obj3 = ethercatmain
obj4 = ethercatconfiglist
obj5 = ethercatprint
obj6 = ethercatbase
obj7 = ethercattype
obj8 = nicdrv
obj9 = fw_update
obj10 = ethercatsoe
obj11 = slaveinfo
obj12 = ethercatdc
obj13 = ethercatconfig
CFLAGS = -O2 -Wall -g
LFLAGS = -O2 -lpthread -lm -lrt -lc -Wall -g


all:	fw_update slaveinfo	
	rm src/*.o 


fw_update:  src/$(obj9).o src/$(obj8).o src/$(obj5).o src/$(obj10).o src/$(obj3).o src/$(obj6).o src/$(obj2).o src/$(obj1).o src/$(obj13).o
	$(CC) -o $@ $+ $(LFLAGS)
 
slaveinfo:  src/$(obj11).o src/$(obj8).o src/$(obj5).o src/$(obj10).o src/$(obj3).o src/$(obj6).o src/$(obj12).o src/$(obj1).o src/$(obj13).o
	$(CC) -o $@ $+ $(LFLAGS)
# Tell make how to build .o files from .c files:
obj/%.o:src/%.c
	$(CC) $(CFLAGS) -c $+
	
	
	
# Removing the executable and the object files
clean:	
	rm slaveinfo fw_update			
	echo clean: make complete
