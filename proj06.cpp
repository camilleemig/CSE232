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
	long e_count = 0;
	long i_count = 0;
	long zero_count = 0;
	long one_count = 0;
	long rows = image.size();
	long columns = image.at(0).size();
	for(int i = 0; i < rows -1; i++){
		for(int j = 0; j < columns - 1; j++){
			zero_count = 0;
			one_count = 0;
			
			//Count the number of 1's and 0's
			if(image[i][j] == 0){
				zero_count += 1;
			}
			else{
				one_count += 1;
			}
			if(image[i+1][j] == 0){
				zero_count += 1;
			}
			else{
				one_count += 1;
			}
			if(image[i][j+1] == 0){
				zero_count += 1;
			}
			else{
				one_count += 1;
			}
			if(image[i+1][j+1] == 0){
				zero_count += 1;
			}
			else{
				one_count += 1;
			}
			
			//Check if it is a corner
			if(zero_count == 3){
				i_count += 1;
			}
			else if(one_count == 3){
				e_count += 1;
			}
		}

		
    }
    return (int)((e_count - i_count)/4);
}
