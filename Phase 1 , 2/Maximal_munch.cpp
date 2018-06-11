//#include <iostream>
//#include <fstream>
//#include <vector>
//#include "Maximal_munch.h"
//
//
//using namespace std;
//
//
//Maximal_munch::Maximal_munch(string code_file_path, vector<DFAstate *> &states) {
////    string code_file_string = scan_code_file(code_file_path);
////    vector<string> tokens = extract_tokens(code_file_string, states);
////    add_token_to_file(tokens);
//}
//
///*
// * This function is responsible to go from
// * stage to another starting with calling the nfa function
// * till outputing the final tokens file
// */
////void Maximal_munch::maximal_engine(string code_file_path, vector<DFAstate *> &states) {
////    string code_file_string = scan_code_file(code_file_path);
////    vector tokens<string> = extract_tokens(code_file_string, states);
////    add_token_to_file(tokens);
////}
//
///*
// * Function to read the code file and concatenate
// * it to one string
// */
////string Maximal_munch::scan_code_file(string path) {
////
////    ifstream file;
////    file.open(path);
////    string scanned;
////    string file_string;
////    if (!file)
////        exit(-12);
////
////    while (file >> scanned) {
////        file_string += scanned + " ";
////    }
////    file.close();
////    cout << file_string << endl;
////    return file_string;
////}
//
///*
// * The heart of the class, it tokenize the file string
// * to specific tokens of each token type.
// */
//vector<string> Maximal_munch::extract_tokens(string code, vector<DFAstate *> &states) {
//    int state_index = 0, last_accepted_char_index_in_code_string = 0;
//    int size_before = 0, size_after = 1;
//    int ascii;
//    string token;
//    vector <string> tokens;
//    DFAstate *current_state;
//
//    while (!code.empty() && size_after < size_before) {
//        for (int i = 0; i < code.size() && state_index > -1; i++) {
////            state_index = current_state.DFATransitions[ascii];
//
//            current_state = states.at(state_index);
//            if (current_state->accepting) {
//                // minus 1 to get the index of the char of the
//                // loop before this one
//                last_accepted_char_index_in_code_string = i - 1;
//                token = current_state->token_name;
//            }
//
//            // get the next char and its state
//            // i is the index of the next char not the current char
//            // this to deal with the start state of index 0 in the
//            // vector states
//            ascii = code[i];
//            state_index = current_state->DFATransitions[ascii];
//        }
//        size_before = code.size();
//        code = code.substr(last_accepted_char_index_in_code_string + 1);
//        size_after = code.size();
//        token += "\n";
//        tokens.push_back(token);
//    }
//    return tokens;
//}
//
///*
// * This funciton outputs the vector of strings to the tokens
// * file.
// */
//void Maximal_munch::add_token_to_file(vector<string> &tokens) {
////    ofstream outfile;
////    outfile.open(OUTPUT_FILE_PATH, std::ios_base::app);
////
////    for (int i = 0; i < tokens.size(); i++)
////        outfile << tokens.at(i);
////    outfile.close();
//
//}
