/*************************************
* Project 5
* Camille Emig
* Section 003
* 02-20-2017
*
* Switch function decides which function to call
* 	1) Convert to lower case, remove non-letters
*	2) Encode one character
*	3) Encode a string
*	4) Decode a character
*	5) Decode a string
**************************************/
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


string lower_and_strip(string s){
	string return_string = "";
	for(char c : s){
		if((c<='Z') && (c >='A')){ //If it is an upper case letter
			return_string += c-('Z'-'z'); //add the lower case letter
		}
		else if ((c<='z' && c >='a')){ //add the lower case letters
			return_string += c;
		}
	}
	return return_string; //Returns lower case stripped string
}
int return_encoded_char(string key, string::size_type &start, char C){
	int return_val = 0;
	string::size_type new_pos = 0;
	new_pos = key.find(C, start); //Tries to find the character in the key
	if(new_pos != string::npos){ //If the character was found
		return_val = new_pos - start;
		start = new_pos;
	}
	else{ //Character was not found
		new_pos = key.find(C); //Try to find it in the beginning of the string
		if(new_pos != string::npos){ //If it was found
			return_val = new_pos + (key.length() - start);
			start = new_pos;
		}
		else{ //If it wasn't found, it is not in key
			return_val = key.size() + 1;
			start = 0;
		}
	}
	return return_val;
}

string encode(string message, string key){
	string::size_type start = 0;
	string return_string = "";
	message = lower_and_strip(message); //strips and converts message to lower case
	for(char c : message){
		//Convert message one character at a time
		return_string += std::to_string(return_encoded_char(key, start, c)) + " ";
	}
	return return_string;
}

char return_decoded_char(string key,string::size_type &start, int num){
	char return_char = '_';
	if(num < key.size() + 1){ //
		return_char = key[(start + num)%key.size()];
		start = (start + num)%key.size();
	}
	else{
		return_char = '_';
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
  
  
