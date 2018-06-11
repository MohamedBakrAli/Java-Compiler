#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "ExpressionEvaluator.h"

class Parser
{
    public:
        Parser(std::string file_name, ExpressionEvaluator *exp);
        virtual ~Parser();
        void start_parsing();
        vector<std::string> getKeys();
    protected:
    private:
        void punctuation(string input, int index);
        void key_word(string input, int index);
        void definition(string type, string input, int index);
        void expression(string type, string input, int index);
};

#endif // PARSER_H
