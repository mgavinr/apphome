#====================#
# Definitions
#====================#
include Makefile.opts
SRCS    = lidebug.c
HDRS    = lidebug.h
NAME    = lidebug
OBJS_DIR = ./objs
# cpp c files
OBJS1   = $(SRCS:%.cpp=$(OBJS_DIR)/%.o)
OBJS   = $(OBJS1:%.c=$(OBJS_DIR)/%.o)
# i files
OBJSE1   = $(SRCS:%.cpp=$(OBJS_DIR)/%.i)
OBJSE2   = $(SRCS:%.cpp=$(OBJS_DIR)/%.check)
BINDIR  = ./bin
BIN 	= $(BINDIR)/$(NAME)
INSTALL = build/$(NAME).tar
LIB     = ./objs/liblidebug.a
CLIB     = ./objs/liblidebug_c.a
BDATE   = `date | sed 's/ /-/g' | sed 's/:/-/g'`

#====================#
# Make options
#====================#
all:    $(LIB)

clean:  
	@echo "*** Deleting $(LIB) $(OBJS) ..."
	@-$(RM) $(LIB) $(OBJS) 
	@-$(RM) $(INSTALL)
	@echo " "

install:  
	@echo "*** Installing ..."
	$(CP) $(HDRS) ~/jhbuild/install/include/
	$(CP) $(LIB) ~/jhbuild/install/lib/
	@echo " "

#====================#
# Make commands
#====================#

#====================#
# Make commands
#====================#
$(OBJS):    $(HDRS)

$(LIB): $(OBJS)
	@echo "Creating $@:"
	$(AR) $@ $(OBJS)
	@echo " "

$(OBJS_DIR)/%.o:    $*%.cpp
	@echo "*** Creating $@:"
	$(CPP) $(CPP_FLAGS) $*.cpp -o $@
	@echo " "

$(OBJS_DIR)/%.i:    $*%.cpp
	@echo "*** Creating $@:"
	$(CPP) $(CPP_FLAGS) -E $*.cpp -o $@
	@echo " "

$(OBJS_DIR)/%.check:    $*%.cpp
	@echo "*** Creating $@:"
	cppcheck --enable=all $(CPP_INCS) $*.cpp > $@ 2>&1
	@echo " "

$(OBJS_DIR)/%.o:    $*%.c
	@echo "*** Creating $@:"
	$(CPP) $(CPP_FLAGS) $*.c -o $@
	@echo " "
