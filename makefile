# Compiler
CC = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Include paths
INCLUDE = -I./include

# Source and Object directories
SRCDIR = ./test
OBJDIR = ./obj
BLDDIR = ./build

# Target executable name
TARGET = ./build/run_tests

# Source and Object files
SOURCES = $(wildcard $(SRCDIR)/*.cc)
OBJECTS = $(patsubst $(SRCDIR)/%.cc, $(OBJDIR)/%.o, $(SOURCES))

$(TARGET): $(OBJECTS)
	@mkdir -p $(BLDDIR)
	$(CC) $(CXXFLAGS) $(INCLUDE) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	@mkdir -p $(OBJDIR)
	$(CC) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)
