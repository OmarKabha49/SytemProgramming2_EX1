CXX = clang++
CXXFLAGS = -std=c++11
INCLUDES = -I.
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

SOURCES = Graph.cpp Algorithms.cpp TestCounter.cpp Test.cpp Demo.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLES = demo test

all: $(EXECUTABLES)

demo: Demo.o Graph.o Algorithms.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

test: Test.o TestCounter.o Graph.o Algorithms.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

run: demo
	./demo

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: $(EXECUTABLES)
	valgrind $(VALGRIND_FLAGS) ./demo
	valgrind $(VALGRIND_FLAGS) ./test

clean:
	rm -f *.o $(EXECUTABLES)
