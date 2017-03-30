/**********
* Camille Emig
* Section 003
* 3-30-17
* Finite State Machine
***********/
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
    //Initializer
    start_ = strt;
    finish_ = stp;
    state_ = strt;
}
FSA::FSA(ifstream& fs){
    //Gets the start and stop points
    string strt, stp, inpt;
    fs >> strt >> stp;
    start_ = strt;
    finish_ = stp;
    state_ = strt;
    //Gets all of the transitions in the file
    while (fs >> strt >> inpt >> stp){
        table_[strt][inpt] = stp;
    }
}
bool FSA::exists_state(string s){
    //Checks if the key is in the table
    if (table_.find(s) == table_.end()){
        return false;
    }
    return true;
}
void FSA::add_state(string s){
    //If the state is not in the table, add it
    if (!exists_state(s)){
        table_[s];
    }
    //Otherwise throw a domain error
    else{
        string error_str = s + " already exists";
        throw std::domain_error(error_str);
    }
}
void FSA::add_transition(string s1, string s2, string s3){
    //If the key is in the table, add the transition
    if (table_.find(s1) != table_.end()){
        table_[s1][s2] = s3;
    }
    //Otherwise throw a domain error
    else{
        string error_str = s1 + " doesn't exist";
        throw std::domain_error(error_str);
    }
}

string FSA::transitions_to_string(string s){
    ostringstream os;
    string return_s;
    //If the key is in the table, add it to the string
    if (table_.find(s) != table_.end()){
        os << s << ":";
        for (pair<string, string> p: table_[s]){
            os <<" on " << p.first << " -> " << p.second << ",";
        }
        return_s = os.str();
        return_s = return_s.substr(0, return_s.size()-1);
        return return_s;

    }
    //Otherwise throw a domain error
    else{
        string error_str = s+ " doesn't exist";
        throw std::domain_error(error_str);
    }
}
string FSA::next(string s1,string s2){
    //If the string is in the table
    if (table_.find(s1) != table_.end()){
        //If the transition is there
        if (table_[s1].find(s2) != table_[s1].end()){
          //Returns the next place to go
          return table_[s1][s2];
        }
        //Otherwise throw a domain error
        else{
          string error_str = s1 + " has no transition on input " + s2;
          throw std::domain_error(error_str);
        }
    }
    //Otherwise throws a domain error
    else{
        string error_str = s1 + " doesn't exist";
        throw std::domain_error(error_str);
    }

}
bool FSA::run(string s){
    //For each transition in the string
    for (char c : s){
        state_ = next(state_, string(1,c)); //Get the next state
        cout << "Got to:" << state_ << " on a " << c << endl; //Outputs the path
    }
    return (state_ == finish_); //Returns if it made it to the finish
}

ostream& operator<<(ostream& os, FSA& f){
    //Prints the current state
    os << "Start:" << f.start_ << ", Finish:" << f.finish_ << ", Present:" << f.state_ << endl;
    //Prints the table
    for (pair<string, map<string, string>> p: f.table_){
        os << f.transitions_to_string(p.first) << endl;
    }
    return os;
}
