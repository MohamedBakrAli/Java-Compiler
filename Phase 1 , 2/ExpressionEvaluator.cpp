#include "ExpressionEvaluator.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <stack>
#include <string.h>
#include <string>
#include "NfaGraph.h"

using namespace std;

vector < pair<string,string> > allRegExpr;
vector <NfaGraph *> NonTerminalNFAs;
vector<Node *> nfaNodes;

ExpressionEvaluator::ExpressionEvaluator()
{
    //ctor
}

ExpressionEvaluator::~ExpressionEvaluator()
{
    //dtor
}

bool isOperation(char op)
{
    if(op == '*' || op == '|' || op == '^' || op == '+')
        return true;
    return false;
}

//normalize
string normalize(string regexp)
{
    string new_regexp = "";
    for(unsigned int i=0; i<regexp.size(); i++)
    {
        if(regexp[i] == ' ' && regexp[i-1] != ' ' && regexp[i-1] != '(' && regexp[i-1] != '|' && !isOperation(regexp[i+1]))
        {
            new_regexp += "^";
        }
        else if(regexp[i] == '(' && regexp[i-1] != ' ' && regexp[i-1] != '|' && i != 0)
        {
            new_regexp += "^";
            new_regexp += regexp[i];
        }
        else if(regexp[i] == ')' && i < (regexp.size() - 1) && !isOperation(regexp[i+1]) && regexp[i+1] != ' ')
        {
            new_regexp += regexp[i];
            new_regexp += "^";
        }
        else if (regexp[i] != ' ')
            new_regexp += regexp[i];
    }
    return new_regexp;
}

int priority(char c)
{
    switch(c)
    {
    case '*':
        return 3;
    case '+':
        return 3;
    case '^':
        return 2;
    case '|':
        return 1;
    default:
        return 0;
    }
}

string regexp_to_postfix(string regexp)
{
    string postfix="";
    stack<char> op;
    char c;
    for(unsigned int i=0; i<regexp.size(); i++)
    {
        if(isOperation(regexp[i]) && regexp[i-1] != '\\')
        {
            postfix += " ";
            while(!op.empty())
            {
                c=op.top();
                if(priority(c)>=priority(regexp[i]))
                {
                    postfix += " ";
                    postfix+=op.top();
                    postfix += " ";
                    op.pop();
                }
                else
                    break;
            }
            op.push(regexp[i]);
        }
        else if (regexp[i] == '(' && regexp[i-1] != '\\')
        {
            op.push(regexp[i]);
        }
        else if (regexp[i] == ')' && regexp[i-1] != '\\')
        {
            while(op.top()!='(')
            {
                postfix += " ";
                postfix+=op.top();
                op.pop();
            }
            op.pop();
        }
        else
        {
            postfix+=regexp[i];
        }
    }
    while(!op.empty())
    {
        postfix += " ";
        postfix += op.top();
        op.pop();
    }
    return postfix;
}

vector<string> splitStr(string txt, vector<string> &strs, char ch)
{
    unsigned int pos = txt.find( ch );
    unsigned int initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != string::npos )
    {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back(txt.substr(initialPos, min( pos, txt.size() ) - initialPos) );

    return strs;
}

int allRegExprIndex(string nfaName)
{
    for(unsigned int i = 0 ; i < allRegExpr.size() ; i++)
    {
        if(allRegExpr[i].first == nfaName)
            return i;
    }
    return -1;
}

NfaGraph * solve(string postfix)
{
    vector<string> args;
    splitStr(postfix, args, ' ');
    stack <NfaGraph *> s;
    for(unsigned int i = 0 ; i < args.size() ; i++)
    {
        if(isOperation(args[i][0]))
        {
            NfaGraph * newNfaGraph =  new NfaGraph();
            if(args[i] == "*")
            {
                NfaGraph *x = s.top();
                s.pop();
                newNfaGraph->createGraphForNonTerminals(x,x,args[i]);
            }
            else if(args[i] == "+")
            {
                NfaGraph *x = s.top();
                s.pop();
                NfaGraph * z =  new NfaGraph();
                z->createGraphForNonTerminals(x,x,"*");
                newNfaGraph->createGraphForNonTerminals(x,z,"^");
            }
            else
            {
                NfaGraph *y = s.top();
                s.pop();
                NfaGraph *x = s.top();
                s.pop();
                newNfaGraph->createGraphForNonTerminals(x,y,args[i]);
            }
            s.push(newNfaGraph);
        }
        else
        {
            int idx = allRegExprIndex(args[i]);
            if(idx == -1)
            {
                NfaGraph *newNfaGraph =  new NfaGraph();
                newNfaGraph->createGraphForTerminals(args[i]);
                s.push(newNfaGraph);
            }
            else
            {
                s.push(solve(allRegExpr.at(idx).second));
            }
        }
    }
    NfaGraph *nfa = s.top();
    s.pop();
    return nfa;
}

void ExpressionEvaluator::regToNfa(string name,string regexp,string type)
{
    string normalized = normalize(regexp);
//    cout<<"normalized = "<<normalized<<endl;
    string postfix = regexp_to_postfix(normalized);
    string normalPostfix = "";
    for(unsigned int i = 0 ; i < postfix.size() ; i++)
    {
        if((postfix[i] == ' ' && postfix[i - 1] != ' ' && i != postfix.size()-1) || postfix[i] != ' ')
            normalPostfix += postfix[i];
    }
//    cout<<"postfix = "<<normalPostfix<<endl;
    if(type == "e")
    {
        NfaGraph *nfa = solve(normalPostfix);
        nfa->getAccept()->name = name;
        NonTerminalNFAs.push_back(nfa);
    }
    allRegExpr.push_back(make_pair(name,normalPostfix));
}

int dfs(Node * node, int counter)
{
    node->visited = true;
    node->index = counter;
    counter++;
    for(unsigned int i = 0 ; i < 257 ; i++)
    {
        if(node->input_ptr[i].size() > 0)
        {
            for(unsigned int j = 0 ; j < node->input_ptr[i].size() ; j++)
            {
                if(!node->input_ptr[i].at(j)->visited)
                {
                    counter = dfs(node->input_ptr[i].at(j),counter);
                }
            }
        }
    }
    return counter;
}

//make transitions
void makeTransitions(Node * node)
{
    node->transVisited = true;
    nfaNodes.at(node->index) = node;
    for(unsigned int i = 0 ; i < 257 ; i++)
    {
        if(node->input_ptr[i].size() > 0)
        {
            for(unsigned int j = 0 ; j < node->input_ptr[i].size() ; j++)
            {
                node->input_index[i].push_back(node->input_ptr[i].at(j)->index);
            }
        }
    }

    for(unsigned int i = 0 ; i < 257 ; i++)
    {
        if(node->input_ptr[i].size() > 0)
        {
            for(unsigned int j = 0 ; j < node->input_ptr[i].size() ; j++)
            {
                if(!node->input_ptr[i].at(j)->transVisited)
                {
                    makeTransitions(node->input_ptr[i].at(j));
                }
            }
        }
    }
}

vector <Node *> ExpressionEvaluator::getNfa()
{
    NfaGraph * finalNfa =  new NfaGraph();
    for(unsigned int i = 0 ; i < NonTerminalNFAs.size() ; i++)
    {
        NonTerminalNFAs.at(i)->getStart()->isStart = false;
        finalNfa->getStart()->input_ptr[256].push_back(NonTerminalNFAs.at(i)->getStart());
    }
    int y = dfs(finalNfa->getStart(),0);
    nfaNodes.resize(y);
    makeTransitions(finalNfa->getStart());
    cout<<"#OfNodes = "<<y<<endl;
    return nfaNodes;
}
