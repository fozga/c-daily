# Root dispatcher Makefile
# Usage:
#   make day=01 test
#   make day=01 asan
#   make day=01 valgrind
#   make day=01 clean

DAY ?= $(day)

ifeq ($(strip $(DAY)),)
$(error Please provide day=NN, e.g. make day=01 test)
endif

DAY_DIR := day$(DAY)/solution

.PHONY: test asan valgrind clean check-day

test: check-day
	$(MAKE) -C $(DAY_DIR) test

asan: check-day
	$(MAKE) -C $(DAY_DIR) asan

valgrind: check-day
	$(MAKE) -C $(DAY_DIR) valgrind

clean: check-day
	$(MAKE) -C $(DAY_DIR) clean

check-day:
	@test -d "$(DAY_DIR)" || (echo "Missing $(DAY_DIR). Use day from 01 to 30." && exit 1)
