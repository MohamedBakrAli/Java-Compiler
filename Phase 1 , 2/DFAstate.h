#ifndef DFASTATE_H_INCLUDED
#define DFASTATE_H_INCLUDED
#include <bitset>
#include "constants.h"
using namespace std;

struct DFAstate
{
    bool accepting;
    bitset<1000> formingNFAstates;
    bitset<1000> transitions[ALPHABET];
    int DFATransitions[ALPHABET];
    string token_name;
};

#endif // DFASTATE_H_INCLUDED
