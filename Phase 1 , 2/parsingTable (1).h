#ifndef PARSINGTABLE_H
#define PARSINGTABLE_H
#include "first_follow.h"
#include <stack>
#include <iostream>
#include <cstdlib>
using namespace std;


class parsingTable
{
    public:
        parsingTable();
        ~parsingTable();
        void print();
        void create_parsing_table();


    private:
//        void create_parsing_table();
        stack < string > after_equal_stack(string x_after_equal);
        vector <string> remove_empty_element(vector<string> araf);
        string after_equal (string x);
        string before_equal(string x);
        first_follow tok_nontok;
        vector <string> update(vector<string> s);
        string remove_spaces(string str);
        int get_terminal_index(string);
        int get_nonterminal_index(string);
        void test();
        void parse_input(stack <string> cards, string *);

        vector<string> _split(const string &s, char delim);
};

#endif // PARSINGTABLE_H
