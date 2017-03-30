#include<iostream>
using std::ostream;
using std::boolalpha;
#include<sstream>
using std::ostringstream;
#include<fstream>
using std::ifstream;
#include<map>
using std::map;
#include<string>
using std::string;
#include<iostream>
using std::cout; using std::endl;
#include<utility>
using std::pair;
#include"functions.h"

FSA::FSA(string strt, string stp){
    start_ = strt;
    finish_ = stp;
    state_ = strt;
}
FSA::FSA(ifstream& fs){
    string strt, stp, inpt;
    fs >> strt >> stp;
    start_ = strt;
    finish_ = stp;
    state_ = strt;
    while (fs >> strt >> inpt >> stp){
        table_[strt][inpt] = stp;
    }
}
bool FSA::exists_state(string s){
    if (table_.find(s) == table_.end()){
        return false;
    }
    return true;
}
void FSA::add_state(string s){
    if (!exists_state(s)){
        table_[s];
    }
    else{
        string error_str = s + " already exists";
        throw std::domain_error(error_str);
    }
}
void FSA::add_transition(string s1, string s2, string s3){
    if (table_.find(s1) != table_.end()){
        table_[s1][s2] = s3;
    }
    else{
        string error_str = s1 + " doesn't exist";
        throw std::domain_error(error_str);
    }
}

string FSA::transitions_to_string(string s){
    ostringstream os;
    string return_s;
    if (table_.find(s) != table_.end()){
        os << s << ":";
        for (pair<string, string> p: table_[s]){
            os <<" on " << p.first << " -> " << p.second << ",";
        }
        return_s = os.str();
        return_s = return_s.substr(0, return_s.size()-1);
        return return_s;

    }
    else{
        string error_str = s+ " doesn't exist";
        throw std::domain_error(error_str);
    }
}
string FSA::next(string s1,string s2){
    if (table_.find(s1) != table_.end()){
        if (table_[s1].find(s2) != table_[s1].end()){
          return table_[s1][s2];
        }
        else{
          string error_str = s1 + " has no transition on input " + s2;
          throw std::domain_error(error_str);
        }
    }
    else{
        string error_str = s1 + " doesn't exist";
        throw std::domain_error(error_str);
    }

}
bool FSA::run(string s){
    for (char c : s){
        state_ = next(state_, string(1,c));
        cout << "Got to:" << state_ << " on a " << c << endl;

    }
    return (state_ == finish_);
}

ostream& operator<<(ostream& os, FSA& f){
    os << "Start:" << f.start_ << ", Finish:" << f.finish_ << ", Present:" << f.state_ << endl;
    for (pair<string, map<string, string>> p: f.table_){
        os << f.transitions_to_string(p.first) << endl;
    }
    return os;
}
