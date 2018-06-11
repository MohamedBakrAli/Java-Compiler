#ifndef FIRST_FOLLOW_H
#define FIRST_FOLLOW_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "convert_to_LL1.h"

using namespace std;


class first_follow
{
    public:
        first_follow();
        ~first_follow();
        void print();
        void read_from_file();
        void apply_first();
        void apply_follow();

        vector <pair < string,string > > get_first_array();
        vector <pair < string,string > > get_follow_array();
        vector <string> get_terminal();
        vector <string> get_nonterminal();
        void get_follow();



    private:

        void check1(int i, int j);
        void check2(int i, int j);
        void check3(int i, int j);
        bool is_terminal(string x);
        string get_first(string left, string part);

        void parse(string line);
        string remove_spaces(string str);
        vector <string> nonTerminal;
        vector <string> Terminal;
        vector <string> remove_empty_element(vector<string> araf);
        vector<string> _split(const string &s, char delim);
        vector <pair < string,string > > productions_;
        vector <pair < string,string > > first;
        vector <pair < string,string > > follow;
        int count_epison,epison_occur;
        convert_to_LL1 LL1_recovery;

};

#endif // FIRST_FOLLOW_H
