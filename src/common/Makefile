srcs := $(wildcard *.c)
objs := $(patsubst %.c, $(OBJS_DIR)/%.o, $(srcs))
sub_dirs := $(subst ./,,$(shell find . -maxdepth 1 -type d | sed '1d'))

all : $(objs)
	@for dir in $(sub_dirs); \
	do \
	if [ -f $$dir/Makefile ];then \
		$(MAKE) -C $$dir; \
	fi ;\
	done

$(OBJS_DIR)/%.o : %.c
	$(COMPILE) $@ $< $(CFLAGS)
	 
