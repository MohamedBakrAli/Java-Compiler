#include "parsingTable.h"
#include "first_follow.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


parsingTable::parsingTable()
{

        tok_nontok.read_from_file();
        tok_nontok.apply_first();
        tok_nontok.apply_follow();
        tok_nontok.get_follow();

    //ctor
}
parsingTable::~parsingTable(){

}

void parsingTable::create_parsing_table(){
//    cout << "iam hehr" << endl;



    vector < pair <string , string> > first = tok_nontok.get_first_array();
    vector < pair <string , string> > follow = tok_nontok.get_follow_array();

//        cout << "iam hehr" <<first.size()<< endl;


    vector <string> noterm = (tok_nontok.get_nonterminal());
    vector <string> term = update(tok_nontok.get_terminal());
  int terminal_size = (term).size();
   int non_terminal_size = noterm.size();

string parse_table[non_terminal_size][terminal_size];
cout << "------------------------"<< term.size()<<"-------------------------------" << endl;
for(int i = 0;i < term.size();i++){
    cout << term[i] << endl;
}
ofstream b ("out.txt");

cout << "-------------------------------------------------------" << endl;
    for(int i = 0;i < first.size();i++){
            b << first[i].first << "  " << first[i].second << endl;
            string x_axis = remove_spaces(_split(first[i].first,'=')[0]);
            string y_axis = remove_spaces(first[i].second);
            int x = get_nonterminal_index(x_axis);
            int y = get_terminal_index(y_axis);


            b << x << "  " << y << endl;
            if(x != -1 && y != -1){
                    parse_table[x][y] = (first[i].first);
//            cout << x  << " ( " << noterm[x] << " ) " << "  "<< y <<" ( "<<term[x] << " ) " << "  " << parse_table[x][y] << endl;
            }else{
                ///error
            }
    }
    for(int i = 0;i < first.size();i++){
            b << first[i].first << "  " << first[i].second << endl;
            string x_axis = remove_spaces(_split(first[i].first,'=')[0]);
            string y_axis = remove_spaces(first[i].second);
            int x = get_nonterminal_index(x_axis);
            int y = get_terminal_index(y_axis);

            if(y_axis == "\L"){
                cout << y_axis <<"   "<<x_axis<<endl;
                for(int i = 0;i < follow.size();i++){
                        int h;
                        cout << parse_table[x][y]<<endl;
                        int tt = get_terminal_index(follow[i].second);
                    if(remove_spaces(x_axis) == remove_spaces(follow[i].first) && parse_table[x][tt] == ""){
                        h = get_terminal_index(remove_spaces(follow[i].second));
                        parse_table[x][h] = "L";
                    }
                }
            }
    }
    for(int i = 0; i < follow.size();i++){
            string x = remove_spaces(follow[i].first);
            string y = remove_spaces(follow[i].second);
            int x_index = get_nonterminal_index(x);
            int y_index = get_terminal_index(y);
            if(parse_table[x_index][y_index] == ""){
                parse_table[x_index][y_index] = "synch";
            }
    }

    for(int i = 0;i < term.size();i++){
        b << term[i] << "     " ;
    }
    b << "\n";
    for(int i = 0; i < non_terminal_size;i++){
        for (int j = 0;j < terminal_size;j++){
                b << "( " << i << " , "  << j << " ) ";
            b << noterm[i] << "  ->  ";
            b << term[j] << "  ---->  ";
            b << parse_table[i][j] << "  " ;
            b << "\n";
        }
    }




    ///function
    /**
      Assumed in the parse table:
      1- epsilon = L
      2- synchronized entry -> "synch"
      3- empty/error entry is empty string -> "".
    */
    string start_non_terminal = "";
    int i = 0;
	/// get method_body (start symbol)
    while(start_non_terminal == ""){
        if(parse_table[0][i] != "") start_non_terminal = before_equal(parse_table[0][i]);
        i++;
    }
    /**
     EXAMPLE INPUT CODE
        int y;
        float z ;
        z = -5.5;

        while(y >= x)
        {
          if (x > 2)
            {
                x = 0;
            }
          else
            {
                if (x > 2)
                {
                    if (x > 2)
                    {
                        x = 0;
                    }
                    else {
                      a = a * b;
                    }
                }
                else {
                     while(y >= x)
                    {
                      if (x > 2)
                        {
                            x = +0.0;
                        }
                    }
                }
            }
        }


        LEXICAL CONVERTION:
        int id ;
        id = num ;
        if ( id relop num ) { id = num ; } else { id = id ; }
        while ( id relop id ) { id = id addop id ; }
    */
    vector<string> parse_stack;
    stack<string> input_stack;
    string parsing_table_entry;

    parse_stack.push_back("$");
    parse_stack.push_back(start_non_terminal);
    input_stack.push("$");
    /** Read from file Lex_analizer_output.txt as input*/
    vector<string> token;
    ifstream in("Lex_analizer_output.txt");
    char Lex_analizer_output_token[255];
    string tok;
    while(in) {
        in.getline(Lex_analizer_output_token, 255);  // delim defaults to '\n'
        tok = remove_spaces(Lex_analizer_output_token);
        if(in) {
           if(tok == "assign") tok = "=";
           if(tok == "\\(") tok = "(";
           if(tok == "\\)") tok = ")";
           if(tok.substr(0, 10) == "thislexeme") tok = "num";
           token.push_back(tok);
        }
    }
    in.close();

    token = remove_empty_element(token);
    for(int i = token.size()-1; i >= 0; i--){
        cout<<"input["<<i<<"]= "<<token[i]<<endl;
        input_stack.push(token[i]);
    }
    bool errorFlag = false;
    string top_of_stack, current_sympol;
    stack<string> aux_stack;
    int aux_s_size;
    /** The output of the syntax analyzer(parser) put into file parser_stack_output.txts*/
    ofstream output_file;
    output_file.open ("parser_table_entry_output.txt");
    ofstream parser_stack_output;
    parser_stack_output.open ("parser_stack_output.txt");
    int num_of_steps = 0;
    cout<<"--------------------------------------------------------------"<<endl;
    while(1){
        num_of_steps++;
        for(int c = 0; c < parse_stack.size(); c++){
            parser_stack_output<<parse_stack[c]<<"  ";
        }
        parser_stack_output<<"\n";

        top_of_stack = parse_stack.back();
        current_sympol = input_stack.top();
       // cout<<"top_of_stack= "<<top_of_stack<<" ||current_sympol= "<<current_sympol<<endl;
        if(top_of_stack == "$" && current_sympol == "$"){
                if(errorFlag) {
                    cout << "Successful Completion with error recovery"<<endl;
                    output_file << "Successful Completion with error recovery\n";
                }
                else {
                    cout << "Successful Completion without error recovery" <<endl;
                    output_file << "Successful Completion with error recovery\n";
                }
            break;
        } else if(top_of_stack == "$" && current_sympol != "$"){
            cout << "Error unsuccessful Completion, compiler halts"<<endl;
            output_file<<"Error unsuccessful Completion, compiler halts\n";
            break;
        }

       ///  if top_of_stack and current_symbol are terminals and do not equal "$"

        if(get_terminal_index(top_of_stack) != -1
           && get_terminal_index(current_sympol) != -1
           && top_of_stack != "$"
           && current_sympol != "$"){
             parse_stack.pop_back();
             if(top_of_stack == current_sympol) {
                 cout<<"Match("<<current_sympol<<")"<<endl;
                 output_file<<"Match("<<current_sympol<<")\n";
                 input_stack.pop();
             } else {
                cout<<"Error,unmatched terminal ("<<top_of_stack<<") inserted"<<endl;
                output_file<<"Error,unmatched terminal ("<<top_of_stack<<") inserted\n";
                errorFlag = true;
             }
             continue;
        }

        /// if top_of_stack is non terminal and does not equal "$"

        if(get_nonterminal_index(top_of_stack) != -1
           && top_of_stack != "$"){

           parsing_table_entry = parse_table[get_nonterminal_index(top_of_stack)][get_terminal_index(current_sympol)];
          //  cout<<"parsing_table_entry= "<<parsing_table_entry<<endl;
           if(parsing_table_entry == ""){
             parse_stack.pop_back();
             cout<<"Error ,illegal ("<<top_of_stack<<")-discard ("<<top_of_stack<<")"<<endl;
             output_file<<"Error ,illegal ("<<top_of_stack<<")-discard ("<<top_of_stack<<")\n";
             errorFlag = true;
           } else if(remove_spaces(parsing_table_entry) =="synch"){
            parse_stack.pop_back();
            cout<<"Error,illegal ("<<current_sympol<<")-discard ("<<top_of_stack<<")"<<endl;
            output_file<<"Error,illegal ("<<current_sympol<<")-discard ("<<top_of_stack<<")\n";
            errorFlag = true;
           } else if(remove_spaces(parsing_table_entry) == "L"){
               parse_stack.pop_back();
               cout <<"-EPSILON-"<<endl;
               output_file<<"-EPSILON-\n";
           } else {
               parse_stack.pop_back();
               string k = after_equal (parsing_table_entry);
               if(k == "synch") {
                  parse_stack.pop_back();

               } else {
               aux_stack = after_equal_stack(k);
               aux_s_size = aux_stack.size();
               for(int i = 0; i < aux_s_size; i++){
                  parse_stack.push_back(aux_stack.top());
                  aux_stack.pop();
               }
               cout <<parsing_table_entry<<endl;
               output_file<<parsing_table_entry<<"\n";
             }
           }
           continue;
        }

        parse_stack.pop_back();
        cout<<"Error -discard ("<<top_of_stack<<")"<<endl;
        output_file<<"Error -discard ("<<top_of_stack<<")\n";
        errorFlag = true;
    }
    output_file.close();
    parser_stack_output.close();
    /**Print stack contents on terminal */
    cout<<"--------- parser_stack_output ------------"<<endl;
    cout<<"--------- num_of_steps= "<<num_of_steps<<" -----------"<<endl;
    ifstream file ("parser_stack_output.txt");
    string str;
    while (getline(file, str))
    {
        if(str.size() > 0)
            cout<<str<<endl;
    }
    file.close();

}


vector <string> parsingTable::remove_empty_element(vector<string> araf){
        vector <string> xd ;
        for(int i = 0;i < araf.size();i++){
            if(remove_spaces(araf[i]) != ""){
                xd.push_back(araf[i]);
            }
        }
        return xd;
}

stack < string > parsingTable::after_equal_stack(string x_after_equal){
    string s = "";
    stack<string> st;
    for(int i = 0; i < x_after_equal.size(); i++){
        if(x_after_equal[i] != ' '){
            for(int j = i; j < x_after_equal.size()+1; j++){
                if(x_after_equal[j] == ' ' || j == x_after_equal.size()) {
                    i = j;
                    st.push(s);
                    s = "";
                    break;
                }
                s += string(1, x_after_equal[j]);
            }
        }
    }
    return st;
}

string parsingTable::after_equal (string x){
    string s = "";
    for(int i = 0; i < x.size(); i++){
        if(x[i] == '='){
            for(int j = i+1; j < x.size(); j++){
                s += string(1, x[j]);
            }
            return s;
        }
    }
    return "synch";
}

string parsingTable::before_equal(string x){
    string s = "";
    for(int i = 0; i < x.size(); i++){
        if(x[i] == ' ') continue;
        if(x[i] == '=') return s;
        s += string(1, x[i]);
    }
}


void parsingTable::test(){
stack<string> tet;
tet.push("$");
tet.push("STATEMENT_LIST");
tet.push("id");
tet.push("=");
tet.push("num");
tet.push(";");
}

//
//void parsingTable::parse_input(stack <string> cards){
//    string parse[][] =
//    stack <string> st;
//    st.push("$");
//    st.push("METHOD_BODY");
//    while(cards.size()!=0){
//
//    }
//}
vector <string> parsingTable::update(vector<string> s){

    for(int i = 0;i < s.size();i++){
        if(remove_spaces(s[i]) == "\L"){
                s.erase(s.begin()+i);
        }
    }
    return s;
}
int parsingTable::get_terminal_index(string x){
    vector <string> term = update(tok_nontok.get_terminal());
    for(int i = 0;i < term.size();i++){
        if(remove_spaces(x) == remove_spaces(term[i])){
//                        cout << remove_spaces(x) << " " << remove_spaces(term[i]) << endl;
            return i;
        }
    }
    return -1;
}



int parsingTable::get_nonterminal_index(string x){
    vector <string> nonterm = tok_nontok.get_nonterminal();
    for(int i = 0;i < nonterm.size();i++){
        if(remove_spaces(x) == remove_spaces(nonterm[i])){
//                cout << remove_spaces(x) << " " << remove_spaces(nonterm[i]) << endl;
            return i;
        }
    }
    return -1;
}

vector<string> parsingTable::_split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

void parsingTable::print(){

}

string parsingTable::remove_spaces(string str){
    string temp = "";
    int i;
    for(i = 0 ; i < str.size();i++){
        if(str[i] != ' ' && str[i] != '\t'){
            temp = temp + str[i];
        }
    }
return temp;
}
