#ifndef MINIMIZATION_H_INCLUDED
#define MINIMIZATION_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "NFAConvert.h"

using namespace std;
void initialize_table(int*, int);

class Minimization
{
    public:
        int *fill_table;
        int n_states;
        vector<int> deleted_states;
        vector<DFAstate *> DFA;
        Minimization(vector<DFAstate *> DFAstates);
        vector<DFAstate *> getDFA();
        void printDFA();
        virtual ~Minimization();
    private:
        void minimize(vector <DFAstate *> DFAstates);
        void merge_not_distinct(vector <DFAstate *> DFAstates);
        bool test_transitions(vector <DFAstate *> DFAstates,int i, int j);
        void buildDFA(vector<DFAstate *> DFAstates);
};

#endif // MINIMIZATION_H_INCLUDED
