cmake_minimum_required(VERSION 3.21)
project(Projecte_SuperSopa)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(Projecte_SuperSopa diccTrie.cc Trie.cc NodeTrie.cc program.cc diccBloomFilter.cc diccDHashing.cc)
