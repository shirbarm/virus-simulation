#include "simVirus.h"

simVirus::simVirus(vector<Virus*> ancestor,vector<Virus*> descendant,string target,int timeBeats){
    this->ancestor = ancestor;
    this->descendant = descendant;
    this->target = target;
    this->timeBeats = timeBeats;
    this->virusesNumber = ancestor.size();
    this->strong = 0;
    this->strongStr = "";
    this->stringLetter = "";
}

simVirus::simVirus(const simVirus& other){
    this->ancestor = other.ancestor;
    this->descendant = other.descendant;
    this->target = other.target;
    this->timeBeats = other.timeBeats;
    this->virusesNumber = other.virusesNumber;
    this->strong = other.strong;
    this->strongStr = other.strongStr;
    this->stringLetter = other.stringLetter;
}

simVirus& simVirus::operator=(const simVirus& other){
    if(*this==other) /*if they equals*/
        return *this;
    else{
        this->ancestor = other.ancestor;
        this->descendant = other.descendant;
        this->target = other.target;
        this->timeBeats = other.timeBeats;
        this->virusesNumber = other.virusesNumber;
        this->strong = other.strong;
        this->strongStr = other.strongStr;
        this->stringLetter = other.stringLetter;
    }
    return *this;
}

bool simVirus::operator==(const simVirus& other){ 
    if(typeid(*this) == typeid(other)){
        return true;
    }
    return false;
}

Virus* simVirus::virusType(const Virus* v){
    if(typeid(*v) == typeid(Sars)) return new Sars(*v);
    else if(typeid(*v) == typeid(Mers)) return new Mers(*v);
    else if(typeid(*v)==typeid(Covid)) return new Covid(*v);
    return nullptr;
}

int simVirus::getVirusesNumber() const{
    return virusesNumber;
}

void simVirus::printAncestor() const{
    vector<Virus*>::const_iterator it;
    int strLength = target.length();
    for(it=ancestor.begin(); it != ancestor.end(); it++){
        string str = (*it)->getStr();
        cout << (*it)->getName() << " ";
        for(int i=0;i<strLength;i++)
            cout << str.at(i) << " ";
        cout << (*it)->getRefCount() << endl; 
    }
}

void simVirus::printDescendant() const{
    vector<Virus*>::const_iterator it;
    int strLength = target.length();
    for(it=descendant.begin(); it != descendant.end(); it++){
        string str = (*it)->getStr();
        cout << (*it)->getName() << " ";
        for(int i=0;i<strLength;i++)
            cout << str.at(i) << " ";
        cout << endl;
    }
}

void simVirus::printStronger() const{
    int strLength = target.length();
    cout << stringLetter << " ";
    for(int i=0; i<strLength;i++)
        cout << strongStr.at(i) << " ";
}

void simVirus::findStrongestStr(){ /* the strongest string in all runing history */
    int size = descendant.size();   
    for (int i=0 ; i<size ; i++){
        if (descendant[i]->getPowerful() > strong){
            strong = descendant[i]->getPowerful(); 
            strongStr = descendant[i]->getStr();
            stringLetter = descendant[i]->getName();
        }
    }
}

bool simVirus::hasMatch() const{
    vector<Virus*>::const_iterator it;
    for(it=descendant.begin(); it != descendant.end(); it++){
        if((*it)->getPowerful() == 1.0 )
            return true;
    }
    return false;
}

void simVirus::sortByPowerful(){
    sort(descendant.begin(),descendant.end(),MySort);
}

void simVirus::updateSingel(){
    vector<Virus*>::const_iterator it;
    for(it=descendant.begin(); it != descendant.end(); it++){
        (*it)->update();
        (*it)->setPowerful(target);
    }
}

void simVirus::updateGroup(){
    int s,t,vectorLength=ancestor.size();
    int targetLength = target.length();
    int minS=1, maxS=vectorLength-3, minT=2, maxT=vectorLength-2;
    int firstVirus = rand() % vectorLength;
    int secondVirus = rand() % vectorLength;

    while(firstVirus == secondVirus){ /*for search different string from the population*/
        secondVirus = rand() % vectorLength;
    }

    s = minS + rand() % (( maxS + 1 ) - minS);
    t = minT + rand() % (( maxT + 1 ) - minT);
    if(s > t){
        int tmp = t;
        t = s;
        s = tmp;
    }
    t = t-s+1;

    Virus* first = virusType(ancestor.at(firstVirus)); /*first random choice from the ancestor's vector*/
    string type1 = first->getName();
    Virus* second = virusType(ancestor.at(secondVirus)); /*second random choice from the ancestor's vector*/
    string type2 = second->getName();

    string firstString = first->getStr();
    string secondString = second->getStr();
    string tmp1 = firstString.substr(s,t);
    string tmp2 = secondString.substr(s,t);
    
    string beg = firstString.substr(0,s);
    int cut1 = beg.length()+tmp1.length();
    int cut2 = targetLength-beg.length()-tmp1.length();
    string end = firstString.substr(cut1,cut2);
    firstString = beg + tmp2 + end;
    
    beg = secondString.substr(0,s);
    cut1 = beg.length()+tmp2.length();
    cut2 = targetLength-beg.length()-tmp2.length();
    end = secondString.substr(cut1,cut2);
    secondString = beg + tmp1 + end;

    first->setName(type1);
    first->setStr(firstString);
    second->setName(type2);
    second->setStr(secondString);

    for(int i=0;i<2;i++){
        delete descendant[i];
    }
    
    descendant.erase(descendant.begin(),descendant.begin()+2); /* remove the first and the second elements */
    descendant.push_back(first); /* add the new elements */
    descendant.push_back(second);
    findStrongestStr();
}

/*delete the descendant here because he make some change so we can't delete that
in "readFiles" - where I made him.
the ancestor vector delete in "readFiles" */
simVirus::~simVirus(){
    vector<Virus*>::const_iterator it;
    for(it=descendant.begin(); it != descendant.end() ; it++ ){
        delete (*it);
    }
}