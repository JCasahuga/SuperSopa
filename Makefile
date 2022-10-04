OPCIONS = -O2

all: program

program: program.o diccDHashing.o diccBloomFilter.o
	g++ $(OPCIONS) -o program.x  diccDHashing.o diccBloomFilter.o program.o

program.o: program.cc
	g++ $(OPCIONS) -c program.cc

diccDHashing.o: diccDHashing.cc diccDHashing.h
	g++ $(OPCIONS) -c diccDHashing.cc

diccBloomFilter.o: diccBloomFilter.cc diccBloomFilter.h
	g++ $(OPCIONS) -c diccBloomFilter.cc

# diccSortedVector: diccSortedVector.cc
# 	g++ diccSortedVector.cc -O2 -o diccSortedVector.x

# diccTrie: diccTrie.o
# 	g++ $(OPCIONS) -o diccTrie.x diccTrie.o

# diccTrie.o: diccTrie.cc diccTrie.hh
# 	g++ $(OPCIONS) -c diccTrie.o


diccTrie: diccTrie.cc
	g++ diccTrie.cc -O2 -o diccTrie.x

supersopa: supersopa.cc
	g++ supersopa.cc -O2 -o supersopa.x

clean:
	rm program.o diccDHashing.o diccBloomFilter.o diccSortedVector.o diccTrie.o supersopa.x program.x
