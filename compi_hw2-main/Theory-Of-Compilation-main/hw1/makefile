# Makefile for hw1

# Compiler
CXX := g++
# Compiler flags
CXXFLAGS := -std=c++17

# Target executable
TARGET := hw1.out

all: flex_compile $(TARGET)

# Compile lex.yy.c using flex
flex_compile: scanner.lex
	flex scanner.lex

# Compile the main program
$(TARGET): lex.yy.c hw1.cpp
	$(CXX) $(CXXFLAGS) lex.yy.c hw1.cpp -o $(TARGET)

# Clean up generated files
clean:
	rm -f lex.yy.c $(TARGET)
