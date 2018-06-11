#include "Parser.h"
#include <stdio.h>
#include <string>
#include <vector>


std::string file_path;
std::string s;
vector<string> keys;
ExpressionEvaluator *exp_ev;
Parser::Parser(std::string file_name, ExpressionEvaluator *exp)
{
    file_path=file_name;
    exp_ev=exp;
}

Parser::~Parser()
{
    //dtor
}

void Parser::start_parsing(){
    std::string line;
    std::ifstream infile(file_path.c_str());
    while (std::getline(infile, line))
    {
        std::string token_name="";
        int index=0;
        for(int i=0; i<line.length(); i++) {
            if(line[i]=='{'){
                //key_words
                key_word(line, i+1);
                break;
            }
            else if(line[i]=='[') {
                //punctuations
                punctuation(line, i+1);
                break;
            }
            else if(line[i]==':') {
                //regular definition
                expression(token_name, line, i+1);
                break;
            }
            else if(line[i]=='=') {
                //regular expression
                definition(token_name, line, i+1);

            }
            else if(line[i]==' '){

            }
            else{
                token_name+=line[i];
            }
        }

    }

}

void Parser::punctuation(string input, int index){
    int pos=index;
    s="";
    while(pos<input.length()&&input[pos]!=']'){
        if(input[pos]==' '){
            if(s.length()>0){
                cout<<"\""<<s<<"\""<<s<<"\""<<"e\""<<endl;
                exp_ev->regToNfa(s,s,"e");
            }
            s="";
        }
        else{
            s+=input[pos];
        }
        pos++;

    }
    if(s.length()>0){
        cout<<"\""<<s<<"\""<<s<<"\""<<"e\""<<endl;
        exp_ev->regToNfa(s,s,"e");

    }
}

void Parser::key_word(string input, int index){
    int pos=index;
    s="";
    while(pos<input.length()&&input[pos]!='}'){
        if(input[pos]==' '){
            if(s.length()>0){
                exp_ev->regToNfa(s,s,"e");
                keys.push_back(s);
                cout<<"\""<<s<<"\""<<s<<"\""<<"e\""<<endl;
            }
            s="";
        }
        else{
            s+=input[pos];
        }
        pos++;

    }
    if(s.length()>0){
        cout<<"\""<<s<<"\""<<s<<"\""<<"e\""<<endl;
        exp_ev->regToNfa(s,s,"e");
        keys.push_back(s);

    }
}


void Parser::definition(string type, string input, int index){
    int pos=index;
    s="";
    while(pos<input.length()&&input[pos]==' '){
        pos++;
    }
    while(pos<input.length()) {
        if(input[pos]=='\\' &&input[pos+1]=='='){

        }
        else{
            s+=input[pos];
        }
        pos++;
    }
    if(s.length()>0){
        cout<<"\""<<type<<"\""<<s<<"\""<<"d\""<<endl;
        exp_ev->regToNfa(type,s,"d");

    }
}

void Parser::expression(string type, string input, int index){
    int pos=index;
    s="";
    while(pos<input.length()&&input[pos]==' '){
        pos++;
    }
    while(pos<input.length()) {
        if(input[pos]=='\\' &&input[pos+1]=='='){

        }
        else{
            s+=input[pos];
        }
        pos++;
    }
    if(s.length()>0){
        cout<<"\""<<type<<"\""<<s<<"\""<<"e\""<<endl;
        exp_ev->regToNfa(type,s,"e");

    }
}
vector<std::string> Parser::getKeys() {
    return keys;
}
