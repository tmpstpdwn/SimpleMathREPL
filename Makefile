# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Object files
OBJ = main.o stack.o helpers.o

# Executable name
TARGET = smrepl

# Default target to build the executable
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Rule to compile main.c
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

# Rule to compile stack.c
stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

# Rule to compile helpers.c
helpers.o: helpers.c
	$(CC) $(CFLAGS) -c helpers.c

# Clean up compiled files
clean:
	rm -f $(OBJ) $(TARGET)
