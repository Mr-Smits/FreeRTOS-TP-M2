# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Directories
OUTPUT_DIR = output
$(shell mkdir -p $(OUTPUT_DIR))

# Source files and object files
SRCS = main.c generator.c pretraitement.c traitement.c
OBJS = $(SRCS:%.c=$(OUTPUT_DIR)/%.o)

# Output executable name
TARGET = $(OUTPUT_DIR)/freertos_project

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile source files to object files
$(OUTPUT_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OUTPUT_DIR)

# Clean and rebuild
rebuild: clean all

# Add test compilation if needed
test:
	mkdir -p $(OUTPUT_DIR)/tests
	$(CC) $(CFLAGS) tests/*.c -o $(OUTPUT_DIR)/test_executable

.PHONY: all clean rebuild test