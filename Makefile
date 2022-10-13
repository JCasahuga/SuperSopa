OPCIONS = -O2

all: program

program: program.o hashingTable.o  diccDHashing.o diccBloomFilter.o diccSortedVector.o
	g++ $(OPCIONS) -o program.x hashingTable.o  diccDHashing.o diccBloomFilter.o diccSortedVector.o program.o

program.o: program.cc
	g++ $(OPCIONS) -c program.cc

diccDHashing.o: diccDHashing.cc diccDHashing.h hashingTable.h hashingTable.cc
	g++ $(OPCIONS) -c diccDHashing.cc

HashingTable.o: hashingTable.cc hashingTable.h
	g++ $(OPCIONS) -c hashingTable.cc

diccBloomFilter.o: diccBloomFilter.cc diccBloomFilter.h
	g++ $(OPCIONS) -c diccBloomFilter.cc

diccSortedVector.o: diccSortedVector.cc diccSortedVector.h
	g++ $(OPCIONS) -c diccSortedVector.cc

generator: generator.cc
	g++ generator.cc -O2 -o generator.x

clean:
	rm *.o *.x
