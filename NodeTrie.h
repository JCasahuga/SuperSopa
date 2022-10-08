#include <iostream>
#include <vector>

using namespace std;

struct NodeTrie {
    vector<NodeTrie*> node;
    bool esFulla;

    NodeTrie() {
        node = vector<NodeTrie*>(26, nullptr);
        esFulla = false;
    }
};

#ifndef PROJECTE_SUPERSOPA_NODETRIE_H
#define PROJECTE_SUPERSOPA_NODETRIE_H

#endif //PROJECTE_SUPERSOPA_NODETRIE_H
