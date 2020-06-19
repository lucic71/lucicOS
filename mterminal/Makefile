# SRC_DIR - Directory containing source
# OBJ_DIR - Directory where temporary objects will be created
# INC_DIR - Directory where header files are declared

SRC_DIR := src
OBJ_DIR := obj
INC_DIR := include

# MOBJECT - Module Object

MOBJECT := terminal.o

SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# CCFLAGS, LDFLAGS, INCFLAGS - Flags for linker and compiler.
# HFLAGS - MMD generates makefile dependencies so that whenever a header file
# is modified the project will be rebuilt if needed.

CC = gcc
CCFLAGS = -m32 -nostdlib -lgcc -nostdinc -fno-builtin -fno-stack-protector \
		  -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
HFLAGS = -MMD 
LDFLAGS = -relocatable -m elf_i386
INCFLAGS = -I$(INC_DIR)

.PHONY: all clean

# all - Default rule for building the module object.

all: $(MOBJECT)

# MOBJECT - Links all object into one global module object.

$(MOBJECT): $(OBJECTS) 
	ld $(LDFLAGS) $^ -o $@

# Rule that converts source files into object files.

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CCFLAGS) $(HFLAGS) $(INCFLAGS) $< -o $@

# OBJ_DIR - Creates a temporary folder containing object files.

$(OBJ_DIR):
	mkdir -p $@

# clean, mclean - deletes object files and the module object if necessary

clean:
	@$(RM) -rv $(OBJ_DIR)

distclean: clean
	@$(RM) $(MOBJECT)

# Create d files used for makefile dependencies using o files.

-include $(OBJECTS:.o=.d)
