#include<iostream>
using std::cout; using std::cin; using std::endl;
using std::boolalpha;
#include<cmath>
using std::sqrt; using std::ceil; using std::round;
#include<string>
using std::string; using std::stol; using std::to_string;
#include<algorithm> //using reverse string function

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

bool is_semiprime(long n){
    //Checks to see how many prime factors the number has
    long prime_count = 0;
    //Loops through every number from 2 to n
    for(long i = 2; i < n; i++){
        if(n%i == 0){ //Check to see if the number is divisible
            if(is_prime(i)){ //Check to see if the number is prime
                if(i*i == n){   //Count a factor twice if it is a square root of the number
                    prime_count += 1;
                }
                prime_count += 1;
            }
            else{ //Returns false if a number is divisible but not a prime
                return false;
            }
        } //Stop looking for primes if there are over 2
        if(prime_count > 2){
            break;
        }
    }
    if(prime_count == 2){ //If there were two prime factors, return true
        return true;
    }
    else{ //Returns false if there were not two prime factors
        return false;
    }
}

long reverse_num(long n){
    //Reverses a long
    string string_num = to_string(n); //Converts the number to a string
    std::reverse(string_num.begin(), string_num.end()); //Uses reverse function to reverse the string
    long reversed_num = stol(string_num); //Converts the reversed number back to a long
    return reversed_num; //Returns the reversed long
}

bool is_palindrome(long n){
    //Checks to see if the number is a palindrome
    long reversed_num;
    reversed_num = reverse_num(n); //Stores the reveresed number
    return reversed_num == n; //Returns true or false based on equality of n and reversed_num

}

bool is_emirp(long n){
    //Checks to see if the number is not a palindrome, is prime, and the reversed num is prime
    long reversed_num;
    reversed_num = reverse_num(n);
    return (!is_palindrome(n)) && (is_prime(n)) && (is_prime(reversed_num));
}

bool is_emirpimes(long n){
    //Checks to see if the number is not a palindrome, is semiprime, and the reversed num is semiprime
    long reversed_num;
    reversed_num = reverse_num(n);
    return (!is_palindrome(n)) && (is_semiprime(n)) && (is_semiprime(reversed_num));
}


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
      cout << num << ":" << reverse_num(num) << endl;
    break;
  } // of case 2

  case 3 : {
    long num;
    while (cin >> num)
      cout << num << ":" << is_palindrome(num) << endl;
    break;
  } // of case 3   

  case 4 : {
    long num;
    while (cin >> num)
      cout << num << ":" << is_emirp(num) << endl;
    break;
  } // of case 4

  case 5 : {
    long num;  
    while (cin >> num)
      cout << num << ":" << is_semiprime(num) << endl;
    break;
  } // of case 5

  case 6 : {
    long num;
    while (cin >> num)
      cout << num << ":" << is_emirpimes(num) << endl;
    break;
  } // of case 6    
    
  } // of switch
} // of main
    
