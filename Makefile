# Contact Manager Makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = contact_manager
IMPROVED_TARGET = contact_manager_improved
SOURCE = contact_manager.c
IMPROVED_SOURCE = contact_manager_improved.c

# Default target
all: $(IMPROVED_TARGET)

# Compile improved version
$(IMPROVED_TARGET): $(IMPROVED_SOURCE)
	$(CC) $(CFLAGS) -o $(IMPROVED_TARGET) $(IMPROVED_SOURCE)

# Compile original version
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

# Run improved version
run: $(IMPROVED_TARGET)
	./$(IMPROVED_TARGET)

# Run original version
run-original: $(TARGET)
	./$(TARGET)

# Start web server
web:
	python server.py

# Clean compiled files
clean:
	rm -f $(TARGET) $(IMPROVED_TARGET) *.exe contacts.txt

# Install dependencies (if needed)
install:
	@echo "No dependencies to install for C version"
	@echo "For web version, ensure Python 3 is installed"

# Help
help:
	@echo "Available targets:"
	@echo "  all          - Compile improved contact manager"
	@echo "  run          - Compile and run improved version"
	@echo "  run-original - Compile and run original version"
	@echo "  web          - Start web server for frontend"
	@echo "  clean        - Remove compiled files"
	@echo "  help         - Show this help message"

.PHONY: all run run-original web clean install help