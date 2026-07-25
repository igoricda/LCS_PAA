# Variables
CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -O2

# Find all .cpp files
SRCS := $(wildcard *.cpp)

# Executable names (remove .cpp extension)
TARGETS := $(SRCS:.cpp=)

# Default target
all: $(TARGETS)

# Build each executable from its corresponding source
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean
clean:
	rm -f $(TARGETS)

.PHONY: all clean