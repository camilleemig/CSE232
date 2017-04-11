/*************
 *  Camille Emig
 *  Section 003
 *  Project 10
 *  Note: Code basis taken from example code 16.7 stackDynamicTemplate
 *************/

#ifndef STACK_H
#define STACK_H

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
    bool full();
    friend ostream& operator<< <ElementType>(ostream&,
					     const BiStack&);
};

template<typename ElementType>
void BiStack<ElementType>::grow_and_copy(){
  ElementType *new_ary;

  if (sz_ == 0){
    new_ary = new ElementType[1]{};
    sz_ = 1;
    ary_ = new_ary;
  }
  else{
      if (sz_*2 <= max_sz_) {
          new_ary = new ElementType[sz_ * 2]{};
          int new_ary_size = sz_ *2;
          copy(ary_, ary_+top1_+1, new_ary);
          int num_of_elements = sz_ - top2_;
          for (int i = 1; i <= num_of_elements; i++) {
              new_ary[new_ary_size-i] = ary_[sz_-i];
          }
          int difference = sz_ - top2_;
          sz_ *= 2;
          top2_ = sz_ - difference;
          std::swap (new_ary, ary_);
          delete [] new_ary;
      }
      else{
          throw std::overflow_error("stack past max");
      }
  }
}

template<typename ElementType>
BiStack<ElementType>::BiStack(initializer_list<ElementType> lst, size_t max_sz){
    sz_ = lst.size();
    max_sz_ = max_sz;
    ary_ = new ElementType[sz_]{};
    size_t indx = 0;
    top1_ = -1;
    top2_ = sz_;
    for (auto e : lst)
        ary_[indx++] = e;
    top1_ = indx-1;
}

template<typename ElementType>
BiStack<ElementType>::BiStack(size_t initial_sz, size_t max_sz){
    sz_ = initial_sz;
    max_sz_ = max_sz;
    ary_ = new ElementType[sz_];
}


template <typename ElementType>
BiStack<ElementType>::BiStack(const BiStack<ElementType> &s){
    sz_ = s.sz_;
    max_sz_ = s.max_sz_;
    top1_ = s.top1_;
    top2_ = s.top2_;
    ary_= new ElementType[s.sz_];
    copy(s.ary_, s.ary_+s.sz_, ary_);
}

template <typename ElementType>
BiStack<ElementType>& BiStack<ElementType>::operator=(BiStack<ElementType> s){
    swap(this->sz_, s.sz_);
    swap(this->max_sz_, s.sz_);
    swap(this->top1_, s.top1_);
    swap(this->top2_, s.top2_);
    swap(this->ary_, s.ary_);
    return *this;
}

template <typename ElementType>
    BiStack<ElementType>::~BiStack(){
    delete [] ary_;
}

template <typename ElementType>
ElementType BiStack<ElementType>::top1(){
  if (top1_ < 0)
    throw underflow_error("underflow stack 1");
  return ary_[top1_];
}

template <typename ElementType>
ElementType BiStack<ElementType>::top2(){
    if (top2_ == sz_)
        throw underflow_error("underflow stack 2");
    return ary_[top2_];
}

template <typename ElementType>
size_t const BiStack<ElementType>::max(){
    //Should be max size
    return max_sz_;
}

template <typename ElementType>
size_t const BiStack<ElementType>::size(){
    //Should be the number of elements in it
    return top1_+1 + (sz_ - top2_);
}

template <typename ElementType>
size_t const BiStack<ElementType>::capacity(){
    //Should be current size
    return sz_;
}


template <typename ElementType>
void BiStack<ElementType>::push1(ElementType element){
    if (top1_ == top2_ - 1){
        grow_and_copy();
        ary_[++top1_] = element;
    }
    else{
        ary_[++top1_] = element;
    }
}

template <typename ElementType>
void BiStack<ElementType>::push2(ElementType element){
    if (top2_ == (top1_ + 1) ){
        // never throws, grows!
        grow_and_copy();
    }
    ary_[--top2_] = element;
}

template <typename ElementType>
void BiStack<ElementType>::pop1(){
  if (top1_ < 0)
    throw underflow_error("underflow stack1");
  --top1_;
}

template <typename ElementType>
void BiStack<ElementType>::pop2(){
    if (top2_ == sz_)
        throw underflow_error("underflow stack2");
    ++top2_;
}


template <typename ElementType>
bool BiStack<ElementType>::empty1(){
    return top1_== -1;
}

template <typename ElementType>
bool BiStack<ElementType>::empty2(){
    return top2_== sz_;
}

template <typename ElementType>
ostream& operator<<(ostream &out, const BiStack<ElementType> &s){
    ostringstream oss;
    string outstring;
    if (s.top1_ != -1){
        out << "Top1 index:" << s.top1_ << endl;
    }
    else{
        out << "Top1 empty" << endl;
    }
    if (s.top2_ != s.sz_){
        out << "Top2 index:" << s.top2_ << endl;
    }
    else{
        out << "Top2 empty" << endl;
    }
    out << "Size:" << s.top1_+1 + (s.sz_ - s.top2_) <<endl;
    out << "Capacity:" << s.sz_ <<endl;
    
    copy(s.ary_, (s.ary_+s.sz_), ostream_iterator<ElementType>(oss, ","));
    outstring = oss.str();
    outstring = outstring.substr(0,outstring.size() -1);
    out << outstring;
    return out;
}


#endif
