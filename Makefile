
CC = gcc
CC_FLAGS = -g -Wall

FILES = src/main.c
INCLUDE = -I./src

all: $(FILES)
	$(CC) $(CC_FLAGS) $(INCLUDE) $<


.PHONY: all
