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
#include "random_support.h"

void get_new_passengers(deque<deque<long>> &available_passengers, deque<deque<long>> &all_passengers, double &current_time){
    //Iterate through all passengers
    for(deque<long> passenger : all_passengers){
        //Check to see if passenger is available
        if(passenger[0] <= current_time){
            //Add the passenger to available passengers, remove from total list
            available_passengers.push_back(passenger);
            all_passengers.pop_front();
        }
        //If it has passed the current time, stop checking
        else{
            break;
        }
    }
}

long decide_floor_strategy(deque<deque<long>> &current_passengers, deque<deque<long>> &available_passengers, long current_floor){
    //Set next possible floor to first floor
    long next_floor = 1;
    
    //This is to decide by current passengers
    long floor_difference = 1000000000000000;
    
    //These variable are to decide by available passengers
    map<long,long> floors;
    long max_passengers = 0;
    long old_floor_difference, new_floor_difference;
    
    //DECIDE BY CURRENT PASSENGERS
    //Iterate through passengers on elevator
    for(deque<long> passenger : current_passengers){
        //Check for proper floor difference
        if(current_floor > passenger[1]){
            //If this passenger is closest, set their floor to the next floor
            if((current_floor-passenger[1]) < floor_difference){
                floor_difference = current_floor - passenger[1];
                next_floor = passenger[1];
            }
        }
        else{
            //If this passenger is closest, set their floor to the next floor
            if((passenger[1]-current_floor) < floor_difference){
                floor_difference = passenger[1] - current_floor;
                next_floor = passenger[1];
            }
        }
    }
    
    //DECIDE BY GETTING NEW PASSENGERS
    //If the floor was not set by current passengers
    if(floor_difference == 1000000000000000){
        //Iterate through available passengers
        for(deque<long> passenger : available_passengers){
            //Count number of passengers on each floor, using a map
            if(floors.find(passenger[2]) != floors.end()){
                floors.at(passenger[2]) += 1;
            }
            else{
                floors.insert(std::pair<long,long>(passenger[2],1));
            }
        }
        for(auto elem : floors)
        {
            //If this floor has the most amount of people waiting, go to it
            if(elem.second > max_passengers){
                next_floor = elem.first;
                max_passengers = elem.second;
            }
            //If this floor has the same amount of people waiting, check to see which is closest
            else if(elem.second == max_passengers){
                old_floor_difference = (current_floor > next_floor) ? current_floor - next_floor: next_floor - current_floor;
                new_floor_difference = (current_floor > elem.first) ? current_floor - elem.first: elem.first - current_floor;
                //If it's closer than the other one with this amount of passengers, go to it
                if(new_floor_difference <= old_floor_difference){
                    next_floor = elem.first;
                }
            }
        }

    }
    
    //RETURNS THE FLOOR TO GO TO
    return next_floor;
}

long decide_floor_random(deque<deque<long>> &current_passengers, deque<deque<long>> &available_passengers, mt19937_64 &reng){
    long next_floor = 1;
    //If there are passengers on the elevator, go to those first
    if(current_passengers.size() != 0){
        //Picks a random number to index into current passengers at
        next_floor = current_passengers.at(random_long_in_range(0,current_passengers.size()-1,reng))[1];
    }
    //If there were no passengers on the elevator, go by available passengers
    else if(available_passengers.size() != 0){
        //Picks a random number to index into available passengers at
        next_floor = available_passengers.at(random_long_in_range(0, available_passengers.size()-1,reng))[2];
    }
    //RETURNS THE FLOOR TO GO TO
    return next_floor;
}



void move_floor(long &current_floor, long next_floor, double elevator_rate, double &time){
    //Calculate number of floors moved
    long floor_difference = next_floor - current_floor;
    //Make sure number of floors moved is positive
    floor_difference = (floor_difference > 0) ? floor_difference: (-1*floor_difference);
    //Add time based on amount of floors moved
    time += floor_difference*elevator_rate;
    //Update the floor
    current_floor = next_floor;
}

void unload_passengers(deque<deque<long>> &current_passengers, long current_floor, double passenger_rate, double &time, ofstream &myfile){
    deque<deque<long>> new_current_passengers; //Used to remove passengers from current passengers
    deque<deque<long>> unloaded_passengers; //Used so that it is possible to print the unloaded passengers
    
    //Iterate through passengers on the elevator
    for(deque<long> passenger : current_passengers){
        //If they are not getting off on this floor, keep them on the elevator
        if(current_floor != passenger[1]){
            new_current_passengers.push_back(passenger);
        }
        //If they are getting off at this elevator
        else{
            //Add them to the list of unloaded people
            unloaded_passengers.push_back(passenger);
            //Increase the time for this person leaving
            time += passenger_rate;
        }
    }
    //Prints the people who left, as long as at least one person left
    if(unloaded_passengers.size() != 0){
        myfile << "Unloaded passengers" << endl << print_2d_deque(unloaded_passengers) << endl;
    }
    //Updates the passengers on the elevator to not include those who left
    current_passengers = new_current_passengers;
}

void unload_passengers_multiple(deque<deque<long>> &current_passengers, long current_floor, double passenger_rate, double &time, double &min_wait_time, double &max_wait_time, double &total_wait_time){
    deque<deque<long>> new_current_passengers; //Used to remove passengers from current passengers
    //deque<deque<long>> unloaded_passengers; Not used?
    double wait_time = 0; //Used for statistics
    
    //Iterate through passengers on the elevator
    for(deque<long> passenger : current_passengers){
        //If they are not getting off on this floor, keep them on the elevator
        if(current_floor != passenger[1]){
            new_current_passengers.push_back(passenger);
        }
        //If they are getting off at this elevator
        else{
            //unloaded_passengers.push_back(passenger); not necessary?
            //Increase the time for this person leaving
            time += passenger_rate;
            //Calculate the person's wait time, update max and min wait times if necessary
            wait_time = time - passenger[0];
            if(wait_time > max_wait_time){
                max_wait_time = wait_time;
            }
            if(wait_time < min_wait_time){
                min_wait_time = wait_time;
            }
            //Update the total wait time of all passengers
            total_wait_time += wait_time;
        }
    }
    //Updates the passengers on the elevator to not include those who left
    current_passengers = new_current_passengers;
}


void load_passengers(deque<deque<long>> &current_passengers,deque<deque<long>> &available_passengers, long current_floor, double passenger_rate, double &time){
    deque<deque<long>> new_available_passengers; //Used to remove passengers from available passengers
    
    //Iterate through passengers who are available
    for(deque<long> passenger : available_passengers){
        //If they are on this floor
        if(current_floor == passenger[2]){
            //Add them to the elevator, increase time for them getting on
            current_passengers.push_back(passenger);
            time += passenger_rate;
        }
        else{
            //Add them to the list of people still available
            new_available_passengers.push_back(passenger);
        }
    }
    //Update those available to not include the people who got on the elevator
    available_passengers = new_available_passengers;
}

void single_run(long floor_max, double passenger_rate, double elevator_rate, mt19937_64 &reng, long passenger_max, string turn, deque<deque<long>> all_passengers, ofstream &myfile){
    myfile << "Running " << turn << " simulation" << endl;
    
    //Used to store the passengers
    deque<deque<long>> available_passengers; //People whose time is less than or equal to the current time
    deque<deque<long>> current_passengers; //People on the elevator
    
    long next_floor, current_floor = 1;
    double time = 0;
    double last_time = 0; //Used to calculate the difference in time for each cycle
    
    long cycle_number = 0; //Used to keep track of the total amount of times it had to loop
    
    //While there is still someone to move
    while((all_passengers.size() > 0) || (available_passengers.size() > 0) || (current_passengers.size() > 0)  ){
        myfile << endl << endl << "CYCLE NUMBER " << cycle_number + 1<< endl;
        
        //STEP 1) CHECK FOR AVAILABLE PASSENGERS
        get_new_passengers(available_passengers, all_passengers,time);
        //STEP 2) ONLY CONTINUE WITH THIS CYCLE IF THERE IS SOMEONE TO MOVE
        if((current_passengers.size() != 0) || (available_passengers.size() != 0)){
            myfile << "Time before moving: "<< time << " seconds" << endl;
            myfile << "Number of passengers on elevator: " << current_passengers.size() << endl;
            
            if(available_passengers.size() != 0){
                myfile << "Passengers available:" << endl << print_2d_deque(available_passengers)<< endl;
            }
            else{
                myfile << "No passengers available at time = " << time << " seconds"<<  endl;
            }
            
            
            //STEP 3) LOAD NEW PASSENGERS
            load_passengers(current_passengers, available_passengers, current_floor, passenger_rate, time);
            if(current_passengers.size() != 0){
                myfile << "Current Passengers After Loading"<< endl << print_2d_deque(current_passengers) << endl;
            }

            //STEP 4) DECIDE FLOOR, MOVE TO THAT FLOOR
            myfile << "Current Floor: " << current_floor << endl;
            
            //Decides which floor to go to
            if(turn == "strategy"){
                next_floor = decide_floor_strategy(current_passengers, available_passengers, current_floor);
            }
            else if (turn == "random"){
                next_floor = decide_floor_random(current_passengers, available_passengers, reng);

            }
            
            //If the elevator needs to move, move it
            if(next_floor != current_floor){
                move_floor(current_floor, next_floor, elevator_rate, time);
                myfile << "Moved to floor: " << current_floor << endl;
            }
            else{
                myfile << "Floor did not change." << endl;
            }
            
            
            //STEP 5) UNLOAD PASSENGERS
            unload_passengers(current_passengers, current_floor, passenger_rate, time, myfile);
            myfile << "Current time after moving and unloading: "<< time << " seconds"<< endl;
            myfile << "Time for cycle: " << time-last_time << " seconds"<< endl;
        }
        else{
            //CHANGE TIME IF NOTHING HAPPENED
            myfile << "No passengers available to move. Time incremented by one." << endl;
            time += 1;
        }
        
        //Change the time for this cycle
        last_time = time;

        //Increment cycle number
        cycle_number++;
    }
    myfile << endl << endl  <<"All passengers have been handled." << endl << "STATISTICS:" << endl << "total time: " << time << " seconds"<< endl << "number of cycles: " << cycle_number << endl << endl << endl;

}

void multiple_run(long floor_max, double passenger_rate, double elevator_rate, mt19937_64 &reng, long passenger_max, string turn, deque<deque<long>> all_passengers, double &total_time, double &min_total_time, double &max_total_time, double &total_wait_time, double &min_wait_time, double &max_wait_time, ofstream &myfile){
    deque<deque<long>> available_passengers; //People whose time is less than or equal to the current time
    deque<deque<long>> current_passengers; //People who are on the elevator
    
    long next_floor, current_floor = 1;
    double time = 0;
    double last_time = 0; //Used to keep track of cycle time
    
    long cycle_number = 0; //Used to keep track of how many cycles it went through
    
    //While there are people to move
    while((all_passengers.size() > 0) || (available_passengers.size() > 0) || (current_passengers.size() > 0)  ){
        //STEP 1) CHECK FOR AVAILABLE PASSENGERS
        get_new_passengers(available_passengers, all_passengers,time);
        //If there are people available
        if((current_passengers.size() != 0) || (available_passengers.size() != 0)){
            //STEP 2) LOAD NEW PASSENGERS
            load_passengers(current_passengers, available_passengers, current_floor, passenger_rate, time);
            
            //STEP 3) DECIDE FLOOR, MOVE TO THAT FLOOR
            if(turn == "strategy"){
                next_floor = decide_floor_strategy(current_passengers, available_passengers, current_floor);
            }
            else if (turn == "random"){
                next_floor = decide_floor_random(current_passengers, available_passengers, reng);
                
            }
            //Only move to the next floor if the floor actually changes
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
        
        //Update for cycle time tracking
        last_time = time;
        
        //Increment cycle number
        cycle_number++;
    }
    //Each time the elevator finishes, do this
    total_time += time; //Updates the total time to include this run
    if(time < min_total_time){ //Updates the min run time if necessary
        min_total_time = time;
    }
    else if(time > max_total_time){ //Updates the max run time if necessary
        max_total_time = time;
    }

}


int main (){
    random_device rd;
    mt19937_64 reng;
    long floor_max, passenger_max, run_count, seed;
    double elevator_rate, passenger_rate;
    cin >> elevator_rate >> passenger_rate >> floor_max
        >> passenger_max >> run_count >> seed;

    reng.seed(seed);
    /*
     if for some reason you also want a random seed each time
     so that things are as random as possible, see the random engine
     using the random_device instead of a seed. Sequence will be
     random but likely un-reproduceable unless you remember the seed
     */
    // reng.seed( rd() );

    ofstream myfile; //File to write to
    myfile.open("single_run.txt");
    
    myfile << random_long_in_range(0,1,reng) << endl; //WHYYYYY
    myfile << random_long_in_range(10,100,reng) << endl; //WHYYYYY

    
    deque<deque<long>> passengers = gen_passengers(floor_max, passenger_max, reng); //Generates passengers for single run
    
    //Runs both single runs with the first batch of passengers
    single_run(floor_max,passenger_rate, elevator_rate, reng, passenger_max, "random", passengers,myfile);
    single_run(floor_max,passenger_rate, elevator_rate, reng, passenger_max, "strategy", passengers, myfile);
    
    //Closes the single run file
    myfile.close();
    
    //Opens the file for multiple runs
    myfile.open("multiple_run.txt");
    
    //Variables for keeping track of total time
    double total_time_random = 0;
    double total_time_strategy = 0;
    
    double min_total_time_rand = 10000000000;
    double max_total_time_rand = 0;
        
    double min_total_time_strat = 10000000000;
    double max_total_time_strat = 0;
    
    //Variables for keeping track of wait time
    double total_wait_time_rand = 0;
    double min_wait_time_rand = 10000000000;
    double max_wait_time_rand = 0;

    double total_wait_time_strat = 0;
    double min_wait_time_strat = 10000000000;
    double max_wait_time_strat = 0;
    
    
    long cnt = 0;
    while (cnt < run_count){
        //Generates a new load of passengers for each run
        passengers = gen_passengers(floor_max, passenger_max, reng);
        //Runs the elevator for random and strategy
        multiple_run(floor_max,passenger_rate, elevator_rate, reng, passenger_max, "random", passengers, total_time_random, min_total_time_rand, max_total_time_rand, total_wait_time_rand, min_wait_time_rand, max_wait_time_rand, myfile);
        multiple_run(floor_max,passenger_rate, elevator_rate, reng, passenger_max, "strategy", passengers, total_time_strategy, min_total_time_strat, max_total_time_strat, total_wait_time_strat, min_wait_time_strat, max_wait_time_strat,myfile);
        ++cnt;
    }
    
    //Outputs all statistics to the file. Pretty self explanatory.
    myfile << "MULTIPLE RUN STATISTICS" << endl;
    myfile << "Average time- random:" << total_time_random/run_count<< endl;
    myfile << "Average time- strategy:" << total_time_strategy/run_count<< endl;
    myfile << "Average wait time- random:" << total_wait_time_rand/(run_count*passenger_max)<< endl;
    myfile << "Average wait time- strategy:" << total_wait_time_strat/(run_count*passenger_max)<< endl;
    myfile << "Max wait time- random:" << max_wait_time_rand<< endl;
    myfile << "Max wait time- strategy:" << max_wait_time_strat<< endl;
    myfile << "Min wait time- random:" << min_wait_time_rand<< endl;
    myfile << "Min wait time- strategy:" << min_wait_time_strat<< endl;

    //Closes the file
    myfile.close();
}
