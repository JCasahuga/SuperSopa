#include <iostream>
#include <vector>
using namespace std;

#ifndef PROJECTE_SUPERSOPA_NODETRIE_H
#define PROJECTE_SUPERSOPA_NODETRIE_H

class NodeTrie {

    public:
        //Constructora
        NodeTrie();

        vector<NodeTrie*> node;
        bool esFulla;
};

#endif //PROJECTE_SUPERSOPA_NODETRIE_H
