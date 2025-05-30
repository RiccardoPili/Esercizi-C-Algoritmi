# Compiler settings
CC = gcc
CFLAGS = -Wall -g

# List of source files
SOURCES = bTree.c \
         kTree.c \
         list.c \
         array.c \
         heap.c

# Create a list of targets by replacing .c with nothing
TARGETS = $(SOURCES:.c=)

# Default target
all: $(SOURCES)
	$(foreach source,$(SOURCES),$(CC) $(CFLAGS) $(source) -o $(basename $(source));)

# Clean target
clean:
	rm -f $(basename $(SOURCES))