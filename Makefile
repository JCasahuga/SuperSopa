OPCIONS = -O2

all: program

program: program.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	g++ $(OPCIONS) -o program.x  diccDHashing.o diccBloomFilter.o diccSortedVector.o diccTrie.o program.o

program.o: program.cc
	g++ $(OPCIONS) -c program.cc

diccDHashing.o: diccDHashing.cc diccDHashing.h
	g++ $(OPCIONS) -c diccDHashing.cc

diccBloomFilter.o: diccBloomFilter.cc diccBloomFilter.h
	g++ $(OPCIONS) -c diccBloomFilter.cc

diccTrie.o: diccTrie.cc diccTrie.h
	g++ $(OPCIONS) -c -std=c++17 diccTrie.cc

diccSortedVector.o: diccSortedVector.cc diccSortedVector.h
	g++ $(OPCIONS) -c diccSortedVector.cc

supersopa: supersopa.cc
	g++ supersopa.cc -O2 -o supersopa.x

clean:
	rm *.o *.x
