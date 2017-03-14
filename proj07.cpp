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
	for(auto ch : w){
		if(isalpha(ch)){
			ss << (char)tolower(ch);
		}
	}
	ss >> s;
	return s;
}

vector<string> generate_ngrams(string w, size_t n){
	vector<string> vec;
	if(w.size() != 0){
		for(int i = 0; i < (w.size()-n + 1); i ++){
			vec.push_back(w.substr(i, n));
		}
	}
	return vec;
}

string map_to_string(map<string,long>  &m){
	stringstream ss;
	string s;
	for(auto elem : m){
    	ss << elem.first << ":" << elem.second << ", ";
    }
	s = ss.str();
	s = s.substr(0, s.size() - 2);
	return s;
}

string vector_to_string(vector<pair<string,long>> &v){
	stringstream ss;
	string s;
	for(auto elem : v){
    	ss << elem.first << ":" << elem.second << ", ";
    }
	s = ss.str();
	s = s.substr(0, s.size() - 2);
	return s;
}

void process_line(map<string, long>& m, string line, size_t n){
	line = clean_string(line);
	vector<string> vec = generate_ngrams(line, n);
    for(string s : vec){
        if(m.find(s) != m.end()){
            m.at(s) += 1;
        }
        else{
            m.insert(std::pair<string,long>(s,1));
        }
    }
}

bool pair_string_lessthan(const pair<string, long> &p1, const pair<string, long> &p2){
	return p1.first < p2.first;
}

bool pair_frequency_greaterthan(const pair<string, long> &p1, const pair<string, long> &p2){
	if(p1.second != p2.second){
		return p1.second > p2.second;
	}
	else{
		return p1.first < p2.first;
	}
}

vector<pair<string, long>> top_n(map<string, long> &m, int num){
	vector<pair<string, long> > v;
    copy(m.begin(), m.end(), back_inserter(v));
    sort(v.begin(), v.end(), pair_frequency_greaterthan);
    vector<pair<string, long>> return_v(v.begin(), v.begin() + num);
    return return_v;
}

double ochiai(map<string, long> &m1, map<string, long> &m2){
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
