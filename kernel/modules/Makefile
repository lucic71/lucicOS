# Upper directories

ROOT_DIR := ../
SCRIPTS_DIR = $(ROOT_DIR)/scripts/

# Directories containing modules

MODULE_DIR = $(wildcard */)
MODULE_INC_DIR = include/

MODULE_DIR := $(filter-out $(MODULE_INC_DIR), $(MODULE_DIR))

# Makefile for each module

MAKEFILE = $(SCRIPTS_DIR)/Makefile.Module

all:
	@echo
	@$(foreach MODULE, $(MODULE_DIR), \
		cp $(MAKEFILE) $(MODULE)/Makefile; \
		$(MAKE) -C $(MODULE); \
		$(RM) $(MODULE)/Makefile; \
		echo; \
	)


clean:
	@echo
	@$(foreach MODULE, $(MODULE_DIR), \
		cp $(MAKEFILE) $(MODULE)/Makefile; \
		$(MAKE) -C $(MODULE) clean; \
		$(RM) $(MODULE)/Makefile; \
		echo; \
	)
