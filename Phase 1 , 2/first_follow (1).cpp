#include "first_follow.h"

first_follow::first_follow()
{
    count_epison = 0;
    epison_occur = 0;
    //ctor
}

first_follow::~first_follow(){

}


void first_follow::read_from_file(){
    std::ifstream infile("CFG.txt");
    string line;
    int first = 0;
    while(getline(infile,line)){
        parse(line);
        if(first == 0){
                int mid = line.find('=');
                string L = line.substr(2,mid-2);
                follow.push_back(std::make_pair(L,"$"));
                first = 1;
        }
    }
    productions_ = LL1_recovery.get_productions(productions_);
    for(int i = 0;i < productions_.size();i++){
            nonTerminal.push_back(remove_spaces(productions_[i].first));
    }
    cout << " ----------------------------------"<< "\n";
    for(int i = 0;i < nonTerminal.size();i++){
        cout <<nonTerminal[i]<<endl;
    }

    for(int i = 0;i < productions_.size();i++){
        string right = productions_[i].second;
        vector <string> s = _split(right,'|');
//        cout << right << endl;

        for(int j = 0 ; j < s.size();j++){
            vector <string> d = _split(s[j],' ');


            for(int k = 0;k < d.size();k++){

                if(is_terminal(remove_spaces(d[k])) && remove_spaces(d[k]) != "" && remove_spaces(d[k]) != "\L"){
                   // Terminal.push_back(d[k]);
//                   cout << d[k] << endl;
                d[k] = d[k].substr(1,d[k].size() - 2);
                    Terminal.push_back(remove_spaces(d[k]));

                }
                if( remove_spaces(d[k]) == "\L"){
                    Terminal.push_back(remove_spaces(d[k]));
                }
            }
            s[j] = "";
            for(int g = 0;g < d.size();g++){
                s[j] = s[j] + d[g];
                if(g != d.size() - 1)
                    s[j] = s[j] + " ";
            }
        }

        right = "";
            for(int g = 0;g < s.size();g++){
                right = right + s[g];
                if(g == s.size() - 1)
                    right = right + "";
                else {
                    right = right + " |";
                }
            }
        productions_[i].second = right;
    }

    cout << " ------------------before----------------"<< "\n";
    for(int i = 0;i < Terminal.size();i++){
        cout <<Terminal[i]<<endl;
    }

    for(int i = 0;i < Terminal.size();i++){
        string temp =Terminal[i];
        if(remove_spaces(temp) == ""){
            Terminal.erase(Terminal.begin()+i);
        }
        for(int j = i+1; j < Terminal.size();j++){
            if(remove_spaces(temp) == remove_spaces(Terminal[j])){
                cout << remove_spaces(temp) <<  " "<< remove_spaces(Terminal[j]) << endl;
                Terminal.erase(Terminal.begin()+j);
            }
        }
    }
for(int i = 0;i < Terminal.size();i++){
        string temp =Terminal[i];
        if(remove_spaces(temp) == ""){
            Terminal.erase(Terminal.begin()+i);
        }
        for(int j = i+1; j < Terminal.size();j++){
            if(remove_spaces(temp) == remove_spaces(Terminal[j])){
                cout << remove_spaces(temp) <<  " "<< remove_spaces(Terminal[j]) << endl;
                Terminal.erase(Terminal.begin()+j);
            }
        }
    }

    cout << " --------------after--------------------"<< "\n";
    for(int i = 0;i < Terminal.size();i++){
        cout <<Terminal[i]<<endl;
    }
    Terminal.push_back("$");

}




void first_follow::parse(string line){
    int mid;

    string LHS = "";
    string RHS = "";

    if(line[0] == '#'){
//            cout << line[0] << "\n";
       mid = line.find('=');
       LHS = line.substr(2,mid-2);
       LHS = remove_spaces(LHS);
       RHS = line.substr(mid+1,line.size() - 1);
       //nonTerminal.push_back(LHS);
       productions_.push_back(std::make_pair(LHS,RHS));

    } else if (line[0] == '|'){
        string first = productions_[productions_.size()-1].first;
        string second = productions_[productions_.size()-1].second;
        productions_.pop_back();
        second = second +" "+line;
        productions_.push_back(std::make_pair(first,second));
    } else {
            // generate an error
    }
}


void first_follow::print(){
    ofstream u("pro.txt");
    cout << "----------------------------------------------- " << endl;
    for(int i = 0; i < productions_.size();i++){
        u <<"tttt " <<productions_[i].first << "   " << productions_[i].second << " \n";
    }

}


string first_follow::remove_spaces(string str){
    string temp = "";
    int i;
    for(i = 0 ; i < str.size();i++){
        if(str[i] != ' ' && str[i] != '\t'){
            temp = temp + str[i];
        }
    }
return temp;
}


vector<string> first_follow::_split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}


string first_follow::get_first(string left, string part){
//    cout << left << "                    "  << part << endl;
    vector <string> note = _split(part,' ');
    note = remove_empty_element(note);
    string temp = "";

int check = 0;
    for(int i = 0;i < note.size();i++){
            cout << "note   = "<<note[i] <<endl;
              if((is_terminal(remove_spaces(note[i])))){
                temp +=note[i];
                return temp;
    }
            for(int j = 0; j < first.size() ; j++){
                cout << remove_spaces(note[i]) << "  " << remove_spaces(_split(first[j].first,'=')[0]) << endl;
                if(remove_spaces(note[i]) == remove_spaces(_split(first[j].first,'=')[0])){
                    if (remove_spaces(first[j].second) == "\L"){
                        check = 1;
                    } else {
                        temp += first[j].second;
                        temp += " |";
                    }
                }
            }
            if(check == 1){
                check = 0;
            }else {
                return temp;
            }

    }
    return temp;
}


void first_follow::apply_first(){
    string left;
    string right;
    for(int i = productions_.size()-1; i >= 0;i--){
            left = productions_[i].first;
            right = productions_[i].second;
            vector <string> toks = _split(right,'|');
            string right_after_check = "";
            for(int i = 0;i < toks.size();i++){
                    if(get_first(left,toks[i]) != ""){
                            right_after_check = get_first(left,toks[i]);
                            if(right_after_check.find('|')!= std::string::npos){
                                    vector <string> splitted = _split(right_after_check,'|');

                                    /// we need to handle if all is go to episson
                                for(int j = 0;j < splitted.size();j++){
                                    if(splitted[j] != ""){

                                                first.push_back(std::make_pair(left+" = "+ toks[i],splitted[j]));
                                    }
                                }
                            } else {
//                                        first.push_back(std::make_pair(left+" = "+ toks[i],remove_spaces(right_after_check.substr(1,right_after_check.size() - 2))));
                                          first.push_back(std::make_pair(left+" = "+ toks[i],(right_after_check)));
                            }
                    }
            }


    }
}

void first_follow::check1(int i, int j){
    string left = productions_[i].first;
    string right = productions_[j].second;
    vector <string> parts = _split(right,'|');
//    cout << left << "   +    " << right <<endl;
    for(int i = 0;i < parts.size();i++){
        if(parts[i].find(left) != std::string::npos){
//                cout << "exist" <<endl;
        vector <string> parts_of_part = _split(parts[i],' ');
        parts_of_part = remove_empty_element(parts_of_part);
//        cout << parts_of_part.size() << endl;

            for(int j = 0;j < parts_of_part.size() - 1;j++){
                if(remove_spaces(parts_of_part[j]) == remove_spaces(left)){
                      int y = j + 1;

                      string next = remove_spaces(parts_of_part[y]);

//                      cout << "check terminal or not" <<endl;
                      if(is_terminal((next)) && (next) != "\L" && next != ""){
                            follow.push_back(std::make_pair(remove_spaces(left),(next)));
//                            cout << "i am terminal" <<endl;
                      } else {
//                          cout << "i am not terminal" <<endl;
                            for(int i = 0;i < first.size();i++){
//                                    cout << "in   " << remove_spaces(_split(first[i].first,'=')[0]) <<  "   "  <<next<< endl;
                                if(next == remove_spaces(_split(first[i].first,'=')[0]) && remove_spaces(first[i].second).find("\L") == std::string::npos){
//                                        cout << "gg  " << left << "           " << remove_spaces(first[i].second) << endl;;
                                    follow.push_back(std::make_pair(remove_spaces(left),remove_spaces(first[i].second)));
                                }
                            }
                      }
                }
            }
        }
    }
}


vector <string> first_follow::remove_empty_element(vector<string> araf){
        vector <string> xd ;
        for(int i = 0;i < araf.size();i++){
            if(remove_spaces(araf[i]) != ""){
                xd.push_back(araf[i]);
            }
        }
        return xd;
}
void first_follow::get_follow(){

    for(int i = 0; i < follow.size();i++){
            string first = follow[i].first;
            string second = follow[i].second;
        for (int j = i+1;j < follow.size();j++){
            if(remove_spaces(first) == remove_spaces(follow[j].first) && remove_spaces(second) == remove_spaces(follow[j].second)){
                  follow.erase (follow.begin()+j);
            }
        }
    }
//    cout << "hehehehe" << endl;
    for(int i = 0;i < follow.size();i++){
//            cout << follow[i].first << "    "  <<follow[i].second << endl;
        if(remove_spaces(follow[i].second) == ""){
//                        cout << follow[i].first << "    "  <<follow[i].second << endl;
                              follow.erase (follow.begin()+i);
        }
    }
    print();
}


vector< pair <string , string> > first_follow::get_first_array(){
    return first;
}


vector< pair <string , string> > first_follow::get_follow_array(){
    return follow;
}

vector <string> first_follow::get_terminal(){
    return Terminal;
}

vector <string> first_follow::get_nonterminal(){
    return nonTerminal;
}
void first_follow::check2(int i, int j){
    string left = productions_[i].first;
    string left2 = productions_[j].first;
    string right = productions_[j].second;
//    cout << left << "  -  " << left2 << "  -  " << right << endl;
    vector <string> parts = _split(right,'|');
    for(int i = 0;i < parts.size();i++){
        if(parts[i].find(remove_spaces(left)) != std::string::npos){
            vector <string> parts_of_part = _split(parts[i],' ');
            parts_of_part = remove_empty_element(parts_of_part);
            for(int j = 0;j < parts_of_part.size();j++){
                if(remove_spaces(parts_of_part[j]) == remove_spaces(left) && j == parts_of_part.size()-1){

                      for(int i = 0; i < follow.size();i++){
//                          cout << " mos ==   " << follow[i].first << "     mos2 " << left2 << "\n";
                        if(remove_spaces(follow[i].first) == remove_spaces(left2)
                           && remove_spaces(follow[i].second).find("\L") == std::string::npos && remove_spaces(left2) != remove_spaces(left)){
                                follow.push_back(std::make_pair(remove_spaces(left),remove_spaces(follow[i].second)));
                        }
                      }
                }
            }
        }
    }
}



void first_follow::check3(int i, int j){
    string left = productions_[i].first;
    string left2 = productions_[j].first;
    string right = productions_[j].second;
    vector <string> parts = _split(right,'|');
    int test = 1;
    int has_epison = 0;
    int check_has_epison = 0;
    for(int i = 0;i < parts.size();i++){
        if(parts[i].find(left) != std::string::npos){
            vector <string> parts_of_part = _split(parts[i],' ');
            parts_of_part = remove_empty_element(parts_of_part);
            for(int j = 0;j < parts_of_part.size() && test == 1;j++){
                if( parts_of_part[j] == left ){
                    for(int k = j+1; k < parts_of_part.size() && test == 1;k++){
                        if(is_terminal(parts_of_part[k])){
                            test = 0;
                        } else {
                            check_has_epison++;
                            for(int h = 0; h < first.size() ;h++){
                                if(remove_spaces(first[h].first) == remove_spaces(parts_of_part[k])
                                   && remove_spaces(first[h].second).find("\L") == std::string::npos){

                                         if(is_terminal(parts_of_part[k+1])){
                                            follow.push_back(std::make_pair(left,parts_of_part[k+1]));
                                            k++;
                                         } else {
                                            for(int d = k + 1; d < parts_of_part.size();d++){
                                                    string tet = remove_spaces(parts_of_part[d]);
                                                for(int z = 0; z < first.size();z++){
                                                    if(remove_spaces(_split(first[z].first,'=')[0]) == tet && remove_spaces(first[z].second).find("\L") == std::string::npos){
                                                                follow.push_back(std::make_pair(remove_spaces(left),remove_spaces(first[z].second)));

                                                    } else if(remove_spaces(first[z].second).find("\L") == std::string::npos){
                                                                z = 0;
                                                                tet = remove_spaces(parts_of_part[d+1]);
                                                    }
                                                }
                                            }
                                         }

                                         has_epison++;
                                }
                            }
                        }
                    }

                }

        if(has_epison == check_has_epison && has_epison != 0){

               for(int i = 0; i < follow.size();i++){
//                    cout << i << endl;
//                          cout << " mos ==   " << follow[i].first << "     mos2 " << left2 << "\n";
                        if(follow[i].first == left2 && follow[i].second != "\L"){
                                follow.push_back(std::make_pair(left,remove_spaces(follow[i].second)));
                        }
                      }
        }
            }

        }
    }

}

bool first_follow::is_terminal(string x){
    for(int i = 0;i < nonTerminal.size();i++){
        if(remove_spaces(nonTerminal[i]) == remove_spaces(x)){
            return false;
        }
    }
return true;
}


void first_follow::apply_follow(){

        for(int i = 0;i < productions_.size();i++){
            string left = productions_[i].first;
            for(int j = 0; j < productions_.size();j++){
//                    cout << "first = " << productions_[j].second << "  second = " << left << "\n";
                if((productions_[j].second).find(left) != std::string::npos){
                    check1(i,j);
                    check2(i,j);
                    check3(i,j);
                }
            }
        }
}
