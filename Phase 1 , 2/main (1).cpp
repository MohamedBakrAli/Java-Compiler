#include <iostream>
#include "convert_to_LL1.h"
#include "first_follow.h"
#include "parsingTable.h"
#include <stdio.h>
#include <vector>
#include <string.h>
#include "NfaGraph.h"
#include "ExpressionEvaluator.h"
#include "Node.h"
#include "NFAConvert.h"
#include "Parser.h"
#include "Minimization.h"
#include "Maximal Munch.h"
using namespace std;




vector<string> _split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}


string remove_spaces(string str){
    string temp = "";
    int i;
    for(i = 0 ; i < str.size();i++){
        if(str[i] != ' ' && str[i] != '\t'){
            temp = temp + str[i];
        }
    }
return temp;
}

vector <string> remove_empty_element(vector<string> araf){
        vector <string> xd ;
        for(int i = 0;i < araf.size();i++){
            if(remove_spaces(araf[i]) != ""){
                xd.push_back(araf[i]);
            }
        }
        return xd;
}

int get_max_length(string str){
    vector <string> temp;
    vector <string> split_str = _split(str,'|');
    temp = _split(split_str[0],' ');
    temp = remove_empty_element(temp);
    int t = temp.size();
    int maximmum = t;
    for(int i = 1; i < split_str.size() ; i++){
            temp = _split(split_str[i],' ');
            temp = remove_empty_element(temp);
            int t = temp.size();
//            cout << t << endl;
        if(t > maximmum)
            maximmum = t;
    }
    return maximmum;
}

vector < pair < int,vector < int > > > get_in(int maximum, vector <string> r){
    int test[r.size()];

    for(int i = 0; i < r.size();i++){
        test[i] = 0;
    }
    int out = 0;
    int gege = 0;
    vector < pair < int,vector < int > > > data;
    for(int i = 1 ; i <= maximum;i++){
            cout << "max = " << maximum << endl;;
            int check = 0;
            for(int j = 0;j < r.size();j++){
                vector <int> number_factored;
                number_factored.push_back(j);
                vector <string> split_spaces = _split(r[j],' ');
                split_spaces = remove_empty_element(split_spaces);

                if(test[j] == 0){
                for(int k = 0; k < r.size();k++){
                        if(k != j && test[k] == 0){
                                test[j] = 1;
                                vector <string> split_spaces_next = _split(r[k],' ');
                                split_spaces_next = remove_empty_element(split_spaces_next);
                                int test_size = 0;
                                for(int m = 0; m < i && m < split_spaces_next.size() && m < split_spaces.size();m++){
                                    if(split_spaces[m] == split_spaces_next[m]){
                                        test_size++;
                                        if(m == 0){
                                            gege = 1;
                                        }
                                    }
                                }
                                if(test_size == i  && gege == 1){
//                                                                     cout << k <<endl;
                                    number_factored.push_back(k);
                                    test[k] = 1;
                                    check = 1;
                                } else {
                                    if(check == 0)
                                        test[j] = 0;
                                }
                                test_size = 0;
                        }
                }

                if(gege == 1){
                    gege = 0;
                    data.push_back(std::make_pair(i,number_factored));

                }
                }
            }
    }
    return data;
}


vector < pair < string ,string > > left_factor(string left ,vector <string> temp, vector < pair < int,vector < int > > > data){
    /// temp ->  a      a c      a b      a b c      c d      c d f
    /// data ->  1      0  1  2  3
    /// data ->  1      4  5
    vector < pair < string ,string > > pro;
    int valid[temp.size()];
        temp = remove_empty_element(temp);
    for(int i = 0;i < temp.size();i++){
        valid[i] = 0;
        cout << i <<"  " <<temp[i] <<endl;
    }
    vector <string> part;
    string actual = "";
    string change_var = "X";
    string sep = "'";
    string right = "";

    for(int i = 0;i < data.size();i++){
        int number_of_common = data[i].first;
        cout <<data.size()<<endl;
        vector <int> index_of_having_common = data[i].second;
        for(int w = 0; w < index_of_having_common.size();w++){
            cout << index_of_having_common[i] <<"      ";
        }
        part = _split(temp[index_of_having_common[0]],' ');

        cout  << "ind  = "<<index_of_having_common[0] <<endl;

        part = remove_empty_element(part);
        for(int j = 0;j < number_of_common;j++){
            actual += part[j];
            actual += " ";
        }
        actual += change_var;
        for(int k = 0; k < index_of_having_common.size();k++){
                int index = index_of_having_common[k];
                valid[index] = 1;

            if(remove_spaces(temp[index]).size() == number_of_common){
                right += "L";
                right += " |";
            }else {
                vector <string> tet = _split(temp[index],' ');
                tet = remove_empty_element(tet);
                for(int u = number_of_common; u < tet.size();u++){
                    right += tet[u];
                                    right += " ";

                }
            if(k != index_of_having_common.size() - 1)
                right += " | ";
            }
        }

        pro.push_back(std::make_pair(change_var,right));
        change_var += sep;
        right = "";
        if(i != data.size() - 1 )
                actual += " | ";
    }

    for(int i = 0;i < temp.size();i++){
        if(valid[i] == 0){
            cout << i <<" here" <<endl;
            actual += " |";
            actual += temp[i];
        }
    }

    pro.push_back(std::make_pair(left,actual));

return pro;
}

int main()
{

    ExpressionEvaluator *expEv=new ExpressionEvaluator();
    Parser *parser=new Parser("Lex_analizer_grammar.txt", expEv);
    parser->start_parsing();
    vector <Node *> nfa = expEv->getNfa();
    NFAConvert* conv = new NFAConvert(nfa, 0);
    conv->convert();
    //it is the dfa table used by the minimization process and maximal munch
    vector<DFAstate *> dfa=conv->getResult();
    cout<<"num of DFA states: "<<dfa.size()<<endl;
    Maximal_munch *max_munch = new Maximal_munch("Lex_analizer_input_code.txt", dfa, parser);

    parsingTable y ;
    y.create_parsing_table();

return 0;
}

