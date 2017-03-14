/*************************************
 * Project 7
 * Camille Emig
 * Section 003
 * 03-14-2017
 *
 * Function to clean a string
 * Function to generate a vector of n_grams
 * Function to print a map
 * Function to print a vector
 * Function to create a map from a line
 * Functions to compare map elements for sorting
 * Function to return a sorted vector of a certain length
 * Function to calculate ochiai
 **************************************/

#include<string>
using std::string;
#include<map>
using std::map;
#include<utility>
using std::pair;
#include<vector>
using std::vector;
#include <sstream>
using std::stringstream;
#include <cctype>
using std::isalpha; using std::tolower;
#include <iostream>
using std::cout; using std::skipws; using std::noskipws;
#include<algorithm>
using std::sort; using std::set_intersection;
#include <cmath>
using std::sqrt;


string clean_string(string w){
	stringstream ss;
	string s;
	for(auto ch : w){ //Check each character in the string
		if(isalpha(ch)){ //If the character is alphabetic
			ss << (char)tolower(ch); //add the lower case of the character
		}
	}
	ss >> s; //output the new string to a variable to return
	return s;
}

vector<string> generate_ngrams(string w, size_t n){
	vector<string> vec;
	if(w.size() != 0){ //Makes sure there is at least one character
		for(int i = 0; i < (w.size()-n + 1); i ++){ //w.size()-n + 1 makes it that it stops at the correct char
			vec.push_back(w.substr(i, n)); //adds the n_gram of length n to the vector
		}
	}
	return vec;
}

string map_to_string(map<string,long>  &m){
	stringstream ss;
	string s;
	for(auto elem : m){
    	ss << elem.first << ":" << elem.second << ", "; //add each map pair to the string
    }
	s = ss.str(); //move the new string to a variable
	s = s.substr(0, s.size() - 2); //Delete the last space and comma
	return s;
}

string vector_to_string(vector<pair<string,long>> &v){
	stringstream ss;
	string s;
	for(auto elem : v){
    	ss << elem.first << ":" << elem.second << ", ";  //add each vector pair to the string
    }
	s = ss.str(); //move the string to a new variable
	s = s.substr(0, s.size() - 2); //Delete the last space and comma
	return s;
}

void process_line(map<string, long>& m, string line, size_t n){
	line = clean_string(line); //strips the line
	vector<string> vec = generate_ngrams(line, n); //Generates a vector of the n_grams
    for(string s : vec){
		//Count how many occurances of each element there are
        if(m.find(s) != m.end()){ //Use m[s] += 1?
            m.at(s) += 1;
        }
        else{
            m.insert(std::pair<string,long>(s,1));
        }
    }
}

bool pair_string_lessthan(const pair<string, long> &p1, const pair<string, long> &p2){
	return p1.first < p2.first; //Comparing the strings
}

bool pair_frequency_greaterthan(const pair<string, long> &p1, const pair<string, long> &p2){
	if(p1.second != p2.second){ //If the number of items isn't the same
		return p1.second > p2.second;
	}
	else{ //Otherwise sort by the string of each
		return p1.first < p2.first;
	}
}

vector<pair<string, long>> top_n(map<string, long> &m, int num){
	vector<pair<string, long> > v;
    copy(m.begin(), m.end(), back_inserter(v)); //Copy each element in the map to the vector
    sort(v.begin(), v.end(), pair_frequency_greaterthan); //Sort the vector
    vector<pair<string, long>> return_v(v.begin(), v.begin() + num); //new vector of top num items
    return return_v; //return the shortened vector
}

double ochiai(map<string, long> &m1, map<string, long> &m2){
	//THIS DOESN'T WORK
	vector<pair<string, long> > v(m1.size()); 
	vector<pair<string, long> >::iterator it;
	top_n(m1, m1.size()); //sort m1
	top_n(m2,m2.size()); //sort m2
	it = set_intersection(m1.begin(), m1.end(), m2.begin(), m2.end(), v.begin());
	v.resize(it-v.begin());

	cout << "The intersection has " << (v.size()) << " elements\n";
	return ((v.size())/(sqrt(m1.size() * m2.size()))); //N(A intersection B)/sqrt(A * B)
}

double ochiai2(map<string, long> &m1, map<string, long> &m2, int num){
	return 0.0;
}
