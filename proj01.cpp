/*************************************
* Project 1
* Camille Emig
* Section 003
* 01-16-2017
*
* Calculates emission from miles per
*	gallon and miles driven per year
**************************************/

#include<iostream>
#include<iomanip>
using std::cout;
using std::cin;
using std::endl;
using std::fixed;

int main(){
	//Initialize all variables
	double mpg = 0;
	double mipyear = 0;
	double galperyear = 0;
	double carbonperyear = 0;
	double emission = 0;
	double upone = 0;
	double upfive = 0;
	
	//Gets input from user
	cin >> mpg >> mipyear;
	
	//Calculates emission for original numbers
	galperyear = mipyear/mpg;
	carbonperyear = galperyear*19.6;
	emission = carbonperyear*100/98.65;
	
	//Calculates emission for when mileage is 1 greater
	mpg += 1;
	galperyear = mipyear/mpg;
	carbonperyear = galperyear*19.6;
	//Calculates difference between original emission and up 1 emission
	upone = emission - carbonperyear*100/98.65;
	
	//Calculates emission for when mileage is 5 greater
	mpg += 4;
	galperyear = mipyear/mpg;
	carbonperyear = galperyear*19.6;
	//Calculates difference between original emission and up 5 emission
	upfive = emission - carbonperyear*100/98.65;
	
	//Outputs all three emissions, separated by spaces and using two decimals
	cout << fixed << std::setprecision(2) << emission << " " 
		 << upone << " " << upfive << endl;
}
