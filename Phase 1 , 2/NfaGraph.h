#ifndef NFAGRAPH_H
#define NFAGRAPH_H
//#include <iostream>
//#include <stdlib.h>
//#include <algorithm>
//#include <stack>
//#include <string.h>
//#include <string>
//#include <vector>
#include "Node.h"
#include <string>
#include <string.h>

using namespace std;

class NfaGraph
{
    public:
        NfaGraph();
        virtual ~NfaGraph();
        void createGraphForTerminals(string input);
        void createGraphForNonTerminals(NfaGraph *x,NfaGraph *y,string op);
        Node *getStart();   // pointer to start node of list
        Node *getAccept();   // pointer to start node of list
        vector <Node *> getNfaNodes();

    private:
        Node *start;   // pointer to start node of list
        Node *accept;   // pointer to accept node of list
};

#endif // NFAGRAPH_H
