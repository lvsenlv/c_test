srcs := $(wildcard *.c)
objs = $(patsubst %.c, $(OBJS_DIR)/%.o, $(srcs))
sub_dirs := $(subst ./,,$(shell find . -maxdepth 1 -type d | sed '1d'))

all : $(objs)
	@echo $(sub_dirs)
	for dir in $(sub_dirs); \
	do \
	if [ -d $$dir/Makefile ];then \
		$(MAKE) -C $$dir; \
	fi ;\
	done

$(OBJS_DIR)/%.o : %.c
	$(CC) $(CFLAGS) $@ $<
	 
-include $(objs:.o=.d)
