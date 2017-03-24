#include<vector>
using std::vector;
#include<utility>
using std::pair;
#include<string>
using std::string;
#include<fstream>
using std::ifstream;
#include<map>
using std::map;
#include<sstream>
using std::istringstream; using std::ostringstream;
#include<cmath>
#include<algorithm>
using std::find; using std::copy;
#include <iterator>
#include "functions.h"
#include<iostream>
using std::cout;

//NODE FUNCTIONS
string Node::to_string () const {
    ostringstream oss;
    //Label:(X,Y)
    oss << label << ":(" << x << "," << y << ")";
    return oss.str();
}

bool Node::equal_nodes(const Node & other){
    //Can assume that the nodes are equal if the labels are the same
    return label == other.label;
}

double Node::distance(const Node & other) const{
    //Distance is the square root of the coordinates subtracted and squared
    return sqrt(pow(x-other.x, 2) + pow(y - other.y, 2));
}

//NETWORK FUNCTIONS
Network::Network(ifstream &file){
    long firstlong, secondlong;
    string label;
    //Gets the values from each line
    while(file >> firstlong >> secondlong >> label){
        //Adds the node
        put_node(Node(firstlong, secondlong, label));
    }
}

string Network::to_string() const{
    ostringstream oss;
    string s;
    //Label, Label, Label, Label
    for(pair<string, Node> p : nodes){
        oss << p.second.to_string() << ", ";
    }
    s = oss.str();
    //Remove last comma and space
    s = s.substr(0, s.size() - 2);
    return s;
}

Node Network::get_node(string s){
    auto it = nodes.find(s);
    if(it == nodes.end()){
        string error_str = "Node not found:"+s;
        throw std::out_of_range(error_str);
    }
    pair<string, Node> p = *it;
    return p.second;
}

void Network::put_node(Node new_node){
    nodes[new_node.label] = new_node;
}

bool Network::in_route(const Node& n){
    if(find(route.begin(), route.end(), n.label) == route.end()){
        return false;
    }
    return true;
}

Node Network::closest(Node & n){
    double shortest_distance = 100000000000.0;
    Node closest;
    for(pair<string, Node> p : nodes){
        auto it = find(route.begin(), route.end(), p.second.label);
        if(! p.second.equal_nodes(n) && (it == route.end())){
            if(n.distance(p.second) < shortest_distance){
                shortest_distance = n.distance(p.second);
                closest = p.second;
            }
        }
    }
    return closest;
}

string Network::calculate_route(const Node& start, const Node& end){
    ostringstream oss;
    string s;
    double total_distance = 0.0;
    //Set the first node
    Node last_node = start;
    route.push_back(start.label); //Add the first node to the route
    Node next_closest = closest(last_node); //Find the next node
    total_distance += last_node.distance(next_closest);
    route.push_back(next_closest.label); //Add that to the route
    while(! next_closest.equal_nodes(end)){
        //Store the last node
        last_node = next_closest;
        //Find the next closest
        next_closest = closest(last_node);
        total_distance += last_node.distance(next_closest);
        //Add to the route
        route.push_back(next_closest.label);
    }
    //Create output string
    oss << total_distance << ": ";
    copy(route.begin(), route.end(), std::ostream_iterator<string>(oss,","));
    s = oss.str();
    s = s.substr(0, s.size() - 1);
    return s;
}
