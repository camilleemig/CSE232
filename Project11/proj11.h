/**************
 *  Camille Emig
 *  CSE232 Project 11
 *  Single Linked List
 *  Code basis from Dr. Punch's 18.2 Example
 *************/
#ifndef PAL_H
#define PAL_H

#include<iostream>
using std::ostream; using std::cout; using std::endl;
#include<utility>
using std::swap;
#include<sstream>
using std::ostringstream;
#include<string>
using std::string;
using std::pair;

template<typename T>
class PAL;


//Element class code taken from Punch's Node class 18.2
//Only variable names have been changed.
template <typename T>
class Element{
private:
  Element *next_ = nullptr;
  string name_ = "";
  T color_ = T();
  
public:
  Element()=default;
  Element(string name, T d) : next_(nullptr), name_(name), color_(d){};
  friend ostream& operator<<(ostream& out, Element& n){
      out << n.name_ << ":" << n.color_;
      return out;
    
  }
  friend class PAL<T>;
};

//PAL class code taken from Punch's SingleLink class 18.2
//Only variable names have been changed.
template <typename T>
class PAL{
private:
  Element<T> *back_ = nullptr;
  Element<T> *front_ = nullptr;
  void print_list(ostream& out);  
public:
  PAL()=default;
  PAL(Element<T> n) : back_(&n), front_(&n) {};
  PAL(string n, T d);
  PAL(const PAL&);
  PAL& operator=(PAL);
  ~PAL();
  void add(Element<T> &n);
  void add(string name, T dat);
  pair<Element<T>*, Element<T>*> find(string name);    
  pair<Element<T>*, Element<T>*> find(Element<T> &n);
  void move_forward1(Element<T> &n);
  void move_to_front(Element<T> &n);  
  void move_back1(Element<T> &n);
  void move_to_back(Element<T> &n);  

  friend ostream& operator<<(ostream& out, PAL<T>& p){
    p.print_list(out);
    return out;
  };
};

template<typename T>
PAL<T>::PAL(string n, T d){
    //Constuctor code from example 18.2
    //Only variable names have been changed
    //Makes a new element, sets front and back to that element
    Element<T> *ptr = new Element<T>(n,d);
    back_ = ptr;
    front_ = ptr;
};


template<typename T>
void PAL<T>::print_list(ostream& out){
    //Constuctor code from example 18.2
    //Only variable names have been changed
    ostringstream oss;
    Element<T> *ptr;
    for(ptr = back_; ptr != nullptr; ptr = ptr->next_) //Walks from back to front
        oss << *ptr << ", "; //Prints each element
    string s = oss.str();
    out << s.substr(0,s.size()-2); //Returns the string without last ', '
}



template<typename T>
PAL<T>::PAL(const PAL& p){
    //Constuctor code from example 18.2
    //Only variable names have been changed
    //Handles if it's empty
    if (p.back_ == nullptr){
        back_ = nullptr;
        front_ = nullptr;
    }
    else{
        back_ = new Element<T>(*(p.back_)); //Copies the back
        front_ = back_; //Sets front to back
        Element<T>* p_ptr = p.back_->next_; //goes to the next element
        Element<T>* new_node; //New node template
        while (p_ptr != nullptr){
            new_node = new Element<T>(*p_ptr); //Makes a new node
            front_->next_ = new_node; //Sets the next
            p_ptr = p_ptr->next_; //Moves the pointer up one
            front_ = new_node; //Updates the front
        }
    }
}

template<typename T>
PAL<T>& PAL<T>::operator=(PAL p){
    //Equal constructor from example 18.2
    //Only variable names have been changed
    swap(front_, p.front_);
    swap(back_, p.back_);
    return *this;
}

template<typename T>
PAL<T>::~PAL(){
    //Destructor code from example 18.2
    //Only variable names have been changed
    Element<T>* to_del = back_; //Sets the first element to delete
    while (to_del != nullptr){
        back_ = back_->next_; //Walks down the list of elements
        delete to_del; //Deletes the element
        to_del = back_; //Sets the next element to delete
    }
    //Updates the pointers
    front_ = nullptr;
    back_ = nullptr;
}

template<typename T>
void PAL<T>::add(Element<T> &n){
    //Add back code from example 18.2 append_front
    //Only variable names have been changed
    if (back_ != nullptr){ //If there is an element
        n.next_ = back_; //point this to the current back
        back_ = &n; //Set the back to this
    }
    else {
        //Update front and back to be the new element
        front_=&n;
        back_=&n;
    }
}

template<typename T>
void PAL<T>::add(string name, T dat){
    //Add front code from example 18.2
    //Only variable names have been changed, element constructor changed to match.
    Element<T>* n = new Element<T>(name,dat);
    add(*n);
}

template<typename T>
pair<Element<T>*, Element<T>*> PAL<T>::find(string name){
    //Search loop from example 18.2
    //Variable names have been changed, second pointer code added
    Element<T> *previous_element = nullptr;
    Element<T> *element = nullptr;
    //Walks through the elements
    for(Element<T> *Element = back_; Element != nullptr; Element = Element->next_){
        //Checks the element to see if it is the same
        if (Element != nullptr && Element->name_ == name){
            element = Element; //Keeps track of the current element
            break; //Stops the loop
        } // of if
        previous_element = Element; //Keeps track of the last element
    } // of for
    auto return_pair = make_pair(element, previous_element);
    return return_pair;
}

template<typename T>
pair<Element<T>*, Element<T>*> PAL<T>::find(Element<T> &n){
    return this->find(n.name_); //Finds the element by name
}

template<typename T>
void PAL<T>::move_forward1(Element<T> &n){
    auto pr = this->find(n);
    auto previous = pr.second; //Keeps track of the last one
    auto current = pr.first; //Keeps track of the current one
    if(current!= nullptr && current->next_ != nullptr){
        if(previous != nullptr){ //If there was one before it
            auto move_back = current->next_; //Keeps track of the one ahead of it
            current->next_ = move_back->next_; //Points the current to the one it needs to point to
            move_back->next_ = current; //Points the one ahead to current
            previous->next_ = move_back; //Points previous to the one ahead
            if (current->next_ == nullptr){
                front_ = current; //Updates front if necessary
            }
        }
        else if(previous == nullptr){
            auto move_back = current->next_; //Keeps track of the one ahead
            current->next_ = move_back->next_; //Points the current to the one two ahead
            move_back->next_ = current; //Points the one ahead to current
            back_ = move_back; //Points the back to the one ahead
            if (current->next_ == nullptr){ //UPdates front if necessary
                front_ = current;
            }
        }
    }
}

template<typename T>
void PAL<T>::move_to_front(Element<T> &n){
    auto pr = this->find(n);
    auto previous = pr.second; //Keeps track of the last one
    auto current = pr.first; //Keeps track of the current one
    if(current != nullptr && current->next_ != nullptr){ //If it's not already at the front
        if(previous != nullptr){ //If there was one before it
            previous->next_ = current->next_; //Point the last one to the next one
            front_->next_ = current; //Point the front to current
            front_ = current; //Update front
            current->next_ = nullptr;
        }
        else if(previous == nullptr){ //If it's at the back
            back_ = current->next_; //update the back
            front_->next_ = current; //Point the current front to this
            front_ = current; //Update the front
            current->next_ = nullptr; //Update the next of current
        }
    }
}

template<typename T>
void PAL<T>::move_back1(Element<T> &n){
    //Stores previous and current
    auto pr = this->find(n);
    auto previous = pr.second;
    auto current = pr.first;
    //If there is a previous and current
    if(previous != nullptr && current != nullptr){
        if(previous == back_){ //If the previous is at the back
            previous->next_ = current->next_; //Point the previous to the next
            current->next_ = previous; //Point the current to the previous
            back_ = current; //Update current
        }
        else{
            auto pr_pr = this->find(*previous); //Finds the previous of the previous
            auto previous_previous = pr_pr.second; //Stores the previous of the previous
            previous_previous->next_ = current; //Points the previous of the previous to the current
            current->next_ = previous;  //Points the current to the previous
            previous->next_ = nullptr; //Points the previous to the front
        }
        if(current == front_){
            front_ = previous;
        }
    }
}

template<typename T>
void PAL<T>::move_to_back(Element<T> &n){
    auto pr = this->find(n);
    auto previous = pr.second;
    auto current = pr.first;
    if(previous != nullptr && current != nullptr){
        auto move_forward = back_;
        back_ = current;
        
        previous->next_ = current->next_;
        current->next_ = move_forward;
        if(current == front_){
            front_ = previous;
        }
    }
}


#endif
