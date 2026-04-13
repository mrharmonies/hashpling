# Makefile for hashpling - Cross-platform shebang interpreter
# Supports Windows (MinGW), Unix-like systems (Linux, macOS, Haiku), and DOS (DJGPP)

# Detect operating system
UNAME_S := $(shell uname -s 2>/dev/null || echo "Unknown")
UNAME_M := $(shell uname -m 2>/dev/null || echo "Unknown")

# Default compiler
CC = gcc

# C99 standard (required for loop initial declarations)
STD = -std=c99

# Warning flags
WARNINGS = -Wall -Wextra -Wpedantic -Wformat-security -Wnull-dereference -Wstack-protector -Wtrampolines

# Platform-specific settings
ifeq ($(OS),Windows_NT)
    # Windows (MinGW/MSYS2)
    DETECTED_OS = Windows
    EXECUTABLE = hp.exe
    CFLAGS = $(STD) $(WARNINGS) -O2
    LDFLAGS = -static
    INSTALL_DIR = C:/Windows
    UNINSTALL_CMD = del "$(INSTALL_DIR)\$(EXECUTABLE)"
else ifeq ($(UNAME_S),Darwin)
    # macOS
    DETECTED_OS = macOS
    EXECUTABLE = hp
    CFLAGS = $(STD) $(WARNINGS) -O2
    LDFLAGS = 
    INSTALL_DIR = /usr/local/bin
    UNINSTALL_CMD = rm -f "$(INSTALL_DIR)/$(EXECUTABLE)"
else ifeq ($(UNAME_S),Haiku)
    # Haiku OS
    DETECTED_OS = Haiku
    EXECUTABLE = hp
    CFLAGS = $(STD) $(WARNINGS) -O2
    LDFLAGS = 
    INSTALL_DIR = /boot/common/bin
    UNINSTALL_CMD = rm -f "$(INSTALL_DIR)/$(EXECUTABLE)"
else ifeq ($(UNAME_S),Linux)
    # Linux
    DETECTED_OS = Linux
    EXECUTABLE = hp
    CFLAGS = $(STD) $(WARNINGS) -O2 -D_POSIX_C_SOURCE=200809L
    LDFLAGS = 
    INSTALL_DIR = /usr/local/bin
    UNINSTALL_CMD = rm -f "$(INSTALL_DIR)/$(EXECUTABLE)"
else
    # Default/Unknown (assume Unix-like)
    DETECTED_OS = Unix-like
    EXECUTABLE = hp
    CFLAGS = $(STD) $(WARNINGS) -O2
    LDFLAGS = 
    INSTALL_DIR = /usr/local/bin
    UNINSTALL_CMD = rm -f "$(INSTALL_DIR)/$(EXECUTABLE)"
endif

# Source files
SRC_DIR = src
SRC = $(SRC_DIR)/hashpling.c
OBJ = $(SRC_DIR)/hashpling.o

# Debug build settings
DEBUG_CFLAGS = $(STD) $(WARNINGS) -g -O0 -DDEBUG
DEBUG_EXECUTABLE = $(EXECUTABLE:.exe=_debug)$(suffix $(EXECUTABLE))

# Release build settings (with optimizations)
RELEASE_CFLAGS = $(STD) $(WARNINGS) -O3 -DNDEBUG -flto
RELEASE_EXECUTABLE = $(EXECUTABLE:.exe=_release)$(suffix $(EXECUTABLE))

# Cross-compilation support
CROSS_PREFIX ?=
CROSS_CC = $(CROSS_PREFIX)gcc
CROSS_CFLAGS = $(STD) $(WARNINGS) -O2
CROSS_EXECUTABLE = $(EXECUTABLE)

# Default target
all: $(EXECUTABLE)

# Main build target
$(EXECUTABLE): $(SRC)
	@echo "Building for $(DETECTED_OS) ($(UNAME_M))..."
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Debug build
debug: $(SRC)
	@echo "Building debug version for $(DETECTED_OS)..."
	$(CC) $(DEBUG_CFLAGS) -o $(DEBUG_EXECUTABLE) $^
	@echo "Debug executable: $(DEBUG_EXECUTABLE)"

# Release build (optimized)
release: $(SRC)
	@echo "Building release version for $(DETECTED_OS)..."
	$(CC) $(RELEASE_CFLAGS) $(LDFLAGS) -o $(RELEASE_EXECUTABLE) $^
	@echo "Release executable: $(RELEASE_EXECUTABLE)"

# Cross-compilation target
cross: $(SRC)
	@echo "Cross-compiling with $(CROSS_PREFIX)gcc..."
	$(CROSS_CC) $(CROSS_CFLAGS) $(LDFLAGS) -o $(CROSS_EXECUTABLE) $^
	@echo "Cross-compiled executable: $(CROSS_EXECUTABLE)"

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -f $(EXECUTABLE) $(DEBUG_EXECUTABLE) $(RELEASE_EXECUTABLE) $(OBJ) \
	      hp hp_debug hp_release hp.exe hp_debug.exe hp_release.exe \
	      *.o *.obj *.exe *.dSYM/

# Install to system directory
install: $(EXECUTABLE)
	@echo "Installing $(EXECUTABLE) to $(INSTALL_DIR)..."
	@if [ "$(DETECTED_OS)" = "Windows" ]; then \
		if [ -d "$(INSTALL_DIR)" ]; then \
			cp "$(EXECUTABLE)" "$(INSTALL_DIR)/"; \
			echo "Installed to $(INSTALL_DIR)/$(EXECUTABLE)"; \
		else \
			echo "Error: Install directory $(INSTALL_DIR) not found"; \
			exit 1; \
		fi; \
	else \
		if [ -w "$(INSTALL_DIR)" ]; then \
			cp "$(EXECUTABLE)" "$(INSTALL_DIR)/"; \
			echo "Installed to $(INSTALL_DIR)/$(EXECUTABLE)"; \
		else \
			echo "Error: Need sudo to install to $(INSTALL_DIR)"; \
			echo "Try: sudo make install"; \
			exit 1; \
		fi; \
	fi

# Uninstall from system directory
uninstall:
	@echo "Uninstalling $(EXECUTABLE) from $(INSTALL_DIR)..."
	@if [ "$(DETECTED_OS)" = "Windows" ]; then \
		if [ -f "$(INSTALL_DIR)/$(EXECUTABLE)" ]; then \
			$(UNINSTALL_CMD); \
			echo "Uninstalled from $(INSTALL_DIR)/$(EXECUTABLE)"; \
		else \
			echo "$(EXECUTABLE) not found in $(INSTALL_DIR)"; \
		fi; \
	else \
		if [ -f "$(INSTALL_DIR)/$(EXECUTABLE)" ]; then \
			if [ -w "$(INSTALL_DIR)" ]; then \
				$(UNINSTALL_CMD); \
				echo "Uninstalled from $(INSTALL_DIR)/$(EXECUTABLE)"; \
			else \
				echo "Error: Need sudo to uninstall from $(INSTALL_DIR)"; \
				echo "Try: sudo make uninstall"; \
				exit 1; \
			fi; \
		else \
			echo "$(EXECUTABLE) not found in $(INSTALL_DIR)"; \
		fi; \
	fi

# Test the security improvements
test: $(EXECUTABLE)
	@echo "Testing hashpling security improvements..."
	@echo "Creating test scripts..."
	@echo '#!/bin/bash\necho "Safe script"' > test_safe.sh
	@echo '#!/bin/bash; rm -rf /' > test_unsafe.sh
	@echo '#!/usr/bin/env python\nprint("Hello from Python")' > test_python.hp
	@echo ""
	@echo "1. Testing safe interpreter path..."
	@./$(EXECUTABLE) test_safe.sh 2>/dev/null && echo "✓ Safe script executed" || echo "✗ Safe script failed"
	@echo ""
	@echo "2. Testing unsafe interpreter path (should fail)..."
	@./$(EXECUTABLE) test_unsafe.sh 2>/dev/null && echo "✗ Unsafe script should have failed" || echo "✓ Unsafe script correctly rejected"
	@echo ""
	@echo "3. Testing Python script..."
	@./$(EXECUTABLE) test_python.hp 2>/dev/null && echo "✓ Python script executed" || echo "✗ Python script failed"
	@echo ""
	@echo "4. Testing non-existent file..."
	@./$(EXECUTABLE) nonexistent.txt 2>/dev/null && echo "✗ Should have failed" || echo "✓ Correctly failed for non-existent file"
	@echo ""
	@echo "Cleaning up test files..."
	@rm -f test_safe.sh test_unsafe.sh test_python.hp
	@echo "Test completed."

# Quick compile check
check: $(SRC)
	$(CC) $(STD) -fsyntax-only $^

# Show build information
info:
	@echo "Build Information:"
	@echo "  OS: $(DETECTED_OS) ($(UNAME_S))"
	@echo "  Architecture: $(UNAME_M)"
	@echo "  Compiler: $(CC)"
	@echo "  C Standard: ANSI C"
	@echo "  Executable: $(EXECUTABLE)"
	@echo "  Source: $(SRC)"
	@echo "  Install directory: $(INSTALL_DIR)"
	@echo ""
	@echo "Available targets:"
	@echo "  all        - Build main executable (default)"
	@echo "  debug      - Build with debug symbols"
	@echo "  release    - Build optimized release version"
	@echo "  cross      - Cross-compile (set CROSS_PREFIX)"
	@echo "  clean      - Remove build artifacts"
	@echo "  install    - Install to system"
	@echo "  uninstall  - Uninstall from system"
	@echo "  test       - Run security tests"
	@echo "  check      - Syntax check only"
	@echo "  info       - Show build information"

# Phony targets
.PHONY: all debug release cross clean install uninstall test check info