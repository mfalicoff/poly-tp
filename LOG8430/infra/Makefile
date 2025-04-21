SHELL := /bin/bash

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
    VAGRANT_PROVIDER := parallels
else
    VAGRANT_PROVIDER := virtualbox
endif

# MAIN COMMANDS

benchmark: ## Run the benchmark
	@echo "Destroying the previous VM..."
	@vagrant destroy -f
	@echo "Running the benchmark..."
	@VAGRANT_DEFAULT_PROVIDER=$(VAGRANT_PROVIDER) vagrant up
	@vagrant destroy -f
