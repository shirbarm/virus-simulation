#ifndef Covid_h_
#define Covid_h_

#include<string>
#include<iostream>
#include <cstdlib>
#include "Virus.h"
using namespace std;

class Covid: public Virus{ 
public: 
    Covid(string name,string str):Virus(name,str){}
    Covid(const Virus& other): Virus(other){}
    virtual void update();
    ~Covid(){}
}; 

#endif /*Covid_h_*/