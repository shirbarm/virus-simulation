#ifndef Mers_h_
#define Mers_h_

#include<string>
#include<iostream>
#include <cstdlib>
#include "Virus.h"
using namespace std;

class Mers: public Virus{ 
public: 
    Mers(string name,string str):Virus(name,str){}
    Mers(const Virus& other): Virus(other){}
    virtual void update();
    ~Mers(){}
}; 

#endif /*Mers_h_*/