# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Output folder and targets
BIN_DIR = bin
TARGET = $(BIN_DIR)/scli
LINKS = mls mmkdir mtouch mrmdir mrm mcp mmv mcat mgrep mchmod

# Default target
all: $(BIN_DIR) $(TARGET) links

# Create the bin directory
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compile the main executable
$(TARGET): src/main.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) src/main.c
	echo "Compiled: $(TARGET)"

# Create symbolic links in the bin directory
links: $(TARGET)
	@for link in $(LINKS); do \
		ln -sf scli $(BIN_DIR)/$$link; \
		echo "Created symbolic link: $(BIN_DIR)/$$link -> scli"; \
	done

# Clean up
clean:
	rm -rf $(BIN_DIR)
	echo "Cleaned up: $(BIN_DIR)"

.PHONY: all links clean

