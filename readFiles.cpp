#include "readFiles.h"

readFiles::readFiles(string configFile,string firstGenerationFile){
    this->configFile = configFile;
    this->firstGenerationFile = firstGenerationFile;
}

void readFiles::openConfig(){
    ifstream config;
    config.open(configFile.c_str());
    if (!config.is_open()){
        config.close();
        throw fileNotOpen(configFile);
    }

    int stringDimension,timeBeats,index;
    string target,line,tmp;

    getline(config,line);
    stringstream dimension(line);
    dimension >> stringDimension;
    if(stringDimension<THREE || stringDimension>TEN_THOUSAND){
        config.close();
        throw invalidInput();
    }

    getline(config,line);
    string space=" ";
    index = line.find(space);

    while(index != -1){
        tmp = line.substr(0,index);
        target = target+tmp;
        line = line.substr(index+1,line.length());
        index = line.find(space);
        if(index == -1)
            target = target+line;
    }
    int len = target.length();
    if(len != stringDimension){
        config.close();
        throw invalidInput();
    }

    getline(config,line);
    stringstream TB(line);
    TB >> timeBeats;
    if(timeBeats<0){
        config.close();
        throw invalidInput();
    }
    config.close();
    this->target = target;
    this->timeBeats = timeBeats;
    this->stringDimension = stringDimension;
}

void readFiles::openFirstGeneration(){
    ifstream first_generation;
    first_generation.open(firstGenerationFile.c_str());
    if(!first_generation.is_open()){
        first_generation.close();
        throw fileNotOpen(firstGenerationFile);
    }
    
    int virusesNumber,index,cnt=0;
    string line,tmp,space=" ";
    getline(first_generation,line);
    stringstream vn(line);
    vn >> virusesNumber;
    if(virusesNumber< TWO || virusesNumber > THOUSAND){
        first_generation.close();
        throw invalidInput();
    }

    vector<Virus*> ancestor;
    vector<Virus*> descendant;
    while(getline(first_generation,line)){ /*should be virusesNumber times*/
        cnt++;
        string str;
        index = line.find(space);
        string type = line.substr(0,index);
        line = line.substr(index+1,line.length());
        index = line.find(space);

        while(index != -1){
            tmp = line.substr(0,index);
            str = str+tmp;
            line = line.substr(index+1,line.length());
            index = line.find(space);
            if(index == -1)
                str = str+line;
        }
        int len = str.length();
        if(len != stringDimension){
            first_generation.close();
            throw invalidInput();
        }
        /**************************************/
        /*          make a new virus          */
        /**************************************/
        if(type == "s"){
            Virus *v1 = new Sars(type,str);
            ancestor.push_back(v1);
            Virus *v2 = new Sars(*v1);
            descendant.push_back(v2);
        }
        else if(type == "m"){
            Virus *v1 = new Mers(type,str);
            ancestor.push_back(v1);
            Virus *v2 = new Mers(*v1);
            descendant.push_back(v2);
        }
        else if(type == "c"){
            Virus *v1 = new Covid(type,str);
            ancestor.push_back(v1);
            Virus *v2 = new Covid(*v1);
            descendant.push_back(v2);
        }
        else{
            first_generation.close();
            throw invalidInput();
        }
    }

    if(cnt != virusesNumber){
        first_generation.close();
        throw invalidInput();
    }
    first_generation.close();
    this->ancestor = ancestor;
    this->descendant = descendant;
}

vector<Virus*> readFiles::getAncestor() const{
    return ancestor;
}

vector<Virus*> readFiles::getDescendant() const{
    return descendant;
}

string readFiles::getTarget() const{
    return target;
}

int readFiles::getTimeBeats() const{
    return timeBeats;
}

/*delete the ancestor here and the descendant in "simViruse"
because he make some change there so we can't delete that here*/
readFiles::~readFiles(){
    vector<Virus*>::iterator it; 
    for(it=ancestor.begin(); it != ancestor.end() ; it++ ){
        delete (*it);
    }
}