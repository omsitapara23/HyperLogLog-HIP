#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../hyperloglog++.hpp"

using namespace hll;
using namespace std;


int main(){
    std::ofstream file1("hllpp-1m-5m.csv");

    
    for(int size = 1000000; size <= 5000000; size += 100000){
        double errornormal = 0;
        double maxerror = 0;
        for(int iter = 0; iter < 100; iter++){
            HyperLogLog hll(16);
            srand (iter);
            int unique = 0;
            for(int i = 0; i < size; i++){
                
                string curr = "userid" + to_string(i);
                int rd = rand() % 10;
                if(rd < 7) {
                unique++;
                hll.add(curr);
                } else if ( rd >= 7 or rd <= 8) {
                hll.add(curr);
                unique++;
                i+=1;
                } else {
                hll.add(curr);
                unique++;
                i+=2;
                }
            }
            double cardinality = hll.estimate();
            double currerror = abs(1-cardinality/unique);
            errornormal += currerror;
            maxerror = max(maxerror, currerror*100);
        }
        
        file1 << size << "," << errornormal << "," << maxerror << endl;


    }

    file1.close();
    return 0;
}