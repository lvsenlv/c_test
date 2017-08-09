CC = gcc
OBJS = common.o main.o control.o
OBJS_DIR = ./objects
LIBS = -lncursesw
DEF = -D__OS -D__LINUX -D__64BIT -D__CHINESE
$(shell mkdir -p $(OBJS_DIR))

test : $(OBJS)
	$(CC) $(wildcard $(OBJS_DIR)/*.o) -o $@ $(LIBS)

%.o : ../src/%.c
	$(CC) -c $< -o $(OBJS_DIR)/$@ -I../include $(DEF) -g -Wall $(LIBS)

clean :
	rm -rf $(OBJS_DIR) test *.*crypt
