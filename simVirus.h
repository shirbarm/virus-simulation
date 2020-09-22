#ifndef simVirus_h_
#define simVirus_h_

#include<string>
#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include "Covid.h"
#include "Sars.h"
#include "Mers.h"
using namespace std;

class simVirus{ 
public:
    simVirus(vector<Virus*> ancestor,vector<Virus*> descendant,string target,int timeBeats);
    simVirus(const simVirus& other);
    simVirus& operator=(const simVirus& other);
    bool operator==(const simVirus& other);
    bool hasMatch() const;
    virtual ~simVirus();
    void updateSingel();
    void printAncestor() const;
    void printDescendant() const;
    void printStronger() const;
    void findStrongestStr();
    int getVirusesNumber() const;
    void sortByPowerful();
    void updateGroup();
    Virus* virusType(const Virus *v);

    struct mySort {
        bool operator() (Virus* i,Virus* j) { return i->getPowerful() < j->getPowerful(); }
    } MySort;

private:
    vector<Virus*> ancestor;
    vector<Virus*> descendant;
    string target;
    int timeBeats;
    int virusesNumber;
    double strong; /* for the strongest string in all runing hisory */
    string strongStr; /* for the strongest string in all runing hisory */
    string stringLetter; /* for the strongest string in all runing hisory */
}; 

#endif /*simVirus_h_*/