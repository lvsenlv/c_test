LIBS = -lncursesw -lpthread
DEF = -D__OS -D__LINUX
#DEF += -D__CHINESE

test : bill_manage.o common.o
	gcc $< -o $@ $(LIBS)

%.o : ../src/%.c
	gcc -c $< -o $@ -I../include $(LIBS) $(DEF) -g -Wall 

clean :
	rm -rf *.o test 
