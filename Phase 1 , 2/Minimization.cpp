#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "Minimization.h"
#include <algorithm>
#include <vector>

Minimization::Minimization(vector <DFAstate *> DFAstates){
    n_states = DFAstates.size();
    fill_table = new int[n_states*n_states];
    initialize_table(this->fill_table, n_states);
    minimize(DFAstates);
}

Minimization::~Minimization(){
}

void initialize_table(int* fill_table, int n){
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++){
            fill_table[i *n +j] = 0;
        }
    }
}

void Minimization::minimize(vector <DFAstate *> DFAstates){
    for(int i=0; i < n_states; i++){
        for(int j=0; j < i; j++){
            if((DFAstates[i]-> accepting == true && DFAstates[j]-> accepting == false)
               || (DFAstates[i]-> accepting == false && DFAstates[j]-> accepting == true)){
                fill_table[i *n_states +j] = 1;
            }
        }
    }
    bool flag = true;
    while(flag){
        flag = false;
        for(int i=0; i < n_states; i++){
            for(int j=0; j < i; j++){
                if (this->fill_table[i * n_states +j] == 0){
                    if(test_transitions(DFAstates, i,j)){
                        this->fill_table[i *n_states +j] = 1;
                        flag = true;
                    }
                }

            }
        }
    }
    merge_not_distinct(DFAstates);
}



bool Minimization::test_transitions(vector <DFAstate *> DFAstates, int i, int j){
    for(int k=0; k < ALPHABET; k++){
        bool cond;
        int x = DFAstates[j]->DFATransitions[k];
        int y = DFAstates[i]->DFATransitions[k];
        if(x==-1 || y==-1){
            continue;
        }
        if(x > y){
            cond = (this->fill_table[x *n_states + y] == 1);
        }else{
            cond = (this->fill_table[y *n_states + x] == 1);
        }
        if(cond){
            return true;
        }
    }
    return false;
}

void Minimization::merge_not_distinct(vector <DFAstate *> DFAstates){
    for(int i=0; i < DFAstates.size(); i++){
        for(int j=0; j < i; j++){
            if (this->fill_table[i * n_states + j] == 0){
                for(int x = 0; x < DFAstates.size(); x++){
                    for(int y = 0; y < ALPHABET; y++){
                        if(DFAstates[x]-> DFATransitions[y] == i){
                            DFAstates[x] -> DFATransitions[y] = j;
                            cout << "State " << x << " Was Transitioning to "<<i <<" but now transitioning on input " << y << " to " <<j << endl;
                            }
                        }
                }
                if(find(deleted_states.begin(), deleted_states.end(), i) == deleted_states.end()){
                    deleted_states.push_back(i);
                }
            }
        }
    }
    for(int l=deleted_states.size()-1; l>=0;l--){
        DFAstates.erase(DFAstates.begin()+ deleted_states[l] -1);
        for(int x = 0; x < DFAstates.size(); x++){
            for(int y = 0; y < ALPHABET; y++){
                if(DFAstates[x]-> DFATransitions[y] > deleted_states[l]){
                    DFAstates[x]-> DFATransitions[y]--;
                }
            }
        }
    }
    this->DFA = DFAstates;
}

vector <DFAstate *> Minimization::getDFA(){
    return this->DFA;
}

void Minimization::printDFA(){
    cout << "Num Of State : " << this->DFA.size() <<endl;
    for(int i=0; i < this->DFA.size(); i++){
        if(this->DFA[i]->accepting){
            cout << "State " << i << " is Accepting state" << endl;
        } else{
            cout << "State " << i << " is not Accepting state" << endl;
        }
        for(int j=0; j<ALPHABET; j++){
            if(this->DFA[i]->DFATransitions[j]!= -1){
                cout<<"input"<<j<<": "<<this->DFA[i]->DFATransitions[j]<<endl;
            }
        }
    }
}
