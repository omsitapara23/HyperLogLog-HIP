#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../hyperloglog++.hpp"

using namespace hll;
using namespace std;


int main(){
    HyperLogLog hll(16);
    double size = 100000;
    srand (time(0));
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
    std::cout << "REAL UNIQUE: " << unique << std::endl; 

    std::cout << "Cardinality:" << cardinality << std::endl;
    std::cout << "ERROR: " << (1 - cardinality/unique)*100 << endl;

    return 0;
}