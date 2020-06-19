# loader and kmain must be the only object files placed in the root directory.

OBJECTS = loader.o kmain.o 

# Configuration directory that contains files for building the project and 
# testing it.

CONFIG_DIR := config/

# Flags for linker and compiler. Those options tell the compiler to stay chill
# and let me handle libraries, linking and other stuff.

CC = gcc
CCFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		  -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T $(CONFIG_DIR)/link.ld -m elf_i386

AS = nasm
ASFLAGS = -f elf32

# Each module directory starts with the character 'm'. MDIRS will search for such
# directories and MOBJECTS will collect the module objects to be linked with the
# root objects (loader and kmain).

MDIRS = $(wildcard m*)
MOBJECTS = $(wildcard $(MDIRS)/*.o)

.PHONY: all clean mall

# all - Default rule that build the entire project.

all: mall kernel.elf 

# mall - Recursively build all modules.

mall:
	for dir in $(MDIRS); do \
		$(MAKE) -C $$dir; \
	done

# kernel.elf - Link all root objects and module objects to create the
# kernel.elf executable

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) $(MOBJECTS) -o kernel.elf

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
	$(CC) $(CCFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

# clean, mclean - Clean unuseful files from root directory and from module
# directories

clean: mclean
	@$(RM) *.o kernel.elf os.iso bochslog.txt iso/boot/kernel.elf

mclean:
	for dir in $(MDIRS); do \
		$(MAKE) -C $$dir distclean; \
	done
