#ifndef CONVERT_TO_LL1_H
#define CONVERT_TO_LL1_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class convert_to_LL1
{
    public:
        convert_to_LL1();
        ~convert_to_LL1();
      void split(string);
      void print();
      void get_result_left_factor();
      void eliminate_left_recursion();
      vector< pair <string,string> > get_productions(vector< pair < string ,string > > product);



    private:
                      vector < pair < string,string > > prod;
                      vector < pair < string,string > > prod1;

        int get_max_length(string str);
        vector < pair < int,vector < int > > > get_in(int maximum, vector <string> r);
        vector < pair < string ,string > > left_factor(string left ,vector <string> temp, vector < pair < int,vector < int > > > data);

        void read_file();
        void substitute_with_nonterminal();
        //void eliminate_left_recursion();
        int get_repeat(string sub, string RHS);
        //void get_result_left_factor();
        int get_counter(string x);
        int find_ALL(string str, string sub);
        vector <string> remove_empty_element(vector<string> araf);

        void eliminate_left_factoring();
        string remove_spaces(string);
        string access_replace(string sub, string RHS, int count);
        vector<string> _split(const string &s, char delim);
        string RHS,LHS;
        vector < string > nonTerminal;
        vector < pair < string,string> > productions;
};

#endif // CONVERT_TO_LL1_H
