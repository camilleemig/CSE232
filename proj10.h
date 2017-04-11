/*************
 *  Camille Emig
 *  Section 003
 *  Project 10
 *  Note: Code basis taken from example code 16.7 stackDynamicTemplate
 *************/

#ifndef BISTACK_H
#define BISTACK_H

#include<iostream>
using std::ostream;
#include<string>
using std::string; using std::to_string;
#include<iterator>
using std::ostream_iterator;
#include<sstream>
using std::ostringstream;
#include<algorithm>
using std::copy;
using std::swap;
#include<initializer_list>
using std::initializer_list;

template<typename ElementType>
class BiStack;

template <typename ElementType>
ostream& operator<<(ostream& out, const BiStack<ElementType> &s);

template<typename ElementType>
class BiStack{
private:
    ElementType *ary_ = nullptr;
    int sz_ = 4;
    int max_sz_ = 16;
    int top1_ = -1;
    int top2_ = sz_;
    void grow_and_copy();

public:
    BiStack()=default;
    BiStack(size_t initial_sz, size_t max_sz = 16);
    BiStack(initializer_list<ElementType>, size_t max_sz = 16);
    
    BiStack(const BiStack &s);   // copy
    ~BiStack();                // destructor
    BiStack& operator=(BiStack);
    
    ElementType top1();
    ElementType top2();
    
    const size_t size();
    const size_t max();
    const size_t capacity();
    
    void pop1();
    void pop2();
    
    void push1(ElementType);
    void push2(ElementType);
    
    bool empty1();
    bool empty2();
    
    friend ostream& operator<< <ElementType>(ostream&,
					     const BiStack&);
};


template<typename ElementType>
BiStack<ElementType>::BiStack(initializer_list<ElementType> lst, size_t max_sz){
    //List constructor
    
    //Sets size to the size of the list
    sz_ = lst.size();
    //Sets the max size to provided size or 16 if no size is provided
    max_sz_ = max_sz;
    //Sets top variables
    top1_ = -1;
    top2_ = sz_;
    //Creates a new array to hold the list items
    ary_ = new ElementType[sz_]{};
    //Used to iterate through array to add list items
    size_t indx = 0;
    //Copys list items into array
    for (auto e : lst)
        ary_[indx++] = e;
    //Updates the top of stack 1
    top1_ = indx-1;
}

template<typename ElementType>
BiStack<ElementType>::BiStack(size_t initial_sz, size_t max_sz){
    //Size constuctor
    
    //Initializes varaibles
    sz_ = initial_sz;
    max_sz_ = max_sz;
    ary_ = new ElementType[sz_];
    top1_ = -1;
    top2_ = sz_;
}

template <typename ElementType>
BiStack<ElementType>::BiStack(const BiStack<ElementType> &s){
    //Copy constuctor
    sz_ = s.sz_;
    max_sz_ = s.max_sz_;
    
    top1_ = s.top1_;
    top2_ = s.top2_;
    
    ary_= new ElementType[s.sz_];
    copy(s.ary_, s.ary_+s.sz_, ary_);
}

template <typename ElementType>
BiStack<ElementType>& BiStack<ElementType>::operator=(BiStack<ElementType> s){
    //Assignment operator
    swap(this->sz_, s.sz_);
    swap(this->max_sz_, s.sz_);
    
    swap(this->top1_, s.top1_);
    swap(this->top2_, s.top2_);
    
    swap(this->ary_, s.ary_);
    
    return *this;
}

template <typename ElementType>
BiStack<ElementType>::~BiStack(){
    //Destructor
    delete [] ary_;
}

template<typename ElementType>
void BiStack<ElementType>::grow_and_copy(){
  ElementType *new_ary;

  if (sz_ == 0){
    new_ary = new ElementType[1]{};
    sz_ = 1;
    ary_ = new_ary;
  }
  else{
      //If the array can double in size without growing past max size
      if (sz_*2 <= max_sz_) {
          //Create a new array
          new_ary = new ElementType[sz_ * 2]{};
          int new_ary_size = sz_ *2;
          
          //Copy the old array into the new array
          //copy front
          copy(ary_, ary_+top1_+1, new_ary);
          //copy back
          int num_of_elements = sz_ - top2_;
          for (int i = 1; i <= num_of_elements; i++) {
              new_ary[new_ary_size-i] = ary_[sz_-i];
          }
          
          //Update size and tops
          int difference = sz_ - top2_;
          sz_ *= 2;
          top2_ = sz_ - difference;
          
          //Swap arrays
          std::swap (new_ary, ary_);
          //Prevent memory leak
          delete [] new_ary;
      }
      //If it is too big, throw an error
      else{
          throw std::overflow_error("stack past max");
      }
  }
}



template <typename ElementType>
ElementType BiStack<ElementType>::top1(){
    
    //If there are no elements in stack 1, throw an error
    if (top1_ < 0)
        throw underflow_error("underflow stack 1");
    
    //Otherwise return the top element in stack 1
    return ary_[top1_];
}

template <typename ElementType>
ElementType BiStack<ElementType>::top2(){
    
    //If there are no elements in stack 2, throw an error
    if (top2_ == sz_)
        throw underflow_error("underflow stack 2");
    
    //Otherwise return the top element in stack 2
    return ary_[top2_];
}

template <typename ElementType>
size_t const BiStack<ElementType>::max(){
    //Should be max size
    return max_sz_;
}

template <typename ElementType>
size_t const BiStack<ElementType>::size(){
    //Should be the number of elements in the stacks
    return top1_+1 + (sz_ - top2_);
}

template <typename ElementType>
size_t const BiStack<ElementType>::capacity(){
    //Should be current size
    return sz_;
}


template <typename ElementType>
void BiStack<ElementType>::push1(ElementType element){
    //If there are no more empty spaces, attempt to grow the array.
    if (top1_ == top2_ - 1){
        grow_and_copy();
        ary_[++top1_] = element;
    }
    //Otherwise update the array and top
    else{
        ary_[++top1_] = element;
    }
}

template <typename ElementType>
void BiStack<ElementType>::push2(ElementType element){
    //If there are no more empty spaces, attempt to grow the array.
    if (top2_ == (top1_ + 1) ){
        grow_and_copy();
    }
    //Otherwise update the array and top
    ary_[--top2_] = element;
}

template <typename ElementType>
void BiStack<ElementType>::pop1(){
    
    //If there are no elements in stack 1, throw an error
    if (top1_ < 0)
        throw underflow_error("underflow stack 1");
    
    //Otherwise update top to remove item
    --top1_;
}

template <typename ElementType>
void BiStack<ElementType>::pop2(){
    
    //If there are no elements in stack 2, throw an error
    if (top2_ == sz_)
        throw underflow_error("underflow stack 2");
    
    //Otherwise update top to remove item
    ++top2_;
}


template <typename ElementType>
bool BiStack<ElementType>::empty1(){
    //Check if there are elements in stack 1
    return top1_== -1;
}

template <typename ElementType>
bool BiStack<ElementType>::empty2(){
    //Check if there are elements in stack 2
    return top2_== sz_;
}

template <typename ElementType>
ostream& operator<<(ostream &out, const BiStack<ElementType> &s){
    ostringstream oss;
    string outstring;
    //Print stack 1 top index
    if (s.top1_ != -1){
        out << "Top1 index:" << s.top1_ << endl;
    }
    else{
        out << "Top1 empty" << endl;
    }
    
    //Print stack 2 top index
    if (s.top2_ != s.sz_){
        out << "Top2 index:" << s.top2_ << endl;
    }
    else{
        out << "Top2 empty" << endl;
    }
    
    //Prints size and capacity
    out << "Size:" << s.top1_+1 + (s.sz_ - s.top2_) <<endl;
    out << "Capacity:" << s.sz_ <<endl;
    
    //Prints the underlying array
    copy(s.ary_, (s.ary_+s.sz_), ostream_iterator<ElementType>(oss, ","));
    outstring = oss.str();
    outstring = outstring.substr(0,outstring.size() -1);
    out << outstring;
    
    //Returns the outstream
    return out;
}


#endif
