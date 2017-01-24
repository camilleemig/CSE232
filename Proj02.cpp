/*************************************
* Project 2
* Camille Emig
* Section 003
* 01-22-2017
*
* Calculates emission from miles per
*    gallon and miles driven per year
**************************************/

#include<iostream>
#include<list>
using std::cin; //Get input from user
using std::cout; //Send output to conso;e
using std::endl; //New line character


long gcd(long lowerLim, long upperLim){
	//Calculates the greatest common demonimator of two numbers
	int i;
	int gcd = 1;
	//Loop through every number from 1 to the lower limit
	for(i = 1; i < lowerLim + 1; i++){
		//If both numbers are divisible by i, make it the GCD
		if(lowerLim%i == 0 && upperLim%i == 0){
			gcd = i;
		}
	}
	//Returns the greatest common demonimator
	return gcd;
}

long phi(long totativeUpper){
	long lower;
	long totative = 0;
	long i;
	long gcd = 0;
	//Loops through every number from 1 to the number given by the user
	for(lower = 1; lower < totativeUpper; lower++){
		//Checks to see if the number is a relative prime
		for(i = 1; i < lower + 1; i++){
			if(lower%i == 0 && totativeUpper%i == 0){
				gcd = i;
			}
		}
		//if the number is a relative prime, output it and increase the counter
		if(gcd == 1){
			cout << lower << " ";
			totative += 1;
		}
	}
	//
	return totative;
}

int main(){
	long lowerLim; //lower number for GCD
	long upperLim; //upper number for GCD
	long totativeUpper; //number to go up to for the totative
	long totative = 0; //totative count of relative primes
	long gcdNum = 0; //greatest common demonimator of lowerLim and upperLim
	
	//Get numbers from user
	cin >> lowerLim >> upperLim >> totativeUpper;
	
	//Check to make sure all are valid
	if(lowerLim < 1 || upperLim < 1 || totativeUpper < 1){
		cout << "Error" << endl;
	}
	//Runs the program if all the numbers are valid
	else{
		//Checks to make sure the lower variable is actually smaller than upper
		if (upperLim < lowerLim){
			long switchVar = lowerLim;
			lowerLim = upperLim;
			upperLim = switchVar;
		}
		//Finds the greatest common demonimator and output it
		gcdNum = gcd(lowerLim, upperLim);
		cout << gcdNum <<endl;
		
		//Find the relative prime numbers and count them, output the count
		totative = phi(totativeUpper);
		cout << endl << totative << endl;
	}
}

