#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
using namespace std;



// Thanks Chat GPT!
void findLargestAndSecondLargest(long long *arr, int size, long long& max1, int& max1Index, long long& max2, int& max2Index) {
    max1 = arr[0];
    max1Index = 0;
    max2 = arr[1];
    max2Index = 1;

    for (int i = 1; i < size; i++) {
        if (arr[i] > max1) {
            max2 = max1;
            max2Index = max1Index;
            max1 = arr[i];
            max1Index = i;
        } else if (arr[i] > max2) {
            max2 = arr[i];
            max2Index = i;
        }
    }
}



int karmarkar_karp(long long * arr, int length) {

    for (int i = 0; i < length - 1; i++) {
        long long max1;
        long long max2;
        int max1index;
        int max2index;
        
        findLargestAndSecondLargest(arr, length, max1, max1index, max2, max2index);
        arr[max1index] = max1 - max2;
        arr[max2index] = 0;
    }

    for (int i = 0; i < 100; i++) {
        if (arr[i] != 0) {
            return arr[i];
        }
    }
    return 0;
}

// generates random standard form solution of length "length"
int* random_sol(int length) {
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<long long> dist(0, 1);
    int* sol = new int[length];
    for (int i = 0; i < length; i++) {
        sol[i] = 1 - 2 * dist(generator);
    }
    return sol;
}

// calculates residue of standard form solution
long long standard_residue(int* sol, long long* A, int length) {
    long long sum = 0;
    for (int i = 0; i < length; i++) {
        sum += sol[i] * A[i];
    }
    return abs(sum);
}

// repeated_random algo for standard form solutions
int repeated_random(long long* A, int length, int max_iter) {
    long long sres = 0;
    long long s1res = 0;
    int* S = random_sol(length);
    sres = standard_residue(S, A, length);
    for (int i = 0; i < max_iter; i++) {
        int* S1 = random_sol(length);
        s1res = standard_residue(S1, A, length);
        if (s1res < sres) {
            S = S1;
            sres = s1res;
        }
    }
    return sres;
}



// partition flag algorithm inputfile
int main(int _argc, char *argv[]) {
    int flag = stoi(argv[1]);
    int algorithm = stoi(argv[2]);
    ifstream input(argv[3]);
    
    // initializes array A from input file
    long long A[100];
    for (int i = 0; i < 100; i++) {
        string val;
        getline(input, val);
        A[i] = stoll(val);
    }
    printf("%lli", karmarkar_karp(A, 100));
    return 0;
}