LIBS = -lncursesw -lpthread

test : chat_tool.o common.o
	gcc $< -o $@ $(LIBS)

%.o : ../src/%.c
	gcc -c $< -o $@ -I../include $(LIBS) -D__OS -g -Wall

clean :
	rm -rf *.o test 
