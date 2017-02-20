#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<string>
using std::string; using std::stoi; using std::to_string;
#include<sstream>
using std::ostringstream; using std::istringstream;
#include<iterator>
using std::distance; using std::back_inserter;
#include<algorithm>
using std::transform;
#include<cctype>
// whatever headers you need

string lower_and_strip(string s){
	string return_string = "";
	for(char c : s){

		if((c<='Z') && (c >='A')){
			return_string += c-('Z'-'z');
		}
		// || (c == ' ')
		else if ((c<='z' && c >='a')){
			return_string += c;
		}
	}
	return return_string;
}
int return_encoded_char(string key, string::size_type &start, char C){
	int return_val = 0;
	bool found = false;
	for(int i = start; i < key.length(); i++){
		if(key[i] == C){
			found = true;
			return_val = i - start;
			start = i;
		}
	}
	if(found == false){
		for(int i = 0; i < start; i ++){
			if(key[i] == C){
				found = true;
				return_val = i + (key.length() - start);
				start = i;
			}
		}
	}
	if(found == false){
		return_val = key.size() + 1;
		start = 0;
	}
	return return_val;
}

string encode(string message, string key){
	string::size_type start = 0;
	string return_string = "";
	message = lower_and_strip(message);
	for(char c : message){
		return_string += std::to_string(return_encoded_char(key, start, c)) + " ";
	}
	return return_string;
}

char return_decoded_char(string key,string::size_type &start, int num){
	char return_char = '_';
	if(num < key.size() + 1){
		return_char = key[(start + num)%key.size()];
		start = (start + num)%key.size();
	}
	else{
		return_char = '_';
		cout << (start + num)%key.size() << endl;
		//start = 0;
	}
	return return_char;
}

string decode(string encoded_text, string key){
	string::size_type start = 0;
	string return_string = "";
	string c;
	int integer_c;
	for(int i = 0; i < encoded_text.size(); ++i){
		if(encoded_text[i + 1] == ' '){
			c = encoded_text[i];
			++i;
			integer_c = stoi(c);
			return_string += return_decoded_char(key, start, integer_c);
		}
		else{
			//Adds together the two integers to make one int to decode
			integer_c = stoi(string(1,encoded_text[i]))*10 + stoi(string(1,encoded_text[i+1]));
			i += 2;
			return_string += return_decoded_char(key, start, integer_c);
		}
	}
	return return_string;
}


int main (){
  cout << boolalpha;

  int test_case;
  cin >> test_case;

  switch (test_case){

  case 1 : {
    string line;
    cin.ignore(20, '\n');
    getline(cin, line);
    cout << lower_and_strip(line) << endl;
    break;
  } // of case 1

  case 2 : {
    string key;
    char C;
    int num;
    string::size_type start;
    cin.ignore(20, '\n');
    getline(cin, key);
    cin >> C;
    cin >> start;
    num = return_encoded_char (key, start, C); 
    cout << num << " " << start << endl;
    break;
  } // of case 2

  case 3 : {
    string key, line;
    string::size_type start=0;
    cin.ignore(20, '\n');
    getline(cin, key);
    getline(cin, line);
    cout << encode(line, key) << endl;
    break;
  } // of case 3   

  case 4 : {
    int num;    
    string key;
    char C;
    string::size_type start;
    cin.ignore(20, '\n');
    getline(cin, key);
    cin >> num;
    cin >> start;
    C = return_decoded_char (key, start, num);
    cout << C << " "<<start << endl;
    break;
  } // of case 4

  case 5 : {
    string key, line;
    string::size_type start=0;    
    cin.ignore(20, '\n');
    getline(cin, key);
    getline(cin, line);
    cout << decode(line, key) << endl;
    break;
  } // of case 5
    
  } // of switch

} // of main
