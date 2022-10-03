OPCIONS = -O2

all: diccDHashing

program.o: program.cc
	g++ $(OPCIONS) -c program.cc

diccDHashing: program.o diccDHashing.o
	g++ $(OPCIONS) -o diccDHashing.x  diccDHashing.o program.o

diccDHashing.o: diccDHashing.cc diccDHashing.h
	gcc $(OPCIONS) -c diccDHashing.cc

# diccTrie: diccTrie.o
# 	g++ $(OPCIONS) -o diccTrie.x diccTrie.o

# diccTrie.o: diccTrie.cc diccTrie.hh
# 	g++ $(OPCIONS) -c diccTrie.o

diccBloomFilter: diccBloomFilter.cc
	g++ diccBloomFilter.cc -O2 -o diccBloomFilter.x


diccSortedVector: diccSortedVector.cc
	g++ diccSortedVector.cc -O2 -o diccSortedVector.x

diccTrie: diccTrie.cc
	g++ diccTrie.cc -O2 -o diccTrie.x

supersopa: supersopa.cc
	g++ supersopa.cc -O2 -o supersopa.x

clean:
	rm program.o diccDHashing.o diccDHashing.x diccBloomFilter.o diccBloomFilter.x diccSortedVector.o diccSortedVector.x diccTrie.x diccTrie.o supersopa.x
