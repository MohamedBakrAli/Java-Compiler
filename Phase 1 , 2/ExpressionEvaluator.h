#ifndef EXPRESSIONEVALUATOR_H
#define EXPRESSIONEVALUATOR_H
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <stack>
#include <string.h>
#include <string>
#include "NfaGraph.h"
#include "Node.h"

using namespace std;

class ExpressionEvaluator
{
    public:
        ExpressionEvaluator();
        virtual ~ExpressionEvaluator();
        void regToNfa(string name,string regexp,string type);
        vector <Node *> getNfa();

};

#endif // EXPRESSIONEVALUATOR_H
