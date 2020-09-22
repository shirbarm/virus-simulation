#ifndef Virus_h_
#define Virus_h_

#include<string>
#include<iostream>
#include <typeinfo>
using namespace std;

class Virus{ 
public:
    Virus(string name,string str);
    Virus(const Virus& other);
    Virus& operator=(const Virus& other);
    virtual bool operator==(const Virus& other);
    virtual void update() = 0;
    string getName() const;
    void setName(string name);
    string getStr() const;
    void setStr(string str);
    void setPowerful(const string target);
    double getPowerful() const;
    int getRefCount() const;
    virtual ~Virus();

protected: /* maybe private will work */
    string name;
    string str;
    int length;
    double powerful;

private:
    struct virusValue {
        int refCount;
        string data; /*the original string*/
        virusValue(const string initValue);
        ~virusValue();
    };
    virusValue *value;
};



#endif /*Virus_h_*/