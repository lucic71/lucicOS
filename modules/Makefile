# Directories containing modules

MODULE_DIR = $(wildcard */)
MODULE_INC_DIR = include/

MODULE_DIR := $(filter-out $(MODULE_INC_DIR), $(MODULE_DIR))

all:
	for dir in $(MODULE_DIR); do \
		$(MAKE) -C $$dir; \
	done

clean:
	for dir in $(MODULE_DIR); do \
		$(MAKE) -C $$dir clean; \
	done
