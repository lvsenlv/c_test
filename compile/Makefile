include ../src/Make.defines

$(PROGRAM) : build
	$(CC) -o $@ $(wildcard $(OBJS_DIR)/*.o)

build : 
	@$(MAKE) -C $(FILE_DIR)/src/

.PHONY : clean

clean :
	rm -rf $(OBJS_DIR) $(PROGRAM)
