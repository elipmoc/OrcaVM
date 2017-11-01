all:
.PHONY: all clean

CXX = g++
CPPFLAGS = -MD -MP -MF $(@:.o=.dep)
CXXFLAGS = -g -O3 -std=c++14 -Wall -Wextra

orcavm_object_files = bin/orca.o bin/gencode.o bin/vm.o bin/parser.o bin/lexer.o

all: bin/orcavm
bin/orcavm: $(orcavm_object_files)
	$(CXX) $(CXXFLAGS) -o $@ $^

bin/orca.o: src/OrcaVM.cpp
bin/gencode.o: src/Gencode.cpp
bin/vm.o: src/Execute.cpp
bin/parser.o: src/Parser.cpp
bin/lexer.o: src/Lexer.cpp
-include $(orcavm_object_files:.o=.dep)
$(orcavm_object_files):
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	-rm -rf bin/*.o bin/*.dep
