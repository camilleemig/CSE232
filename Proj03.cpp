#include<iostream>
#include<math.h>
using std::cout; using std::cin; using std::endl;
using std::boolalpha;
// add any other includes you like.

// functions go here

bool is_prime(long n){
    for(long i = 2; i < n; i++){
        if (n%i == 0)
            return false;
    }
    return true;
}

bool is_powerful(long n){
    for(long i = 2; i < n; i++){
        if(is_prime(i) && (n%i == 0)){
            if (n%(i*i) != 0)
                return false;
        }
    }
    return true;
}

bool is_perfect_power(long n){
    for(long m = 2; m < sqrt(n) + 1; m++){
        for(long k = 2; k < n; k++){
            if (pow(m,k) == n)
                return true;
            else if(pow(m,k) > n)
                break;
        }
    }
    return false;
}

bool is_achilles(long n){
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
    
