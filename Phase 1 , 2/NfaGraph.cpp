#include "NfaGraph.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <stack>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

Node * NfaGraph::getStart()
{
    return start;
}

Node * NfaGraph::getAccept()
{
    return accept;
}

NfaGraph::NfaGraph()
{
    start = new Node();
    accept = new Node();
    start->isStart = true;
    accept->isAccept = true;
}

NfaGraph::~NfaGraph()
{
    //dtor
}


void NfaGraph::createGraphForTerminals(string input)
{
    if(input == "a-z")
    {
//        cout<<"here 1"<<endl;
        int i = 'a';
        for(int j = 0 ; j < 26 ; j++)
        {
            start->input_ptr[i+j].push_back(accept);
        }
    }
    else if(input == "A-Z")
    {
        int i = 'A';
        for(int j = 0 ; j < 26 ; j++)
        {
            start->input_ptr[i+j].push_back(accept);
        }
    }
    else if(input == "0-9")
    {
        int i = '0';
        for(int j = 0 ; j <= 9 ; j++)
        {
            start->input_ptr[i+j].push_back(accept);
        }
    }
    else if(input == "\L")
    {
        start->input_ptr[256].push_back(accept);
    }
    else if(input.size() == 1)
    {
        int idx = input[0];
        start->input_ptr[idx].push_back(accept);
    }
    else if(input.size() == 2 && input[0] == '\\')
    {
        int idx = input[1];
        start->input_ptr[idx].push_back(accept);
    }
    else
    {
        Node * node = start;
        for(int i = 0 ; i < input.size()-1; i++)
        {
            Node * newNode = new Node();
            int idx = input[i];
            node->input_ptr[idx].push_back(newNode);
            node = newNode;
        }
        int idx = input[input.size()-1];
        node->input_ptr[idx].push_back(accept);
    }
}

void NfaGraph::createGraphForNonTerminals(NfaGraph *x,NfaGraph *y,string op)
{
    if(op == "*")
    {
        x->getStart()->isStart = false;
        x->getAccept()->isAccept = false;

        x->getAccept()->input_ptr[256].push_back(x->getStart());

        start->input_ptr[256].push_back(x->getStart());

        x->getAccept()->input_ptr[256].push_back(accept);

        start->input_ptr[256].push_back(accept);
    }
    else if(op == "^")
    {
        x->getStart()->isStart = false;
        y->getStart()->isStart = false;
        x->getAccept()->isAccept = false;
        y->getAccept()->isAccept = false;

        x->getAccept()->input_ptr[256].push_back(y->getStart());

        start->input_ptr[256].push_back(x->getStart());

        y->getAccept()->input_ptr[256].push_back(accept);
    }
    else if(op == "|")
    {
        x->getStart()->isStart = false;
        y->getStart()->isStart = false;
        x->getAccept()->isAccept = false;
        y->getAccept()->isAccept = false;

        start->input_ptr[256].push_back(x->getStart());
        start->input_ptr[256].push_back(y->getStart());

        x->getAccept()->input_ptr[256].push_back(accept);
        y->getAccept()->input_ptr[256].push_back(accept);
    }
}
