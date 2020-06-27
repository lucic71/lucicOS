PUBLIC_LIBRARY_DIR := so/
INCLUDE_DIR := include/

# Directories containing actual code for libraries.

LIBRARY_DIRS = $(wildcard */)
LIBRARY_DIRS := $(filter-out $(PUBLIC_LIBRARY_DIR), $(LIBRARY_DIRS))
LIBRARY_DIRS := $(filter-out $(INCLUDE_DIR), $(LIBRARY_DIRS))

# Library objects.

LIBRARY_OBJS = $(foreach TMP, $(LIBRARY_DIRS), $(wildcard $(TMP)lobj/*))

# Name of the resulted shared object.

SO := libklib.a

# Archiver flags

ARFLAGS = rcs

# Makefile for each library

MAKEFILE = Makefile.Library

all: lib_build
	mkdir -p $(PUBLIC_LIBRARY_DIR)
	$(AR) $(ARFLAGS) $(PUBLIC_LIBRARY_DIR)$(SO) $(LIBRARY_OBJS)

lib_build:
	@echo
	@$(foreach LIB, $(LIBRARY_DIRS), \
		cp $(MAKEFILE) $(LIB)/Makefile; \
		$(MAKE) -C $(LIB); \
		$(RM) $(LIB)/Makefile; \
		echo; \
	)

clean:
	@echo
	@$(foreach LIB, $(LIBRARY_DIRS), \
		cp $(MAKEFILE) $(LIB)/Makefile; \
		$(MAKE) -C $(LIB) clean; \
		$(RM) $(LIB)/Makefile; \
		echo; \
	)
	@$(RM) -rv $(PUBLIC_LIBRARY_DIR)
