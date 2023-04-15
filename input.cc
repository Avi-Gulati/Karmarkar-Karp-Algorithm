#include <iostream>
#include <fstream>
#include <random>
#include <string>
using namespace std;

int main() {
    random_device rand_dev;
    mt19937 generator(rand_dev());
    long long upper_bound = pow(10, 12);
    uniform_int_distribution<long long> dist(1, upper_bound);
    
    ofstream outfile;
    outfile.open("input.txt");
    for (int i = 0; i < 100; i++) {
            outfile << to_string(dist(generator));
            outfile << "\n";
    }
    outfile.close();
    return 0;
}