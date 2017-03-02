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
#include<iterator>
using std::ostream_iterator;
#include <algorithm>
using std::copy;


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
        copy(vec.begin(), vec.end(), ostream_iterator<int>(cout,""));
        cout << endl;
    }
}

int countHoles(vector<vector<int>> image){
    long e_count = 0; //Counts the total amount of external corners
    long i_count = 0; //Counts the total amount of internal corners
    long count = 0; //Counts the amount of zeros in a two-by-two area
    long rows = image.size(); //Figures out the amount of rows in the image
    long columns = image.at(0).size(); //Figures out the amount of columns in the image
    //Loops through each row
    for(int i = 0; i < rows -1; i++){
        //Loops through each column
        for(int j = 0; j < columns - 1; j++){
            count = 0;  //Resets the counts.
            //Zeros are 2s, Ones are Ones
            //Count the number of 1's and 0's
            count += (image[i][j] == 0) ? 2 : 1;
            count += (image[i+1][j] == 0) ? 2 : 1;
            count += (image[i][j+1] == 0) ? 2 : 1;
            count += (image[i+1][j+1] == 0) ? 2 : 1;

            //Check if it is a corner
            if(count == 7){ //Internal corner
                i_count += 1;
            }
            else if(count == 5){ //External corner
                e_count += 1;
            }
        }
    }
    return (int)((e_count - i_count)/4);
}
