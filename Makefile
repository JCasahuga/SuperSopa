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

generator: generator.cc
	g++ generator.cc -O2 -o generator.x

clean:
	rm *.o *.x
