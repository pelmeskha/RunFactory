# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Werror -O2 -std=c++14 -fopenmp

# Target name
TARGET = main

# Sources
SOURCES = Executor.cpp main.cpp

# Compiler rules
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

# Clear
clean:
	rm -f $(TARGET)