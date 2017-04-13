/**************
 * Camille Emig
 * CSE232 Honors Option
 * Elevator Simulator
 ***************/
#include<iostream>
using std::cout; using std::endl; using std::cin;
#include<deque>
using std::deque;
#include<string>
using std::string;
#include<random>
using std::mt19937_64; using std::random_device;
#include<algorithm>
using std::copy;
#include<iterator>
using std::ostream_iterator;
#include <map>
using std::map;
#include <fstream>
using std::ofstream;
#include<iomanip>
using std::setw; using std::setfill;
#include "random_support.h"

void get_new_passengers(deque<deque<long>> &available_passengers, deque<deque<long>> &all_passengers, double &current_time){
    //Loop through each passenger in the load
    for(deque<long> passenger : all_passengers){
        //Loop through each passenger in the load
        if(passenger[0] <= current_time){
            //Add the passenger to the available passengers
            available_passengers.push_back(passenger);
            all_passengers.pop_front(); //Remove this passenger
        }
        else{
            //Can break because passengers are sorted by time
            break;
        }
    }
}

long decide_floor_strategy_single(deque<deque<long>> &current_passengers, deque<deque<long>> &available_passengers, long current_floor, ofstream &myfile){
    long next_floor = current_floor;
    
    //This is to decide by current passengers
    long floor_difference = 1000000000000000;
    
    //These variable are to decide by available passengers
    map<long,long> floors;
    long max_passengers = 0;
    long old_floor_difference, new_floor_difference;
    
    //Decide by current passengers
    if(current_passengers.size() != 0){
        myfile << "Moving to closest destination floor for current passengers." << endl;
    }
    for(deque<long> passenger : current_passengers){
        //This statement ensures a positive value
        if(current_floor > passenger[2]){
            //Checks to see if this floor is closest
            if((current_floor-passenger[2]) < floor_difference){
                //Stores as the closest
                floor_difference = current_floor - passenger[2];
                next_floor = passenger[2];
            }
        }
        else{
            //Checks to see which floor is closest
            if((passenger[2]-current_floor) < floor_difference){
                //Stores as the closest
                floor_difference = passenger[2] - current_floor;
                next_floor = passenger[2];
            }
        }
    }
    
    //Decide by getting new passengers
    if(floor_difference == 1000000000000000){
        myfile << "Moving to floor with most passengers waiting." << endl;
        //By most passgengers waiting
        for(deque<long> passenger : available_passengers){
            //Stores the number of passengers on a floor
            floors[passenger[1]] += 1;
        }
        //Loops through to find the floor with the most passengers
        for(auto elem : floors)
        {
            //Stores the values of the floor with the most people
            if(elem.second > max_passengers){
                next_floor = elem.first;
                max_passengers = elem.second;
            }
            else if(elem.second == max_passengers){
                //Gets the difference between the floors
                old_floor_difference = (current_floor > next_floor) ? current_floor - next_floor: next_floor - current_floor;
                new_floor_difference = (current_floor > elem.first) ? current_floor - elem.first: elem.first - current_floor;
                //Checks to see which is closest
                if(new_floor_difference <= old_floor_difference){
                    next_floor = elem.first;
                }
            }
        }
        
    }
    
    //RETURNS THE FLOOR TO GO TO
    return next_floor;
}

long decide_floor_strategy_multiple(deque<deque<long>> &current_passengers, deque<deque<long>> &available_passengers, long current_floor){
    long next_floor = current_floor;
    
    //This is to decide by current passengers
    long floor_difference = 1000000000000000;
    
    //These variable are to decide by available passengers
    map<long,long> floors;
    long max_passengers = 0;
    long old_floor_difference, new_floor_difference;
    
    //Decide by current passengers
    
    for(deque<long> passenger : current_passengers){
        if(current_floor > passenger[2]){
            if((current_floor-passenger[2]) < floor_difference){
                floor_difference = current_floor - passenger[2];
                next_floor = passenger[2];
            }
        }
        else{
            if((passenger[2]-current_floor) < floor_difference){
                floor_difference = passenger[2] - current_floor;
                next_floor = passenger[2];
            }
        }
    }
    
    //Decide by getting new passengers
    if(floor_difference == 1000000000000000){
        for(deque<long> passenger : available_passengers){
            //By most passgengers waiting,
            if(floors.find(passenger[1]) != floors.end()){
                floors.at(passenger[1]) += 1;
            }
            else{
                floors.insert(std::pair<long,long>(passenger[1],1));
            }
        }
        for(auto elem : floors)
        {
            if(elem.second > max_passengers){
                next_floor = elem.first;
                max_passengers = elem.second;
            }
            else if(elem.second == max_passengers){
                old_floor_difference = (current_floor > next_floor) ? current_floor - next_floor: next_floor - current_floor;
                new_floor_difference = (current_floor > elem.first) ? current_floor - elem.first: elem.first - current_floor;
                if(new_floor_difference <= old_floor_difference){
                    next_floor = elem.first;
                }
            }
        }
        
    }
    
    //RETURNS THE FLOOR TO GO TO
    return next_floor;
}

long decide_floor_optimal_single(deque<deque<long>> &current_passengers, deque<deque<long>> &available_passengers, long current_floor, ofstream &myfile){
    long next_floor = current_floor;
    
    //This is to decide by current passengers
    long floor_difference = 1000000000000000;
    
    //These variable are to decide by available passengers
    map<long,long> floors;
    
    //Decide by current passengers
    if(current_passengers.size() != 0){
        myfile << "Moving to closest destination floor for current passengers." << endl;
    }
    for(deque<long> passenger : current_passengers){
        //This statement ensures a positive value
        if(current_floor > passenger[2]){
            //Checks to see if this floor is closest
            if((current_floor-passenger[2]) < floor_difference){
                //Stores as the closest
                floor_difference = current_floor - passenger[2];
                next_floor = passenger[2];
            }
        }
        else{
            //Checks to see which floor is closest
            if((passenger[2]-current_floor) < floor_difference){
                //Stores as the closest
                floor_difference = passenger[2] - current_floor;
                next_floor = passenger[2];
            }
        }
    }
    if(current_passengers.size() < 10){
        //Decide by getting new passengers
        for(deque<long> passenger : available_passengers){
            //This statement ensures a positive value
            if(current_floor > passenger[1]){
                //Checks to see if this floor is closest
                if((current_floor-passenger[1]) < floor_difference){
                    //Stores as the closest
                    floor_difference = current_floor - passenger[1];
                    next_floor = passenger[1];
                }
            }
            else{
                //Checks to see which floor is closest
                if((passenger[1]-current_floor) < floor_difference){
                    //Stores as the closest
                    floor_difference = passenger[1] - current_floor;
                    next_floor = passenger[1];
                }
            }
        }
    }
    //RETURNS THE FLOOR TO GO TO
    return next_floor;
}

long decide_floor_optimal_multiple(deque<deque<long>> &current_passengers, deque<deque<long>> &available_passengers, long current_floor){
    long next_floor = current_floor;
    
    //This is to decide by current passengers
    long floor_difference = 1000000000000000;
    
    map<long,long> floors;
    
    
    for(deque<long> passenger : current_passengers){
        //This statement ensures a positive value
        if(current_floor > passenger[2]){
            //Checks to see if this floor is closest
            if((current_floor-passenger[2]) < floor_difference){
                //Stores as the closest
                floor_difference = current_floor - passenger[2];
                next_floor = passenger[2];
            }
        }
        else{
            //Checks to see which floor is closest
            if((passenger[2]-current_floor) < floor_difference){
                //Stores as the closest
                floor_difference = passenger[2] - current_floor;
                next_floor = passenger[2];
            }
        }
    }
    if(current_passengers.size() < 10){
        //Decide by getting new passengers
        for(deque<long> passenger : available_passengers){
            //This statement ensures a positive value
            if(current_floor > passenger[1]){
                //Checks to see if this floor is closest
                if((current_floor-passenger[1]) < floor_difference){
                    //Stores as the closest
                    floor_difference = current_floor - passenger[1];
                    next_floor = passenger[1];
                }
            }
            else{
                //Checks to see which floor is closest
                if((passenger[1]-current_floor) < floor_difference){
                    //Stores as the closest
                    floor_difference = passenger[1] - current_floor;
                    next_floor = passenger[1];
                }
            }
        }
    }
    //RETURNS THE FLOOR TO GO TO
    return next_floor;
}

void move_floor(long &current_floor, long next_floor, double elevator_rate, double &time){
    //Figures out how far the elevator moves
    long floor_difference = next_floor - current_floor;
    //Makes the difference positive
    floor_difference = (floor_difference > 0) ? floor_difference: (-1*floor_difference);
    //Increments the time
    time += floor_difference*elevator_rate;
    current_floor = next_floor; //Updates the floor
}

void unload_passengers(deque<deque<long>> &current_passengers, long current_floor, double passenger_rate, double &time, ofstream &myfile){
    deque<deque<long>> new_current_passengers;
    deque<deque<long>> unloaded_passengers;
    for(deque<long> passenger : current_passengers){
        //Checks each passenger to see if they need to be unloaded
        if(current_floor != passenger[2]){
            //Stores the passengers who are not unloaded
            new_current_passengers.push_back(passenger);
        }
        else{
            //Stores the passengers who are loaded
            unloaded_passengers.push_back(passenger);
            time += passenger_rate; //Adds time for each unloaded person
        }
    }
    //Prints out the details of the people who were unloaded
    if(unloaded_passengers.size() != 0){
        myfile << "Unloaded passengers" << endl << print_2d_deque(unloaded_passengers) << endl;
    }
    current_passengers = new_current_passengers;
}

void unload_passengers_multiple(deque<deque<long>> &current_passengers, long current_floor, double passenger_rate, double &time, double &min_wait_time, double &max_wait_time, double &total_wait_time){
    deque<deque<long>> new_current_passengers;
    deque<deque<long>> unloaded_passengers;
    double wait_time = 0;
    for(deque<long> passenger : current_passengers){
        //Checks each passenger to see if they need to be unloaded
        if(current_floor != passenger[2]){
            //Stores the passengers who are not unloaded
            new_current_passengers.push_back(passenger);
        }
        else{
            //Stores the passengers who are loaded
            unloaded_passengers.push_back(passenger);
            time += passenger_rate; //Adds time for each unloaded person
            //Calculates the wait time
            wait_time = time - passenger[0];
            if(wait_time > max_wait_time){
                max_wait_time = wait_time;
            }
            if(wait_time < min_wait_time){
                min_wait_time = wait_time;
            }
            total_wait_time += wait_time;
        }
    }
    current_passengers = new_current_passengers;
}

void load_passengers(deque<deque<long>> &current_passengers,deque<deque<long>> &available_passengers, long current_floor, double passenger_rate, double &time){
    if(current_passengers.size() < 10){
        deque<deque<long>> new_available_passengers;
        //Loops through all available passengers
        for(deque<long> passenger : available_passengers){
            //If the passenger should get on, add them to the current passengers
            if(current_floor == passenger[1]){
                current_passengers.push_back(passenger);
                time += passenger_rate;
            }
            else{
                //Otherwise keep them in the available passenges
                new_available_passengers.push_back(passenger);
            }
        }
        available_passengers = new_available_passengers; //Updates the available passengers
    }
}

void single_run(long floor_max, double passenger_rate, double elevator_rate, mt19937_64 &reng, long passenger_max, string turn, deque<deque<long>> all_passengers, ofstream &myfile){
    
    deque<deque<long>> available_passengers;
    deque<deque<long>> current_passengers;
    
    
    long next_floor, current_floor = 1;
    double time = 0;
    double last_time = 0;
    
    long cycle_number = 0;
    
    while((all_passengers.size() > 0) || (available_passengers.size() > 0) || (current_passengers.size() > 0)  ){
        myfile << endl << endl << "CYCLE NUMBER " << cycle_number + 1<< endl;
        
        //STEP 1) CHECK FOR AVAILABLE PASSENGERS
        get_new_passengers(available_passengers, all_passengers,time);
        if((current_passengers.size() != 0) || (available_passengers.size() != 0)){
            myfile << "Time before moving: "<< time << " seconds" << endl;
            myfile << "Number of passengers on elevator: " << current_passengers.size() << endl;
            
            if(available_passengers.size() != 0){
                myfile << "Passengers waiting:" << endl << print_2d_deque(available_passengers)<< endl;
            }
            else{
                myfile << "No passengers available at time = " << time << " seconds"<<  endl;
            }
            
            
            //STEP 2) LOAD NEW PASSENGERS
            load_passengers(current_passengers, available_passengers, current_floor, passenger_rate, time);
            if(current_passengers.size() != 0){
                myfile << "Current Passengers After Loading"<< endl << print_2d_deque(current_passengers) << endl;
            }
            
            
            //STEP 3) DECIDE FLOOR, MOVE TO THAT FLOOR
            myfile << "Current Floor: " << current_floor << endl;
            
            if(turn == "strategy"){
                next_floor = decide_floor_strategy_single(current_passengers, available_passengers, current_floor, myfile);
            }
            else if (turn == "optimal"){
                next_floor = decide_floor_optimal_single(current_passengers, available_passengers, current_floor, myfile);
                
            }
            if(next_floor != current_floor){
                move_floor(current_floor, next_floor, elevator_rate, time);
                myfile << "Moved to floor: " << current_floor << endl;
            }
            else{
                myfile << "Floor did not change." << endl;
            }
            
            
            //STEP 4) UNLOAD PASSENGERS
            unload_passengers(current_passengers, current_floor, passenger_rate, time, myfile);
            myfile << "Current time after loading, moving, and unloading: "<< time << " seconds"<< endl;
            myfile << "Time for cycle: " << time-last_time << " seconds"<< endl;
        }
        else{
            //STEP 5) CHANGE TIME IF NOTHING HAPPENED
            myfile << "No passengers available to move. Time incremented by one." << endl;
            time += 1;
        }
        
        last_time = time;
        
        //Increment cycle number
        cycle_number++;
    }
    myfile << endl << endl  <<"All passengers have been handled." << endl << "STATISTICS:" << endl << "total time: " << time << " seconds"<< endl << "number of cycles: " << cycle_number << endl << endl << endl;
    
}

long multiple_run(long floor_max, double passenger_rate, double elevator_rate, mt19937_64 &reng, long passenger_max, string turn, deque<deque<long>> all_passengers, double &total_time, double &min_total_time, double &max_total_time, double &total_wait_time, double &min_wait_time, double &max_wait_time, ofstream &myfile){
    deque<deque<long>> available_passengers;
    deque<deque<long>> current_passengers;
    
    long next_floor, current_floor = 1;
    double time = 0;
    double last_time = 0;
    
    long cycle_number = 0;
    
    while((all_passengers.size() > 0) || (available_passengers.size() > 0) || (current_passengers.size() > 0)  ){
        //STEP 1) CHECK FOR AVAILABLE PASSENGERS
        get_new_passengers(available_passengers, all_passengers,time);
        if((current_passengers.size() != 0) || (available_passengers.size() != 0)){
            //STEP 2) LOAD NEW PASSENGERS
            load_passengers(current_passengers, available_passengers, current_floor, passenger_rate, time);
            
            //STEP 3) DECIDE FLOOR, MOVE TO THAT FLOOR
            if(turn == "strategy"){
                next_floor = decide_floor_strategy_multiple(current_passengers, available_passengers, current_floor);
            }
            else if (turn == "optimal"){
                next_floor = decide_floor_optimal_multiple(current_passengers, available_passengers, current_floor);
                
            }
            if(next_floor != current_floor){
                move_floor(current_floor, next_floor, elevator_rate, time);
            }
            
            //STEP 4) UNLOAD PASSENGERS
            unload_passengers_multiple(current_passengers, current_floor, passenger_rate, time, min_wait_time, max_wait_time, total_wait_time);
            
        }
        else{
            //STEP 5) CHANGE TIME IF NOTHING HAPPENED
            time += 1;
        }
        
        last_time = time;
        
        //Increment cycle number
        cycle_number++;
    }
    total_time += time;
    if(time < min_total_time){
        min_total_time = time;
    }
    else if(time > max_total_time){
        max_total_time = time;
    }
    return time;
}

int main (){
    random_device rd;
    mt19937_64 reng;
    long floor_max, passenger_max, run_count, seed;
    double elevator_rate, passenger_rate;
    cin >> elevator_rate >> passenger_rate >> floor_max
    >> passenger_max >> run_count >> seed;
    
    reng.seed(seed);
    
    ofstream myfile;
    myfile.open("single_run.txt");
    
    deque<deque<long>> passengers = gen_passengers(floor_max, passenger_max, reng);
    
    myfile << "All PASSENGERS" << endl;
    myfile << print_2d_deque(passengers) << endl;
    myfile<< setfill('-') << setw(80) << "-" << endl;
    myfile << "RUNNING OPTIMAL SIMULATION" << endl;
    single_run(floor_max,passenger_rate, elevator_rate, reng, passenger_max, "optimal", passengers,myfile);
    myfile<< setfill('-') << setw(80) << "-" << endl;
    myfile << "RUNNING STRATEGY SIMULATION" << endl;
    single_run(floor_max,passenger_rate, elevator_rate, reng, passenger_max, "strategy", passengers, myfile);
    
    myfile.close();
    
    
    myfile.open("multiple_run.txt");
    
    double total_time_optimal = 0;
    double total_time_strategy = 0;
    
    double min_total_time_rand = 10000000000;
    double max_total_time_rand = 0;
    
    double total_wait_time_rand = 0;
    double min_wait_time_rand = 10000000000;
    double max_wait_time_rand = 0;
    
    double min_total_time_strat = 10000000000;
    double max_total_time_strat = 0;
    
    double total_wait_time_strat = 0;
    double min_wait_time_strat = 10000000000;
    double max_wait_time_strat = 0;
    
    long strategy_win = 0;
    long optimal_win = 0;
    long cnt = 0;
    double game_time_optimal;
    double game_time_strategy;
    
    while (cnt < run_count){
        passengers = gen_passengers(floor_max, passenger_max, reng);
        game_time_optimal = multiple_run(floor_max,passenger_rate, elevator_rate, reng, passenger_max, "optimal", passengers, total_time_optimal, min_total_time_rand, max_total_time_rand, total_wait_time_rand, min_wait_time_rand, max_wait_time_rand, myfile);
        game_time_strategy = multiple_run(floor_max,passenger_rate, elevator_rate, reng, passenger_max, "strategy", passengers, total_time_strategy, min_total_time_strat, max_total_time_strat, total_wait_time_strat, min_wait_time_strat, max_wait_time_strat, myfile);
        if (game_time_strategy < game_time_optimal){
            strategy_win += 1;
        }
        else{
            optimal_win += 1;
        }
        cout << cnt << endl;
        ++cnt;
    }
    myfile << "MULTIPLE RUN STATISTICS" << endl;
    myfile << "Ran " << run_count << " simulations." << endl;
    myfile << "Optimal beat strategy in " << optimal_win <<" games"<< endl;
    myfile << "Strategy beat optimal in " << strategy_win <<" games"<< endl;
    myfile << "Average time- optimal:" << total_time_optimal/run_count<< endl;
    myfile << "Average time- strategy:" << total_time_strategy/run_count<< endl;
    myfile << "Average wait time- optimal:" << total_wait_time_rand/(run_count*passenger_max)<< endl;
    myfile << "Average wait time- strategy:" << total_wait_time_strat/(run_count*passenger_max)<< endl;
    myfile << "Max wait time- optimal:" << max_wait_time_rand<< endl;
    myfile << "Max wait time- strategy:" << max_wait_time_strat<< endl;
    myfile << "Min wait time- optimal:" << min_wait_time_rand<< endl;
    myfile << "Min wait time- strategy:" << min_wait_time_strat<< endl;
    
    myfile.close();
}
