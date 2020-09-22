#ifndef readFiles_h_
#define readFiles_h_

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include<string>
#include "simVirus.h"
#define TWO 2
#define THREE 3
#define THOUSAND 1000
#define TEN_THOUSAND 10000
using namespace std;


class readFiles{ 
public:
    readFiles(string configFile,string firstGenerationFile);
    virtual ~readFiles();
    void openConfig();
    void openFirstGeneration();
    string getTarget() const;
    int getTimeBeats() const;
    vector<Virus*> getAncestor() const;
    vector<Virus*> getDescendant() const;

    /* exception classes */
	class fileNotOpen {
	public:
		fileNotOpen(string name):fileName(name){}
		virtual void PrintError() const{
			cout << "error: " << fileName << " does not exist or cannot be processed." << endl;
		}
	private:
		string fileName;
	};

    class invalidInput {
	public:
		invalidInput(){}
		virtual void PrintError() const{
			cout << "error: invalid input." << endl;
		}
	};

private:
    string configFile;
    string firstGenerationFile;
    string target;
    int timeBeats;
    int stringDimension;
    vector<Virus*> ancestor;
    vector<Virus*> descendant;
}; 


#endif /*Virus_h_*/