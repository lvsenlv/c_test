OBJECTS = main.o 3tcloud_test.o log.o
CFLAGS = -g -c 

test : $(OBJECTS)
	gcc -g -o test $(OBJECTS)

main.o : 3tcloud_test.h log.h
	gcc $(CFLAGS) main.c

3tcloud_test.o : 3tcloud_test.h log.h
	gcc $(CFLAGS) 3tcloud_test.c

log.o : log.h
	gcc $(CFLAGS) log.c

clean :
	rm  -f $(OBJECTS) test
