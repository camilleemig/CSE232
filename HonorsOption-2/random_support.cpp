#include<iostream>
using std::cout;
#include<iomanip>
using std::setw;
#include<deque>
using std::deque;
#include<string>
using std::string;
#include<random>
using std::mt19937_64; using std::random_device;
using std::poisson_distribution; using std::uniform_int_distribution;
#include<algorithm>
using std::copy;
#include<iterator>
using std::ostream_iterator;
#include<sstream>
using std::ostringstream;

#include "random_support.h"

string print_2d_deque (const deque<deque<long>> &d){
  ostringstream oss;
  string result="";
  string temp;
  int width = 3;
  for (auto row : d){
    for (auto col : row){
      oss << setw(width) << col << ", ";
    }
    // get row as string, trim last comma, concat with result string
    // clear oss for next row
    temp = oss.str();
    temp = temp.substr(0, temp.size() - 2);
    result = result + temp + "\n";
    oss.str("");
    oss.clear();
  } // outer for, per row
  return result;
}

/*
take in a random engine BY REFERENCE
return a long in the range from lo to hi
*/
long random_long_in_range(int lo, int hi, mt19937_64 &reng){
  uniform_int_distribution<> dist(lo, hi);
  return dist(reng);
}

/* 
generate a 2D deque, where each row of the deque is a deque of a
passenger arrival event deque consisting of: arrival time, src floor, dest floor
The deque rows are GUARANTEED to come in time arrival order. That is, the first row is
is guaranteed to be the first in order of time, and each subsequent row is guaranteed
to be at the same time or later then all rows that come after
*/
deque<deque<long>> gen_passengers(long floor_max, long passenger_max, mt19937_64 &reng){
  deque<deque<long>> result;
  deque<long> passenger;
  long time = 0;
  long passenger_cnt = 0;
  long src, dst;
  poisson_distribution<> dist_p;
  
  while (passenger_cnt < passenger_max){
    time += dist_p(reng);
    src = random_long_in_range(1,floor_max, reng);
    dst = random_long_in_range(1,floor_max, reng);
    ++passenger_cnt;
    passenger={time, src, dst};
    // copy(passenger.begin(), passenger.end(), ostream_iterator<long>(cout, ", ") );
    result.push_back(passenger);
  }
  return result;
}
