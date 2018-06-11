#ifndef NODE_H
#define NODE_H
#include <vector>
#include <stdlib.h>
#include <string>

using namespace std;

class Node
{
public:
    Node();
    virtual ~Node();
    int index;
    string name;
    bool visited;
    bool transVisited;
    bool isStart;
    bool isAccept;
    vector <Node *> input_ptr[257];
    vector <int> input_index[257];
};

#endif // NODE_H
