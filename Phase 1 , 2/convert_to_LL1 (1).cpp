#include "convert_to_LL1.h"

#include <cstdlib>

convert_to_LL1::convert_to_LL1()
{
    //ctor
}

convert_to_LL1::~convert_to_LL1(){

}


/*
read from file line by line
*/

//void convert_to_LL1::read_file(){
//
//    std::ifstream infile("CFG.txt");
//    string line;
//    while(getline(infile,line)){
//        split(line);
//    }
//}

/*
split the line
*/

vector< pair <string,string> > convert_to_LL1::get_productions(vector< pair <string,string> > product){

    for(int i = 0;i < product.size();i++){
        LHS = remove_spaces(product[i].first);
        RHS = product[i].second;
        nonTerminal.push_back(LHS);
//        substitute_with_nonterminal();
        productions.push_back(std::make_pair(LHS,RHS));
    }
    eliminate_left_recursion();
    eliminate_left_factoring();
    //return vector< pair<string,string> >();
    return prod;
}


string convert_to_LL1::remove_spaces(string str){
    string temp = "";
    int i;
    for(i = 0 ; i < str.size();i++){
        if(str[i] != ' ' && str[i] != '\t'){
            temp = temp + str[i];
        }
    }
return temp;
}


void convert_to_LL1::substitute_with_nonterminal(){
    if(nonTerminal.size() == 1){
        productions.push_back(std::make_pair(LHS,RHS));
    } else {

        for(int i = 0; i < productions.size();i++){
            string prod_LHS = productions[i].first;
            string prod_RHS = productions[i].second;
//            cout << "prod_LHS = " << prod_LHS << "prod_RHS = " <<prod_RHS<<" RHS " << RHS <<endl;
            int f = get_repeat(prod_LHS, RHS);
            RHS = access_replace(prod_LHS,RHS,get_counter(prod_RHS) + 1);
//            cout << "ccccccccccccccccccccccc = " << RHS <<endl;


            if(find_ALL(RHS,prod_LHS) != -1){

                    if(get_counter(prod_RHS) == 0){
                        RHS.replace(find_ALL(RHS,prod_LHS),prod_LHS.size() ,prod_RHS);
                    } else {

                    vector <string> b = _split(prod_RHS,'|');
                    vector <string> t = _split(RHS,'|');
                    for(int i = 0 ; i < b.size();i++){
                        cout <<b[i] <<endl;
                    }
            for(int i = 0 ;i < t.size() ;i++){
                        cout << " " << t[i]<< " ";
                    }
                     int i = 0;
                    int j = 0;

                    cout << "\n";

                        for(int i = 0;i < t.size()/(f+1);i++){
                            for(int j = 0;j < b.size();j++){
                                if(t[i].find(prod_LHS) != std::string::npos){
                                    cout <<"bef = "<<t[i];
                                    t[i].replace(find_ALL(t[i],prod_LHS),prod_LHS.size() ,b[j]);
                                    cout <<"   aft = "<<t[i]<<"\n";
                                    i++;
                                }
                            }
                        }
                        cout << "hhh = " << t.size() << " " << f<<endl;

                        for(int i = t.size()/f  ; i< t.size();i++){
                            for (int j = 0;j < b.size();j++){
                                if(t[i].find(prod_LHS) != std::string::npos){
                                     for(int k = 0; k < f-1;k++){
                                                                                cout <<"bef = "<<t[i];

                                            t[i].replace(find_ALL(t[i],prod_LHS),prod_LHS.size() ,b[j]);
                                                                                cout <<"   aft = "<<t[i]<<"\n";

                                            i++;
                                     }
                                }
//
                            }
                        }
//
//                    for(int h = 0;h < f;h++){
//                            while (i <  t.size() && j < b.size()){
//                                if(t[i].find(prod_LHS) != std::string::npos){
//                                cout <<"bef = "<<t[i];
//
//                            t[i].replace(find_ALL(t[i],prod_LHS),prod_LHS.size() ,b[j]);
//                            cout <<"   aft = "<<t[i]<<"\n";
//                            j++;
//                           // if(j == b.size() - 1)
//                                i++;
//                        }
//                    }
//                    j = 0;
//                    }

                    RHS = "";
                    for(int i = 0 ; i < t.size();i++){
                        RHS+=t[i];
                        if(i != t.size()-1)
                            RHS+=" | ";
                    }
                    cout << "ggggggggggggggggggggggggggggggg = "<<RHS<<endl;
//                    for(int j = 0; j <= get_counter(prod_RHS);j++){
//
//                        RHS.replace(find_ALL(RHS,prod_LHS),prod_LHS.size() ,b[j]);
//                        cout << "iN = " << i << "  RHS = " << RHS <<endl;
//                            // i++;
//                    }
                    }
            }
        }
        productions.push_back(std::make_pair(LHS,RHS));
    }
}

int convert_to_LL1::get_counter(string x){
    int counter = 0;

    for(int i = 0;i < x.size();i++){
        if(x[i] == '|'){
            counter++;
        }
    }
    return counter;
}

//vector < int > convert_to_LL1::find_ALL(string str, string sub){
//    int i;
//    vector <int> find_start_index;
//    int j;
//    int temp;
//    int counter = 0;
//    for(i = 0;i < str.size();i++){
//            j = 0;
//            counter = 0;
//        if(str[i] == sub [j]){
//            cout <<"i = "<< i << "  "<< str[i] << "\n";
//                temp = i;
//                counter++;
//            for(j = 1 ;j < sub.size();j++){
//                i++;
//                if(str[i] == sub[j] && str[i] != ' ' && str[i] !='\t'){
//                    cout <<"in = "<< i << "  " << str[i]<< "\n";
//                    counter++;
//                }
//            }
//            cout <<"temp = " <<temp <<"counter = " << counter << endl;
//            if(temp == 0){
//                if(counter == str.size()){
//                        find_start_index.push_back(temp);
//                } else if (str[counter] == ' ' || str[counter] == '\t'){
//                        find_start_index.push_back(temp);
//                }
//            } else if (temp != 0){
//                if(temp + counter == str.size() && (str[temp - 1] == ' ' || str[temp - 1] == '\t')){
//                        find_start_index.push_back(temp);
//                } else if ((str[temp - 1] == ' ' || str[temp - 1] == '\t') &&
//                            (str[temp + counter] == ' ' || str[temp + counter] == '\t'))
//                            {
//                        find_start_index.push_back(temp);
//                            }
//            }
//        }
//    }
//    return find_start_index;
//}


int convert_to_LL1::find_ALL(string str, string sub){
    int i;
    vector <int> find_start_index;
    int j;
    int temp;
    int counter = 0;
    for(i = 0;i < str.size();i++){
            j = 0;
            counter = 0;
        if(str[i] == sub [j]){
           // cout <<"i = "<< i << "  "<< str[i] << "\n";
                temp = i;
                counter++;
            for(j = 1 ;j < sub.size();j++){
                i++;
                if(str[i] == sub[j] && str[i] != ' ' && str[i] !='\t'){
                   // cout <<"in = "<< i << "  " << str[i]<< "\n";
                    counter++;
                }
            }

            if(temp == 0){
                if(counter == str.size()){
                        return temp;
                } else if (str[counter] == ' ' || str[counter] == '\t'){
                        return temp;
                }
            } else if (temp != 0){
                if(temp + counter == str.size() && (str[temp - 1] == ' ' || str[temp - 1] == '\t')){
                        return temp;
                } else if ((str[temp - 1] == ' ' || str[temp - 1] == '\t') &&
                            (str[temp + counter] == ' ' || str[temp + counter] == '\t'))
                            {
                        return temp;
                            }
            }
        }
    }
    return -1;
}


void convert_to_LL1::print(){
    for(int i = 0;i < productions.size();i++){
//        cout << " i = " << i << " lhs = " << productions[i].first<< " rhs = " << productions[i].second<<"\n";;
    }
}


int convert_to_LL1::get_repeat(string sub, string RHS){
    int counter = 0;
    vector <string> TETE;
    std::string temp = RHS;
    int i,j;
    if(RHS.find('|') != std::string::npos){
         TETE = _split(RHS,'|');
         for(i = 0; i < TETE.size();i++){
            if(TETE[i].find(sub) != std::string::npos){
//                cout << " i  = " << i << "  tete[i] = " << TETE[i]  << "  su = " << sub<<"\n";
                counter++;
            }
         }
    }
return counter;
}


string convert_to_LL1::access_replace(string sub, string RHS, int count){
    vector <string> TETE;
    std::string temp = RHS;
    int i,j;
    if(RHS.find('|') != std::string::npos){
         TETE = _split(RHS,'|');
         for(i = 0; i < TETE.size();i++){
            if(TETE[i].find(sub) != std::string::npos){
                for(j = 1 ; j < count ;j++){
                    temp = temp + " |";
                    temp += TETE[i];
                }

            }
         }
    } else {
        for (int i = 0;i < count - 1 ;i++){
            if(RHS.find(sub) != std::string::npos)
                temp +="|";
                temp +=RHS;
        }
    }
    return temp;
}


vector<string> convert_to_LL1::_split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}




void convert_to_LL1::eliminate_left_factoring(){
    vector < pair < string,string > > prod2;

    string first,second;
    ofstream g("mos.txt");

    for(int i = 0; i < prod.size();i++)
    {
//        cout << prod[i].first << "  " << prod[i].second <<"\n";
    }


    for(int i = 0; i < prod.size();i++){
        vector< pair <string,string > > temp;
        vector< pair <string,string > > temp1;

        string left = prod[i].first;
        string right = prod[i].second;
        vector < string > rere = _split(right,'|');
        vector < pair < int,vector < int > > > u = get_in(get_max_length(right),rere);

        for(int i = 0;i < u.size();i++){
                vector<int> y = u[i].second;
                if(y.size() > 1){

                }else {
                    u.erase(u.begin() + i);
                }
                }


//                cout << "**************************"<<endl;

        temp1 = left_factor(left,rere,u);
        int j = 0;
//                cout << "**************************"<<endl;

        for(j = 0 ; j < i ;j++){
            first = prod[j].first;
            second = prod[j].second;
            temp.push_back(std::make_pair(first,second));
        }
        for(int k = temp1.size() - 1; k >= 0;k--){
            first = temp1[k].first;
            second = temp1[k].second;
            temp.push_back(std::make_pair(first,second));
        }


        for(int h = i+1; h < prod.size();h++){
            first = prod[h].first;
            second = prod[h].second;
            temp.push_back(std::make_pair(first,second));
         }
for(int i = 0;i < temp.size();i++){
//        g << i <<endl;
//        g << temp[i].first << "   " << temp[i].second << endl;
    }
//cout << prod.size()<<"\n";
for(int i = 0;i < prod.size();i++){
//        cout << "hh "<<prod[i].first << "   " << prod[i].second << endl;
    }
        prod.clear();
        for(int w = 0; w < temp.size();w++){
            first = temp[w].first;
            second = temp[w].second;
            g << first << "   " << second <<endl;
            prod.push_back(std::make_pair(first,second));
        }
//        temp.clear();
//        temp1.clear();
//prod = temp;
    }
    g << "----------------------------------------------"<<endl;
    for(int i = 0;i < prod.size();i++){
        g << prod[i].first << "   " << prod[i].second << endl;
    }
    g<< "----------------------------------------------" <<endl;
}






vector <string> convert_to_LL1::remove_empty_element(vector<string> araf){
        vector <string> xd ;
        for(int i = 0;i < araf.size();i++){
            if(remove_spaces(araf[i]) != ""){
                xd.push_back(araf[i]);
            }
        }
        return xd;
}

void convert_to_LL1::eliminate_left_recursion(){

    string left,right;
    vector <string> current,next;


    for(int i = 0;i < productions.size();i++){
        left = productions[i].first;
        right = productions[i].second;
        if(right.find(left) == std::string::npos){
            prod.push_back(std::make_pair(left,right));
        } else {
                        vector <string> subs = _split(right,'|');
                        vector < vector < string > > tok ;
                        for (int i = 0;i< subs.size();i++){
                            vector < string > part;
                            part = _split(subs[i],' ');
//                            cout << "i = " << i << "\n";
                            for(int j = 0 ;j < part.size();j++){
//                                cout << "j = " << j <<" " << "str = " << part[j] << "  ";
                            }
//                            cout << "\n";
                            tok.push_back(part);
                        }

                        for(int i = 0 ;i < tok.size();i++){
//                                cout << remove_spaces(tok[i][1])  << "  " <<remove_spaces(left) << "\n";

//                                cout << remove_spaces(tok[i][1]).size()  << "  " <<remove_spaces(left).size()  << "\n";

                            if( remove_spaces(tok[i][1]) == remove_spaces(left) ){
                                next.push_back(subs[i]);
                            } else {
//                                cout <<"cur = "<< subs[i] << "\n";
                                current.push_back(subs[i]);
                            }
                        }
//                        cout << " size  next = " << next.size() << endl;
                        string current_mod = "";
                        string next_mod = "";


                        for(int i = 0; i < current.size()  && next.size() != 0;i++){
                            current_mod += current[i];
                            current_mod += " ";
                            current_mod += remove_spaces(left) + "# ";
                            if(i != current.size() -1)
                                    current_mod += " | ";
                        }

                        if(next.size() == 0){
                                for(int i = 0;i < current.size();i++){
//                                        cout << current[i] << "  " <<i <<endl;
                                            current_mod += current[i];
                                            if(i != current.size()-1){
                                                current_mod+="|";
                                            }
                                }
                        }
                        prod.push_back(std::make_pair(left,current_mod));
                        for(int i = 0; i < next.size();i++){
                                string temp = "";
                                int appear_first = 1;
                                vector <string> n = _split(next[i],' ');
                                for(int j = 0; j < n.size();j++){
                                        if(remove_spaces(n[j]) == remove_spaces(left) && appear_first == 1 ){
                                            appear_first = 0;
                                        } else {
                                            if(remove_spaces(n[j]) != "")
                                                    temp+=n[j] + " ";
                                        }

                                }
                                next[i] = temp;

                            next_mod += next[i];
                            next_mod += " ";
                            next_mod += remove_spaces(left) + "#";
                            if(i != next.size()-1)
                            next_mod += " | ";
                        }


                        if(next.size()!=0){
                            next_mod += "| \L";
                            prod.push_back(std::make_pair(remove_spaces(left)+"# ",next_mod));
                        }
        }
        while(current.size() != 0){
            current.pop_back();
        }

        while(next.size() != 0){
            next.pop_back();
        }
        }



cout << "\n";
     for(int i = 0; i < prod.size(); i++){
//        cout << prod[i].first<< "  =>  " << prod[i].second<<endl;
    }
}





int convert_to_LL1::get_max_length(string str){
    vector <string> temp;
    vector <string> split_str = _split(str,'|');
    temp = _split(split_str[0],' ');
    temp = remove_empty_element(temp);
    int t = temp.size();
    int maximmum = t;
    for(int i = 1; i < split_str.size() ; i++){
            temp = _split(split_str[i],' ');
            temp = remove_empty_element(temp);
            int t = temp.size();
//            cout << t << endl;
        if(t > maximmum)
            maximmum = t;
    }
    return maximmum;
}

vector < pair < int,vector < int > > > convert_to_LL1::get_in(int maximum, vector <string> r){
    int test[r.size()];
    int gege = 0;
    //int out = 0;
    for(int i = 0; i < r.size();i++){
        test[i] = 0;
    }
    vector < pair < int,vector < int > > > data;
    for(int i = 1 ; i <= maximum;i++){
//            cout << "max = " << maximum << endl;
            int check = 0;
            for(int j = 0;j < r.size();j++){
                vector <int> number_factored;
                number_factored.push_back(j);
                vector <string> split_spaces = _split(r[j],' ');
                split_spaces = remove_empty_element(split_spaces);

                if(test[j] == 0){
                for(int k = 0; k < r.size();k++){
                        if(k != j && test[k] == 0){
                                test[j] = 1;
                                vector <string> split_spaces_next = _split(r[k],' ');
                                split_spaces_next = remove_empty_element(split_spaces_next);
                                int test_size = 0;
                                for(int m = 0; m < i &&m < split_spaces_next.size() && m < split_spaces.size();m++){
                                    if(split_spaces[m] == split_spaces_next[m]){
                                        test_size++;
                                        if(m == 0){
                                            gege = 1;
                                        }
                                    }else {
        //                                out = 1;
                                    }
                                }
                                if(test_size == i ){
//                                                                        cout << k <<endl;
                                    number_factored.push_back(k);
                                    test[k] = 1;
                                    check = 1;
                                } else {
                                    if(check == 0)
                                        test[j] = 0;
                                }
                                test_size = 0;

                        }
                }
                    if(gege == 1){
                        data.push_back(std::make_pair(i,number_factored));
                        gege = 0;
                    }
                    //gege = 0;
                    //out =0;
                }
            }
    }
//    cout <<"end"<<endl;
    return data;
}


vector < pair < string ,string > > convert_to_LL1::left_factor(string left ,vector <string> temp, vector < pair < int,vector < int > > > data){
    /// temp ->  a      a c      a b      a b c      c d      c d f
    /// data ->  1      0  1  2  3
    /// data ->  1      4  5
    vector < pair < string ,string > > pro;
    int valid[temp.size()];
    for(int i = 0;i < temp.size();i++){
        valid[i] = 0;
    }
    vector <string> part;
    string actual = "";
    string change_var = left + "'";
    string sep = "'";
    string right = "";

    for(int i = 0;i < data.size();i++){
        int number_of_common = data[i].first;
        vector <int> index_of_having_common = data[i].second;
        part = _split(temp[index_of_having_common[0]],' ');
        part = remove_empty_element(part);
        for(int j = 0;j < number_of_common;j++){
            actual += part[j];
            actual += " ";
        }
        actual += change_var;
        for(int k = 0; k < index_of_having_common.size();k++){
                int index = index_of_having_common[k];
                valid[index] = 1;
            part = _split(temp[index_of_having_common[k]],' ');
            part = remove_empty_element(part);
//                cout << "bbbbbbbbbbbbbbbbbbb = "<<temp[index] <<"   "<<number_of_common<<endl;
            if(part.size() == number_of_common){
//                cout << "bbbbbbbbbbbbbbbbbbb = "<<temp[index] <<endl;
                right += "L";
                right += " |";
            }else {
                vector <string> tet = _split(temp[index],' ');
                tet = remove_empty_element(tet);
                int ch = 0;
                for(int u = number_of_common; u < tet.size();u++){
                    right += tet[u];
                    right += " ";
                    ch = 1;
                }
            if(k != index_of_having_common.size() - 1 && ch == 0)
                right += " | ";
                ch = 1;
            }
        }

         pro.push_back(std::make_pair(change_var,right));
//        cout << change_var << "   " <<right << endl;
        change_var += sep;
        right = "";
        if(i != data.size() - 1)
                actual += " | ";
    }
    for(int i = 0;i < temp.size();i++){
        if(valid[i] == 0){
//            cout << i <<" here" <<endl;
            actual += " | ";
            actual += temp[i];
        }
    }

    pro.push_back(std::make_pair(left,actual));
//cout << actual <<endl;
return pro;
}

