
CC = gcc
CC_FLAGS = -c -g -Wall
CC_FLAGS = $(CPU) -c -g -fno-common

LD = gcc
LD_FLAGS =
LIBRARY_PATHS =
LIBRARIES = -lc

BINARY_NAME = hlvm

FILES = src/main.o src/arithmetic.o src/memory.o src/branching.o
INCLUDE = -I./lib

COLOR_GREEN = "\e[32m"
COLOR_RESET = "\e[0m"

all: $(FILES) $(BINARY_NAME) clean

.c.o: $(FILES)
	@$(CC) $(CC_FLAGS) $(INCLUDE) -o $@ $<
	@echo -e [$(COLOR_GREEN)CC$(COLOR_RESET)]\ \ $@

$(BINARY_NAME): $(FILES)
	@echo -e [$(COLOR_GREEN)LD$(COLOR_RESET)]\ \ $@
	@$(LD) $(LD_FLAGS) -o $@ $^ $(LIBRARIES) $(LD_SYS_LIBS) $(LIBRARIES) $(LD_SYS_LIBS)

clean:
	rm $(FILES)

.PHONY: all
