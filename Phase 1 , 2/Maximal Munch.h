//
// Created by Fady Nabil Samy on 22/3/18.
//

#ifndef LEXICAL_ANALYZER_MAXIMAL_MUNCH_H
#define LEXICAL_ANALYZER_MAXIMAL_MUNCH_H

#include <map>
#include "iostream"
#include "DFAstate.h"
#include "Parser.h"
using namespace std;
const string OUTPUT_FILE_PATH = "tokens_output.txt";


class Maximal_munch {
private:
    string scan_code_file(string path);

    void add_token_to_file(vector<string> &tokens);

    vector<string> extract_tokens(string code, vector<DFAstate *> &states, Parser* pars);

    void print_symbol_table();

    map<string, string> symbol_table;

    pair<string, string> lexeme_token;

public:
    Maximal_munch(string code_file_path, vector<DFAstate *> &states,Parser* pars);

//    void Maximal_munch::maximal_engine(string code_file_path, vector<DFAstate *> &states);
};

#endif //LEXICAL_ANALYZER_MAXIMAL_MUNCH_H
