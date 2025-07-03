# Compiler and flags
CC = gcc
CFLAGS = -Iinclude

# Directories
SRC_DIR = src
OBJ_DIR = build

# Source and object files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Executable name
TARGET = smrepl

# Default target to build the executable
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Rule to compile .c files into .o files in build/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up compiled files and binary
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
