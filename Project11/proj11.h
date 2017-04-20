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
//#include<utility>
using std::pair;

// forward declaration so we can make Element a friend of PAL
template<typename T>
class PAL;

//Element class
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


template<typename T>
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
    for(ptr = back_; ptr != nullptr; ptr = ptr->next_)
        oss << *ptr << ", ";
    string s = oss.str();
    out << s.substr(0,s.size()-2);
}



template<typename T>
PAL<T>::PAL(const PAL& p){
    if (p.back_ == nullptr){
        back_ = nullptr;
        front_ = nullptr;
    }
    else{
        back_ = new Element<T>(*(p.back_));
        front_ = back_;
        Element<T>* p_ptr = p.back_->next_;
        Element<T>* new_node;
        while (p_ptr != nullptr){
            new_node = new Element<T>(*p_ptr);
            front_->next_ = new_node;
            p_ptr = p_ptr->next_;
            front_ = new_node;
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
    Element<T>* to_del = back_;
    while (to_del != nullptr){
        back_ = back_->next_;
        delete to_del;
        to_del = back_;
    }
    front_ = nullptr;
    back_ = nullptr;
}

template<typename T>
void PAL<T>::add(Element<T> &n){
    //Add back code from example 18.2
    //Only variable names have been changed
    if (back_ != nullptr){
        n.next_ = back_;
        back_ = &n;
    }
    else {
        front_=&n;
        back_=&n;
    }
}

template<typename T>
void PAL<T>::add(string name, T dat){
    //Add back code from example 18.2
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
    for(Element<T> *Element = back_; Element != nullptr; Element = Element->next_){
        if (Element != nullptr && Element->name_ == name){
            element = Element;
            break;
        } // of if
        previous_element = Element;
    } // of for
    auto return_pair = make_pair(element, previous_element);
    return return_pair;
}

template<typename T>
pair<Element<T>*, Element<T>*> PAL<T>::find(Element<T> &n){
    
    return this->find(n.name_);
}

template<typename T>
void PAL<T>::move_forward1(Element<T> &n){
    auto pr = this->find(n);
    auto previous = pr.second;
    auto current = pr.first;
    if(current!= nullptr && current->next_ != nullptr){
        if(previous != nullptr){
            auto move_back = current->next_;
            current->next_ = move_back->next_;
            move_back->next_ = current;
            previous->next_ = move_back;
            if (current->next_ == nullptr){
                front_ = current;
            }
        }
        else if(previous == nullptr){
            auto move_back = current->next_;
            current->next_ = move_back->next_;
            move_back->next_ = current;
            back_ = move_back;
            if (current->next_ == nullptr){
                front_ = current;
            }
        }
    }
}

template<typename T>
void PAL<T>::move_to_front(Element<T> &n){
    auto pr = this->find(n);
    auto previous = pr.second;
    auto current = pr.first;
    if(current->next_ != nullptr){
        if(current!= nullptr && previous != nullptr){
            previous->next_ = current->next_;
            front_->next_ = current;
            front_ = current;
            current->next_ = nullptr;
        }
        else if(current!= nullptr && previous == nullptr){
            back_ = current->next_;
            front_->next_ = current;
            front_ = current;
            current->next_ = nullptr;
        }
    }
}

template<typename T>
void PAL<T>::move_back1(Element<T> &n){
    auto pr = this->find(n);
    auto previous = pr.second;
    auto current = pr.first;
    if(previous != nullptr && current != nullptr){
        if(previous == back_){
            previous->next_ = current->next_;
            current->next_ = previous;
            back_ = current;
        }
        else{
            auto pr_pr = this->find(*previous);
            auto previous_previous = pr_pr.second;
            previous_previous->next_ = current;
            current->next_ = previous;
            previous->next_ = nullptr;
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
