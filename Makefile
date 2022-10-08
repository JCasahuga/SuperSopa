OPCIONS = -O2

all: program

program: program.o diccDHashing.o diccBloomFilter.o diccSortedVector.o
	g++ $(OPCIONS) -o program.x  diccDHashing.o diccBloomFilter.o diccSortedVector.o program.o

program.o: program.cc
	g++ $(OPCIONS) -c program.cc

diccDHashing.o: diccDHashing.cc diccDHashing.h
	g++ $(OPCIONS) -c diccDHashing.cc

diccBloomFilter.o: diccBloomFilter.cc diccBloomFilter.h
	g++ $(OPCIONS) -c diccBloomFilter.cc

diccSortedVector.o: diccSortedVector.cc diccSortedVector.h
	g++ $(OPCIONS) -c diccSortedVector.cc

# diccTrie: diccTrie.o
# 	g++ $(OPCIONS) -o diccTrie.x diccTrie.o

# diccTrie.o: diccTrie.cc diccTrie.hh
# 	g++ $(OPCIONS) -c diccTrie.o

# diccBloomFilter: diccBloomFilter.cc
# 	g++ diccBloomFilter.cc -O2 -o diccBloomFilter.x

diccTrie: diccTrie.cc
	g++ diccTrie.cc -O2 -o diccTrie.x

supersopa: supersopa.cc
	g++ supersopa.cc -O2 -o supersopa.x

clean:
	rm *.o *.x
