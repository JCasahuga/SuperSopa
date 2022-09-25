all: diccTrie.cc
	g++ diccTrie.cc -O2 -o diccTrie.x
diccTrie: diccTrie.cc
	g++ diccTrie.cc -O2 -o diccTrie.x
diccBloomFilter: diccBloomFilter.cc
	g++ diccBloomFilter.cc -O2 -o diccBloomFilter.x
diccDHashing: diccDHashing.cc
	g++ diccDHashing.cc -O2 -o diccDHashing.x
diccSortedVector: diccSortedVector.cc
	g++ diccSortedVector.cc -O2 -o diccSortedVector.x
diccTrie: diccTrie.cc
	g++ diccTrie.cc -O2 -o diccTrie.x
supersopar: supersopar.cc
	g++ supersopar.cc -O2 -o supersopar.x
