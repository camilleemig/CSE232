proj04.cpp submitted by emigcami on 2017-02-06 09:03:14 from 35.9.20.83

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
    long prime_count = 0;
    for(long i = 2; i < n; i++){
        if(n%i == 0){
            if(is_prime(i)){
                if(i*i == n){
                    prime_count += 1;
                }
                prime_count += 1;
            }
            else{
                return false;
            }
        }
        if(prime_count > 2){
            break;
        }
    }
    if(prime_count == 2){
        return true;
    }
    else{
        return false;
    }
}

long reverse_num(long n){
    string string_num = to_string(n);
    std::reverse(string_num.begin(), string_num.end());
    long reversed_num = stol(string_num);
    return reversed_num;
}

bool is_palindrome(long n){
    long reversed_num;
    reversed_num = reverse_num(n);
    return reversed_num == n;

}

bool is_emirp(long n){
    long reversed_num;
    reversed_num = reverse_num(n);
    return (!is_palindrome(n)) && (is_prime(n)) && (is_prime(reversed_num));
}

bool is_emirpimes(long n){
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
    
