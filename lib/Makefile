# Stand-alone directories present in lib/.

SO_DIR := so/
INC_DIR := include/

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

all: rbuild
	$(AR) $(ARFLAGS) $(SO_DIR)/$(SO) $(LIB_OBJ)

# Build all libraries recursively.

rbuild:
	for dir in $(LIB_DIR); do \
		cp $(SCRIPTS_DIR)/MakefileLib $$dir/Makefile; \
		$(MAKE) -C $$dir; \
		$(RM) $$dir/Makefile; \
	done

# Clean all libraries recursively.

clean:
	for dir in $(LIB_DIR); do \
		cp $(SCRIPTS_DIR)/MakefileLib $$dir/Makefile; \
		$(MAKE) -C $$dir clean; \
		$(RM) $$dir/Makefile; \
	done
	@$(RM) -rv $(SO_DIR)/$(SO)
