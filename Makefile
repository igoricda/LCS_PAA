# Variables
CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -O2

# Default target
all: main pdlcs reclcs

main: main.cpp lcs.cpp fileUtils.cpp
	$(CXX) $(CXXFLAGS) main.cpp lcs.cpp fileUtils.cpp -o main

pdlcs: pdlcs.cpp lcs.cpp fileUtils.cpp
	$(CXX) $(CXXFLAGS) pdlcs.cpp lcs.cpp fileUtils.cpp -o pdlcs

reclcs: reclcs.cpp lcs.cpp fileUtils.cpp
	$(CXX) $(CXXFLAGS) reclcs.cpp lcs.cpp fileUtils.cpp -o reclcs

# Clean
clean:
	rm -f main pdlcs reclcs

.PHONY: all clean