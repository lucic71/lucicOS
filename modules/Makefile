# Directories containing modules

MODULE_DIR = $(wildcard */)
MODULE_INC_DIR = include/

MODULE_DIR := $(filter-out $(MODULE_INC_DIR), $(MODULE_DIR))

all:
	@echo
	@$(foreach MODULE, $(MODULE_DIR), \
		$(MAKE) -C $(MODULE); \
		echo ""; \
	)


clean:
	@echo
	@$(foreach MODULE, $(MODULE_DIR), \
		$(MAKE) -C $(MODULE) clean; \
		echo ""; \
	)
