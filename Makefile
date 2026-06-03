CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -pedantic
TARGET := sudoku
TEST_TARGET := sudoku_tests

.PHONY: all clean test

all: $(TARGET)

$(TARGET): sudoku.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(TEST_TARGET): tests.cpp sudoku.cpp
	$(CXX) $(CXXFLAGS) tests.cpp -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)
