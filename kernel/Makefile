# Settings for architecture

DEFAULT_HOST!=../default-host.sh
HOST?=DEFAULT_HOST
HOSTARCH!=../target-triplet-to-arch.sh $(HOST)

# Compiler and linker flags.

CFLAGS?=-g3
CPPFLAGS?=
LDFLAGS?=
LIBS?=

# Destination directories in sysroot.

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

# Updated compiler flags

CFLAGS:=$(CFLAGS) -ffreestanding -D__is_kernel -Iinclude -Wall -Wextra -Werror
CPPFLAGS:=$(CPPFLAGS) 
LDFLAGS:=$(LDFLAGS)
LIB_INCLUDE_FLAGS=-L./lib/so
LIBS:=$(LIBS) -nostdlib -lgcc -lklib #-lk -lgcc

# Current architecture directory

ARCHDIR=arch/$(HOSTARCH)

# Directory for architecture

include $(ARCHDIR)/make.config

# Updated compiler flags with architecture settings added

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

# Main kernel objects and architecture objects

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
kernel/kernel.o \

# Module directories

SPECIAL_DIRS=arch include kernel lib
MODULE_DIRS=$(filter-out $(SPECIAL_DIRS), $(wildcard *))
MODULE_DIRS:=$(filter-out $(wildcard Makefile*), $(MODULE_DIRS))

# Module Makefile, knows how to build each module

MODULE_MAKEFILE=Makefile.Module

# Module objects

MODULE_OBJS=$(foreach MODULE, $(MODULE_DIRS), $(wildcard $(MODULE)/*.o))

# Overall objects

OBJS=	\
	$(ARCHDIR)/crti.o \
	$(ARCHDIR)/crtbegin.o \
	$(KERNEL_OBJS) \
	$(ARCHDIR)/crtend.o \
	$(ARCHDIR)/crtn.o \

# Link list, embeds C run time objects and kernel objects.

LINK_LIST= \
	$(LDFLAGS) \
	$(ARCHDIR)/crti.o \
	$(ARCHDIR)/crtbegin.o \
	$(KERNEL_OBJS) \
	$(ARCHDIR)/crtend.o \
	$(ARCHDIR)/crtn.o \

.PHONY: all clean install install-headers install-kernel module_all \
	module_clean library_all library_clean
.SUFFIXES: .o .c .S

all: os.kernel

module_all:
	@echo
	$(foreach MODULE, $(MODULE_DIRS), \
		cp $(MODULE_MAKEFILE) $(MODULE)/Makefile; \
		$(MAKE) -C $(MODULE); \
		$(RM) $(MODULE)/Makefile; \
		echo; \
	)

module_clean:
	@echo
	$(foreach MODULE, $(MODULE_DIRS), \
		cp $(MODULE_MAKEFILE) $(MODULE)/Makefile; \
		$(MAKE) -C $(MODULE) clean; \
		$(RM) $(MODULE)/Makefile; \
		echo; \
	)

library_all:
	$(MAKE) -C lib

library_clean:
	$(MAKE) -C lib clean

os.kernel: library_all module_all $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST) $(MODULE_OBJS) \
		$(LIB_INCLUDE_FLAGS) $(LIBS)
	grub-file --is-x86-multiboot os.kernel

$(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

clean: library_clean module_clean
	rm -f os.kernel
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: os.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp os.kernel $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)
