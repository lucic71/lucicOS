# Upper directories

ROOT_DIR := ../../
MODULES_DIR := ../

# Stand-alone directories

SRC_DIR := src/
OBJ_DIR := obj/
INC_DIR := $(MODULES_DIR)/include/ ./include/
MOBJ_DIR := mobj/

# MOD_OBJ - Module Object. Its name will be the same as the module so it is
# a good idea to automate that.

CURR_DIR = $(notdir $(shell pwd))
MOD_OBJ := $(MOBJ_DIR)/$(CURR_DIR).o

# Library dependencies

LIB_INC_DIR := $(ROOT_DIR)/lib/include
LIB_SO_DIR := $(ROOT_DIR)/lib/so

# Module sources and their object files

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Compiler settings

CC = gcc
CCFLAGS = -m32 -nostdlib -lgcc -nostdinc -fno-builtin -fno-stack-protector \
		  -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
HFLAGS = -MMD 

# Linker settings

LD = ld
LDFLAGS = -relocatable -m elf_i386

# Library flags

LIBFLAGS = $(foreach TMP, $(LIB_SO_DIR), -L$(TMP))
LIBS = -lklib

# INCFLAGS - include directories for each dependency. These dependencies
# include module dependencies and the include directory inside the current 
# module

INCFLAGS = $(foreach TMP, $(LIB_INC_DIR), -I$(TMP))
INCFLAGS += $(foreach TMP, $(INC_DIR), -I$(TMP))

.PHONY: all clean

# all - Default rule for building the module object.

all: $(MOD_OBJ) 

$(MOD_OBJ): $(OBJ) | $(MOBJ_DIR)
	$(LD) $(LDFLAGS) $(OBJ) -o $@ $(LIBFLAGS) $(LIBS) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CCFLAGS) $(HFLAGS) $(INCFLAGS) $< -o $@

$(OBJ_DIR) $(MOBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(OBJ_DIR) $(MOBJ_DIR) 

-include $(OBJ:.o=.d)
