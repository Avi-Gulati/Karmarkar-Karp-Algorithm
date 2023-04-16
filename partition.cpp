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

long long karmarkar_karp(long long * arr, int length) {

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
    uniform_int_distribution<int> dist(0, 1);
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

int* random_move(int* sol, int length) {
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> dist1(0, length - 1);
    uniform_int_distribution<int> dist2(0, 1);
    // select two random indices i and j s.t. i!=j
    int i = dist1(generator);
    int j = dist1(generator);
    while (true) {
        int j = dist1(generator);
        if (i != j) {
            break;
        }
    }
    sol[i] = -1 * sol[i];
    int p = dist2(generator);
    if (p == 1) {
        sol[j] = -1 * sol[j];
    }
    return sol;
}

long long repeated_random_standard(long long* A, int length, int max_iter) {
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

long long hill_climb_standard(long long* A, int length, int max_iter) {
    long long sres = 0;
    long long s1res = 0;
    int* S = random_sol(length);
    sres = standard_residue(S, A, length);
    for (int i = 0; i < max_iter; i++) {
        int* S1 = random_move(S, length);
        s1res = standard_residue(S1, A, length);
        if (s1res < sres) {
            S = S1;
            sres = s1res;
        }
    }
    return sres;
}

long long simulated_anneal_standard(long long* A, int length, int max_iter) {
    std::random_device rd;
    std::mt19937 gen(rd());
    long long sres = 0;
    long long s1res = 0;
    long long s2res = 0;
    int* S = random_sol(length);
    sres = standard_residue(S, A, length);
    s2res = sres;
    for (int i = 0; i < max_iter; i++) {
        int* S1 = random_move(S, length);
        s1res = standard_residue(S1, A, length);
        if (s1res < sres) {
            S = S1;
            sres = s1res;
        } else {
            float p = exp((-1.*(s1res-sres))/(pow(10,10)*pow(0.8,floor(((float)i/300.)))));
            std::bernoulli_distribution d(p);
            if (d(gen)) { 
                S = S1;
                sres = s1res;
            } if (sres < s2res) {
                s2res = sres;
            }
        }
    }
    return s2res;
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
    int max_iter = 10000;
    switch(algorithm) {
        case 0:
            printf("%lli", karmarkar_karp(A, 100));
            break;
        case 1:
            printf("%lli", repeated_random_standard(A, 100, max_iter));
            break;
        case 2:
            printf("%lli", hill_climb_standard(A, 100, max_iter));
            break;
        case 3:
            printf("%lli", simulated_anneal_standard(A, 100, max_iter));
            break;
    }
    return 0;
}