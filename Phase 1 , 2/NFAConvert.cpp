#include "NFAConvert.h"
#include <bitset>
#include <queue>


vector <DFAstate *> DFAstates;
vector<int> accept_states;
queue<int> q;
int cnt=1;
int num_of_nfa;

NFAConvert::NFAConvert(vector<Node *> input_nfa, int start)
{
        NFAstates=input_nfa;
        start_state=start;
        num_of_nfa=NFAstates.size();
}

DFAstate* getDFAstate() {
    DFAstate *node=new DFAstate;
    for(int i=0; i<ALPHABET; i++) {
        node->DFATransitions[i]=-1;
    }
    node->accepting=false;
    return node;

}

NFAConvert::~NFAConvert()
{
    //dtor
}

void NFAConvert::convert()
{
//    for(int i=0; i<NFAstates.size(); i++) {
//        cout<<"node"<<i<<":"<<endl;
//        for(int j=0; j<257; j++) {
//                if(NFAstates[i]->input_index[j].size()>0){
//                    cout<<"input"<<j<<":  ";
//                }
//            for(int k=0; k<NFAstates[i]->input_index[j].size(); k++){
//                cout<<NFAstates[i]->input_index[j][k]<<"\t";
//            }
//        }
//        cout<<endl;
//    }
    DFAstates.push_back(getDFAstate());
    DFAstates[0]->formingNFAstates[0]=1;
    epsilon_closure(0, DFAstates[0]->formingNFAstates);

    for(int i=0; i<num_of_nfa; i++)
    {
        if(DFAstates[0]->formingNFAstates[i]&&NFAstates[i]->isAccept)
        {
            accept_states.push_back(0);
            DFAstates[0]->accepting=true;
            DFAstates[0]->token_name=NFAstates[i]->name;
            break;
        }
    }
    q.push(0);
    while(!q.empty())
    {
        int cur=q.front();
        q.pop();
        for(int i=0; i<ALPHABET; i++)
        {
            move_NFA(DFAstates[cur]->formingNFAstates, i, DFAstates[cur]->transitions[i]);
            epsilon_closure(DFAstates[cur]->transitions[i], DFAstates[cur]->transitions[i]);
            int j;
            for(j=0; j<cnt; j++)
            {
                if(DFAstates[j]->formingNFAstates==DFAstates[cur]->transitions[i])
                {
                    DFAstates[cur]->DFATransitions[i]=j;
                    break;
                }
            }
            int forming=0;
            for(int index=0; index<num_of_nfa; index++) {
                if(DFAstates[cur]->transitions[i][index] == 1) {
                    forming=1;
                    break;
                }
            }
            if(j==cnt&&forming==1)
            {

                DFAstates[cur]->DFATransitions[i]=cnt;
                DFAstates.push_back(getDFAstate());
                DFAstates[cnt]->formingNFAstates=DFAstates[cur]->transitions[i];
                q.push(cnt);
                cnt++;
            }
        }
    }

    for(int i=0; i<DFAstates.size(); i++){
        for(int indx=0; indx<num_of_nfa; indx++) {
            if(DFAstates[i]->formingNFAstates[indx]==1&&NFAstates[indx]->isAccept) {
                accept_states.push_back(cnt);
                DFAstates[i]->accepting=true;
                DFAstates[i]->token_name=NFAstates[indx]->name;
                break;
            }
        }
    }

}

//finds the epsilon closure of "nfa_state" and put the result into "closure"
void NFAConvert::epsilon_closure(int nfa_state, bitset<MAX_NFA_STATES> &closure)
{
    for(int i=0; i<NFAstates[nfa_state]->input_index[256].size(); i++)
    {
        int newState=NFAstates[nfa_state]->input_index[256][i];
        closure[newState]=1;
        epsilon_closure(newState, closure);
    }
}



//finds the epsilon closure of the set "nfa_set" and put the result into closure
void NFAConvert::epsilon_closure(bitset<MAX_NFA_STATES> nfa_set, bitset<MAX_NFA_STATES> &closure)
{
    for(int i=0; i<num_of_nfa; i++)
    {
        if(nfa_set[i]==1)
            epsilon_closure(i, closure);
    }
}


//finds result states of giving input "input" to the state "start_state"
void NFAConvert::move_NFA(int start_state, int input, bitset<MAX_NFA_STATES> &res)
{
    for(int i=0; i<NFAstates[start_state]->input_index[input].size(); i++)
    {
        int newState=NFAstates[start_state]->input_index[input][i];
        res[newState]=1;
    }
}

//finds result states of giving input "input" to any state of "start_states"
void NFAConvert::move_NFA(bitset<MAX_NFA_STATES> start_states, int input, bitset<MAX_NFA_STATES> &res)
{
    for(int i=0; i<num_of_nfa; i++)
    {
        if(start_states[i]==1)
        {
            move_NFA(i, input, res);
        }
    }
}

vector<DFAstate *> NFAConvert::getResult(){
    return DFAstates;
}

void NFAConvert::print_DFA() {
    for(int j=0; j<cnt; j++){
        cout<<"Forming states node"<<j;
        if(DFAstates[j]->accepting==1) {
            cout<<"  accepting   ";
        }
        cout<<":  ";
        for(int i=0; i<MAX_NFA_STATES; i++) {
            if(DFAstates[j]->formingNFAstates[i]==1) {
                cout<<i<<"  ";
            }
        }
        cout<<endl;
    }

    cout<<endl<<endl<<endl;
    for(int i=0; i<cnt; i++) {
            cout<<"state"<<i<<"transitions:"<<endl;
        for(int j=0; j<ALPHABET; j++){
            if(DFAstates[i]->DFATransitions[j]!=-1){
                cout<<"input"<<j<<": "<<DFAstates[i]->DFATransitions[j]<<"\t";
            }
//                cout<<DFAstates[i]->DFATransitions[j]<<" ";

        }
        cout<<endl<<endl;
    }
    cout<<DFAstates.size();
}
