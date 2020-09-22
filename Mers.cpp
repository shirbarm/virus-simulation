#include "Mers.h"

void Mers::update(){
    double cnt = 0;
    double pm = 1/(double)length;
    while(cnt != length){
        if(str.at(cnt)=='A' || str.at(cnt)=='C' || str.at(cnt)=='G'){
            double r = ((double) rand() / (RAND_MAX));
            if(r < pm) {
                if(str.at(cnt)=='A'){
                    str.at(cnt) = 'T';
                    cnt++;
                    continue;
                }
                else if(str.at(cnt)=='C'){
                    str.at(cnt) = 'G';  
                    cnt++;
                    continue;
                } 
                else str.at(cnt) = 'C';
            }
        }
        cnt++;
    }
}