#include <iostream>
#include <fstream>
#include <vector>
#include "Maximal Munch.h"


using namespace std;
void trim(string &s)
{
    size_t p = s.find_first_not_of(" \t");
    s.erase(0, p);

    p = s.find_last_not_of(" \t");
    if (string::npos != p)
        s.erase(p + 1);
}

vector<string> splitStr(string txt, char ch)
{
    vector <string> strs;
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
    strs.push_back(txt.substr(initialPos, min( pos, txt.size() ) - initialPos));

    return strs;
}

Maximal_munch::Maximal_munch(string code_file_path, vector<DFAstate *> &states, Parser* pars)
{

    ofstream outfile;
    outfile.open("output.txt");
    outfile.close();
    string code_file_string = scan_code_file(code_file_path);
    vector <string> code_split = splitStr(code_file_string,' ');
    for (int i = 0; i < code_split.size(); i++){
        code_split.at(i) += " ";
        vector<string> tokens = extract_tokens(code_split.at(i), states, pars);
        add_token_to_file(tokens);
    }
//    print_symbol_table();
}

/*
 * This function is responsible to go from
 * stage to another starting with calling the nfa function
 * till outputing the final tokens file
 */
//void Maximal_munch::maximal_engine(string code_file_path, vector<DFAstate *> &states) {
//    string code_file_string = scan_code_file(code_file_path);
//    vector tokens<string> = extract_tokens(code_file_string, states);
//    add_token_to_file(tokens);
//}

/*
 * Function to read the code file and concatenate
 * it to one string
 */
string Maximal_munch::scan_code_file(string path)
{


std::ifstream file(path.c_str());

    string scanned;
    string file_string;

    while (std::getline(file, scanned))
    {
        file_string += scanned;
    }
    file.close();

    return file_string;
}

/*
 * The heart of the class, it tokenize the file string
 * to specific tokens of each token type.
 */
vector<string> Maximal_munch::extract_tokens(string code, vector<DFAstate *> &states, Parser *pars)
{
    int state_index = 0, last_accepted_char_index_in_code_string;
    int ascii;
    string lexeme;
    vector<string> tokens;
    DFAstate *current_state;
    string error;
    int index_carry;
    while (!code.empty())
    {
        string token;
        string lexeme;
        state_index = 0;
        last_accepted_char_index_in_code_string = -1;
        for (int i = 0; i < code.size() && state_index > -1; i++)
        {

            current_state = states.at(state_index);
            if (current_state->accepting)
            {
                // minus 1 to get the index of the char of the
                // loop before this one
                last_accepted_char_index_in_code_string = i - 1;
                token = current_state->token_name;
            }

            // get the next char and its state
            // i is the index of the next char not the current char
            // this to deal with the start state of index 0 in the
            // vector states
            ascii = code[i];
            state_index = current_state->DFATransitions[ascii];

        }
        lexeme = code.substr(0, last_accepted_char_index_in_code_string + 1);
        code = code.substr(last_accepted_char_index_in_code_string + 1);

        if (last_accepted_char_index_in_code_string == -1 && token.empty())
        {
            /*
             * append the error chars to the error string to
             * output in dynamic error messeges
             */
            error += code[0];
            code = code.substr(1);

        }
        else
        {
            if (!error.empty())
            {
                /*
                 * if the error string is not empty we output the string as an error
                 * and erase the error string and continue execution
                 */
                error ="this lexeme: "+ error + " does not belong to any token class";
                cout << error << endl;
                tokens.push_back(error);
                error.erase();
            }
            /*
             *
             */
            if (token == "id")
            for (int i = 0; i < pars->getKeys().size(); i++) {
                if (lexeme == pars->getKeys().at(i)) {
                    token = pars->getKeys().at(i);
                    break;
                }
            }
            token += "\n";
            tokens.push_back(token);
//            trim(lexeme);
            lexeme_token.first = lexeme;
            lexeme_token.second = token;
            symbol_table.insert(lexeme_token);
        }
    }

//    if (!error.empty())
//        cout << "this lexeme: " << error << " does not belong to any token class" << endl;

    return tokens;
}

/*
 * prints the symbol table to the console
 * only if it is not empty!
// */
//void Maximal_munch::print_symbol_table()
//{
//    if (!symbol_table.empty())
//        for (int i = 0; i < symbol_table.size(); i++) {
//            cout << sm_pair.first << "     " << sm_pair.second << endl;
//        }
//}


/*
 * This funciton outputs the vector of strings to the tokens
 * file.
 */
void Maximal_munch::add_token_to_file(vector<string> &tokens)
{

    for (int i = 0; i < tokens.size(); i++)
      cout << tokens.at(i) << endl;

    cout << tokens.size() << endl;

    ofstream outfile;
    outfile.open("Lex_analizer_output.txt", ios_base::app);

    for (int i = 0; i < tokens.size(); i++){
        outfile <<tokens.at(i);
    }
    outfile.close();

}
