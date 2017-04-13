#ifndef RANDOM_SUPPORT
#define RANDOM_SUPPORT

#include<deque>
using std::deque;
#include<random>
using std::mt19937_64;
#include<string>
using std::string;

long random_long_in_range(int lo, int hi, mt19937_64 &reng);
deque<deque<long>> gen_passengers(long floor_max, long passenger_max, mt19937_64 &reng);
string print_2d_deque (const deque<deque<long>> &d);

#endif

