# loader and kmain must be the only object files placed in the root directory.

OBJ = loader.o kmain.o 

# Configuration directory that contains files for building the project and 
# testing it.

CONFIG_DIR := config/

# Compiler settings

CC = gcc
CCFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		  -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c

# Linker settings

LD = ld
LDFLAGS = -T $(CONFIG_DIR)/link.ld -m elf_i386

# Assembler settings

AS = nasm
ASFLAGS = -f elf32

# Module directories are located in modules/
# The interfaces are placed in module/include/ and the module objects are
# located in each module under mobj/.

MODULES_ROOT_DIR := modules/
MODULE_DIR = $(wildcard $(MODULES_ROOT_DIR)/*)
MODULE_INC_DIR = $(MODULES_ROOT_DIR)/include

# Locate the mobj/ directories and their contents.

MODULE_OBJ_DIR = mobj/
MODULE_OBJ = $(foreach TMP, $(MODULE_DIR), $(wildcard $(TMP)/$(MODULE_OBJ_DIR)/*.o))

# Exclude modules/include from module directories list.

MODULE_DIR := $(filter-out $(MODULE_INC_DIR), $(MODULE_DIR))

# Libraries directory

LIB_DIR = lib/

# Include flags

INCFLAGS = $(foreach TMP, $(MODULE_INC_DIR), -I$(TMP))

.PHONY: all clean module_all

# Build 

all: lib_all | module_all kernel.elf 

# module_all - Recursively build all modules.

module_all:
	@$(call print_banner, "Building modules")
	@$(MAKE) -C $(MODULES_ROOT_DIR)
	@echo

lib_all:
	@$(call print_banner, "Building the library")
	@$(MAKE) -C $(LIB_DIR)
	@echo

# kernel.elf - Link all root objects and module objects to create the
# kernel.elf executable

kernel.elf: $(OBJ)
	@$(call print_banner, "Building the kernel")
	$(LD) $(LDFLAGS) $(OBJ) $(MODULE_OBJ) -o kernel.elf

# os.iso - Create the OS image and place the kernel fiel in GRUB directory.

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                   \
		-b boot/grub/stage2_eltorito \
		-no-emul-boot                \
		-boot-load-size 4            \
		-A os                        \
		-input-charset utf8          \
		-quiet                       \
		-boot-info-table             \
		-o os.iso 					 \
		iso

# run - Run the emulator using the config file.

BOCHS_CONFIG := $(CONFIG_DIR)/bochsrc.txt

run: os.iso
	bochs -f $(BOCHS_CONFIG) -q

# Compile and assemble c and s files.

%.o: %.c
	$(CC) $(CCFLAGS) $(INCFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean: mclean lclean
	@$(call print_banner, "Cealning root directory")
	@$(RM) *.o kernel.elf os.iso bochslog.txt iso/boot/kernel.elf

mclean:
	@$(call print_banner, "Cleaning the modules")
	$(MAKE) -C $(MODULES_ROOT_DIR) clean

lclean:
	@$(call print_banner, "Cleaning the library")
	$(MAKE) -C $(LIB_DIR) clean

# Functions

define print_banner
	@echo
	@echo "*************** $(1) ***************"
	@echo
endef
