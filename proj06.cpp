/*************************************
* Project 6
* Camille Emig
* Section 003
* 02-28-2017
*
* Function to read in image from file
* Function to print out image
* Function to count the number of holes
**************************************/
#include<vector>
using std::vector;
#include<iostream>
using std::cin; using std::cout; using std::endl;
#include<string>
using std::string; using std::stol; using std::to_string;

vector<vector<int>> readImage(int columns, int rows){
	vector<int> rows_vec(columns, 0); //Vector to use as the row for the image
	vector<vector<int>> image(rows, rows_vec); //Creates a template of the image
	//Used for converting from cin to a long
	string str_num = "";
	long long_num = 0;
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
		    cin >> str_num; //Get the next number into c, up to a space
		    long_num = stol(str_num); //Convert c to an integer
		    image[i][j] = long_num; //Adds the number into the image
		}
	}
	return image;
}

void printImage(vector<vector<int>> image){
	//Loops through each vector in the image
	for(vector<int> vec : image){
		//Loops through each number in the vector
		for(int num : vec){
			//Prints the number
			cout<<num;
		}
		//Prints the new line to start a new row
		cout << endl;
	}
}

int countHoles(vector<vector<int>> image){
	long e_count = 0; //Counts the total amount of external corners
	long i_count = 0; //Counts the total amount of internal corners
	long zero_count = 0; //Counts the amount of zeros in a two-by-two area
	long one_count = 0; //Counts the amount of ones in a two-by-two area
	long rows = image.size(); //Figures out the amount of rows in the image
	long columns = image.at(0).size(); //Figures out the amount of columns in the image
	//Loops through each row
	for(int i = 0; i < rows -1; i++){
		//Loops through each column
		for(int j = 0; j < columns - 1; j++){
			//Resets the counts.
			zero_count = 0;
			one_count = 0;
			
			//Count the number of 1's and 0's
			if(image[i][j] == 0){ //Start current position
				zero_count += 1;
			}
			else{
				one_count += 1;
			}			//End current position
			if(image[i+1][j] == 0){ //Start one to the right of current position
				zero_count += 1;
			}
			else{
				one_count += 1;
			}			//End one to the right of current position
			if(image[i][j+1] == 0){ //Start one below current position
				zero_count += 1;
			}
			else{
				one_count += 1;
			}			//End one below current position
			if(image[i+1][j+1] == 0){ //Start one below and to the right of current position
				zero_count += 1;
			}
			else{
				one_count += 1;
			}			//End one below and to the right of current position
			
			//Check if it is a corner
			if(zero_count == 3){ //Internal corner
				i_count += 1;
			}
			else if(one_count == 3){ //External corner
				e_count += 1;
			}
		}

		
    }
    return (int)((e_count - i_count)/4);
}
