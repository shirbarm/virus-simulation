#include "Virus.h"

Virus::Virus(string name,string str):value(new virusValue(str)){
    this->name = name;
    this->str = str;
    length = str.length();
    powerful = 0;
}

Virus::virusValue::virusValue(const string initValue):refCount(0){ /* c'tor of virusValue */
    data = initValue;
}

Virus::virusValue::~virusValue(){}

Virus::Virus(const Virus& other){
    this->name = other.name;
    this->str = other.str;
    this->length = other.length;
    this->powerful = other.powerful;
    this->value = other.value;
    ++value->refCount;
}

Virus& Virus::operator=(const Virus& other){
    if(*this==other) /*if they equals*/
        return *this;
    else{
        this->name=other.name;
        this->str=other.str;
        this->length=other.length;
        this->powerful = other.powerful;
        this->value = other.value;
    }
    return *this;
}

bool Virus::operator==(const Virus& other){
    if(typeid(*this) == typeid(other)){
        return this->getName()==other.getName();
    }
    return false;
}

string Virus::getName() const{
    return name;
}

void Virus::setName(string name){
    this->name = name;
}

string Virus::getStr() const{
    return str;
}

void Virus::setStr(string str){
    this->str = str;
}

void Virus::setPowerful(const string target){
    double cnt=0;
    double len=target.length();
    string virusString = getStr();
    for(int i=0;i<len;i++){
        if(virusString.at(i) == target.at(i)) 
            cnt++;
    }
    powerful = cnt/len;
}

double Virus::getPowerful() const{
    return powerful;
}

int Virus::getRefCount() const{
    return value->refCount;
}

Virus::~Virus(){ 
    if(--value->refCount==-1){
        delete value;
    }
}