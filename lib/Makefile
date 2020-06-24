# Stand-alone directories present in lib/.

SO_DIR := so/
INC_DIR := include/

# Upper directories

ROOT_DIR := ../
SCRIPTS_DIR = $(ROOT_DIR)/scripts/

# Directories containing actual code for libraries.

LIB_DIR = $(wildcard */)
LIB_DIR := $(filter-out $(SO_DIR), $(LIB_DIR))
LIB_DIR := $(filter-out $(INC_DIR), $(LIB_DIR))

# Library objects.

LIB_OBJ = $(foreach TMP, $(LIB_DIR), $(wildcard $(TMP)/lobj/*))

# Name of the resulted shared object.

SO := libklib.a

# Archiver

AR = ar
ARFLAGS = rcs

# Makefile for each library

MAKEFILE = $(SCRIPTS_DIR)/Makefile.Library

all: rbuild
	$(AR) $(ARFLAGS) $(SO_DIR)/$(SO) $(LIB_OBJ)

# Build all libraries recursively.

rbuild:
	@echo
	@$(foreach LIB, $(LIB_DIR), \
		cp $(MAKEFILE) $(LIB)/Makefile; \
		$(MAKE) -C $(LIB); \
		$(RM) $(LIB)/Makefile; \
		echo; \
	)

# Clean all libraries recursively.

clean:
	@echo
	@$(foreach LIB, $(LIB_DIR), \
		cp $(MAKEFILE) $(LIB)/Makefile; \
		$(MAKE) -C $(LIB) clean; \
		$(RM) $(LIB)/Makefile; \
		echo; \
	)
	@$(RM) -rv $(SO_DIR)/$(SO)
