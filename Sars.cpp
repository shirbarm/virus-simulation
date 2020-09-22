#include "Sars.h"

void Sars::update(){
    int cnt = 0;
    double pm = 0.37;
    while(cnt != length){
        if(str.at(cnt)=='A' || str.at(cnt)=='T'){
            double r = ((double) rand() / (RAND_MAX));
            if(r < pm) {
                if(str.at(cnt)=='A'){
                    str.at(cnt) = 'G';
                    cnt++;
                    continue;
                }
                else str.at(cnt) = 'A';
            }
        }
        cnt++;
    }
}