# Variables
CC = gcc                 # Compiler
CFLAGS = -Wall -Wextra   # Compilation flags
TARGET = player        # Output executable
SRC = player.c clientCommands.c     # Source file

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean up build files
clean:
	rm -f $(TARGET)

# Phony targets to avoid conflicts with files named "all" or "clean"
.PHONY: all clean
