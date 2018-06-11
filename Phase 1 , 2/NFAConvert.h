#ifndef NFACONVERT_H
#define NFACONVERT_H
#include <vector>
#include <bitset>
#include <iostream>
#include "Node.h"
#include "NfaGraph.h"
#include "constants.h"
#include "DFAstate.h"

class NFAConvert
{
    public:
        NFAConvert(vector<Node *> input_nfa, int start);
        virtual ~NFAConvert();
        vector<Node *> NFAstates;
        void convert();
        void print_DFA();
        vector<DFAstate *> getResult();


    protected:
    private:
        int start_state;
        void epsilon_closure(int nfa_state, bitset<MAX_NFA_STATES> &closure);
        void epsilon_closure(bitset<MAX_NFA_STATES> nfa_set, bitset<MAX_NFA_STATES> &closure);
        void move_NFA(int start_state, int input, bitset<MAX_NFA_STATES> &res);
        void move_NFA(bitset<MAX_NFA_STATES> start_states, int input, bitset<MAX_NFA_STATES> &res);


};

#endif // NFACONVERT_H
