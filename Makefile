OPCIONS = -O2

diccTrie: diccTrie.cc diccTrie.h NodeTrie.h Trie.h
	g++ -c -std=c++17 diccTrie.cc -O2 -o diccTrie.x

supersopa: supersopa.cc
	g++ -c -std=c++17 supersopa.cc -O2 -o supersopa.x

trie: Trie.cpp Trie.h NodeTrie.h
	g++ -c -std=c++17 Trie.cpp -O2 -o trie.x

clean:
	rm program.o diccDHashing.o diccBloomFilter.o diccSortedVector.o diccTrie.o supersopa.x program.x