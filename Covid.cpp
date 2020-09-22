#include "Covid.h"

void Covid::update(){
    double cnt = 0;
    double pm = 2/(double)length;
    while(cnt != length){
        if(str.at(cnt)=='T' || str.at(cnt)=='C' || str.at(cnt)=='G'){
            double r = ((double) rand() / (RAND_MAX));
            if(r < pm) {
                if(str.at(cnt)=='T'){
                    str.at(cnt) = 'A';
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