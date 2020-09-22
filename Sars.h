#ifndef Sars_h_
#define Sars_h_

#include<string>
#include<iostream>
#include <cstdlib>
#include "Virus.h"
using namespace std;

class Sars: public Virus{ 
public: 
    Sars(string name,string str):Virus(name,str){}
    Sars(const Virus& other): Virus(other){}
    virtual void update();
    ~Sars(){}
}; 

#endif /*Sars_h_*/