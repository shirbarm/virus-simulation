#include <fstream>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "simVirus.h"
#include "readFiles.h"
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    if (argc != 3){
        cerr << "error: Invalid input." << endl;
        exit(EXIT_FAILURE);
    }
    string configFile=argv[1];
    string firstGenerationFile=argv[2];
    readFiles read(configFile,firstGenerationFile);

    try{
        read.openConfig();
        read.openFirstGeneration();
    }
    catch(readFiles::fileNotOpen &e1){
		e1.PrintError();
        exit(EXIT_FAILURE);
	}
	catch(readFiles::invalidInput &e2){
		e2.PrintError();
        exit(EXIT_FAILURE);
	}
    string target = read.getTarget();
    int timeBeats = read.getTimeBeats();
    vector<Virus*> ancestor = read.getAncestor();
    vector<Virus*> descendant = read.getDescendant();
    simVirus simWorld(ancestor,descendant,target,timeBeats);

    if(read.getTimeBeats()==0){
        simWorld.printAncestor();
        return 0;
    }
    
    int time = 0;
    while(time < timeBeats && !simWorld.hasMatch()){
        simWorld.updateSingel();
        simWorld.sortByPowerful();
        simWorld.updateGroup();
        time++;
    }

    simWorld.sortByPowerful();
    simWorld.printDescendant();
    cout << endl;
    simWorld.printAncestor();
    cout << endl;
    simWorld.printStronger();

    return 0;
}