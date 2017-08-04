CC = gcc
OBJS = common.o encryption.o
LIBS = 
DEF = -D__OS -D__LINUX -D__64BIT
$(shell mkdir -p ./objects)

test : $(OBJS)
	$(CC) $(wildcard ./objects/*.o) -o $@ $(LIBS)

%.o : ../src/%.c
	$(CC) -c $< -o $@ -I../include $(LIBS) $(DEF) -g -Wall
	mv $@ ./objects

clean :
	rm -rf objects/ test *.*crypt
