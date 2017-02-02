/*************************************
* Project 3
* Camille Emig
* Section 003
* 02-02-2017
*
* Switch function decides which function to call
*   1) Check if number is prime
*   2) Check if number is powerful
*   3) Check if number is perfect power
*   4) Check if number is achilles
**************************************/


#include<iostream>
#include<math.h> //Using pow() from this
using std::cout; using std::cin; using std::endl;
using std::boolalpha;

bool is_prime(long n){
    //Checks every number between 2 and n
    for(long i = 2; i < n; i++){
        //If n is divisible by a number other than 1, it is not prime.
        if (n%i == 0)
            return false;
    }
    //If it didn't return false, it is prime, so returns true
    return true;
}

bool is_powerful(long n){
    //Checks every number between 2 and n
    for(long i = 2; i < n; i++){
        //Checks to see if i is a prime number, and if n is divisible by i
        if(is_prime(i) && (n%i == 0)){
            //If n is not divisible by i squared, return false
            if (n%(i*i) != 0)
                return false;
        }
    }
    //Must be powerful number, return true
    return true;
}

bool is_perfect_power(long n){
    //Loops through every number from 2 to the square root of n
    //Can stop at sqrt n, because then m**2 = n, and m**(>2) > n
    for(long m = 2; m < sqrt(n) + 1; m++){
        //Loops through every possible number
        for(long k = 2; k < n; k++){
            if (pow(m,k) == n)
                //Returns true if there is a number where m**k = n
                return true;
            else if(pow(m,k) > n)
                //moves on to the next m if the number created is greater than n
                break;
        }
    }
    //Returns false if there is not a power k of m (m**k) that equals n
    return false;
}

bool is_achilles(long n){
    //Checks to see if number is power and is not a perfect power
    if(is_powerful(n) && (!is_perfect_power(n)))
        return true;
    else
        return false;
}

// main is below. You cannot modify main
int main (){
  cout << boolalpha;

  int test_case;
  cin >> test_case;

  switch (test_case){

  case 1 : {
    long num;
    while (cin >> num)
      cout << num << ":" << is_prime(num) << endl;
    break;
  } // of case 1

  case 2 : {
    long num;
    while (cin >> num)
      cout << num << ":" << is_powerful(num) << endl;
    break;
  } // of case 2

  case 3 : {
    long num;
    while (cin >> num)
      cout << num << ":" << is_perfect_power(num) << endl;
    break;
  } // of case 3   

  case 4 : {
    long num;
    while (cin >> num)
      cout << num << ":" << is_achilles(num) << endl;
    break;
  } // of case 4
    
  } // of switch
} // of main
    
