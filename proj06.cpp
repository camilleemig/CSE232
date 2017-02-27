#include<vector>
using std::vector;
#include<iostream>
using std::cin; using std::cout; using std::endl;
#include<string>
using std::string; using std::stol; using std::to_string;

vector<vector<int>> readImage(int columns, int rows){
	vector<int> rows_vec(columns, 0);
	vector<vector<int>> image(rows, rows_vec);
	string str_num = "";
	long long_num = 0;
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
		    cin >> str_num; //Get the next number into c, up to a space
		    long_num = stol(str_num); //Convert c to an integer
		    image[i][j] = long_num;
		}
    }
    return image;
}

void printImage(vector<vector<int>> image){
	for(vector<int> vec : image){
		for(int num : vec){
			cout<<num;
		}
		cout << endl;
	}
}

int countHoles(vector<vector<int>> image){
	return 0;
}
