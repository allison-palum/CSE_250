/***
 *  $Id$
 **
 *  File: a1.cpp
 *  Author: Jaroslaw Zola <jzola@buffalo.edu>
 */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>


// convert DNA to digit (base4)
inline int to_digit(char c) {
    switch (c) {
      case 'A': return 0;
      case 'C': return 1;
      case 'G': return 2;
      case 'T': return 3;
    }
    return 0;
} // to_digit


void count_kmers(const std::string& s, int k,
                 std::vector<int>& C,
                 std::vector<std::string>& S) {
    // check if we can enumerate any k-mers
    int l = s.size();
    if (l < k) return;

    int end = l - k + 1;

    // this is O(l) algorithm to compute indexes of consecutive k-mers
    // consider decimal number 3527 and say we are interested
    // in 3-mers, then: 527 = (352 - 3*10^2) * 10 + 7
    // we are using exactly the same idea just in base4 system

    // first k-mer
    int v = to_digit(s[k - 1]);
    for (int i = 0; i < k - 1; ++i) {
        v += to_digit(s[i]) * (1 << ((k - i - 1) << 1));
    }

    if (C[v] == 0) S[v] = s.substr(0, k);
    C[v]++;

    // then all following k-mers
    int b = 1 << ((k - 1) << 1);

    for (int i = 1; i < end; ++i) {
        v = (v - b * to_digit(s[i - 1])) * 4 + to_digit(s[i + k - 1]);
        if (C[v] == 0) S[v] = s.substr(i, k);
        C[v]++;
    }
} // count_kmers


int main(int argc, char* argv[]) {
    if (argc != 2) return -1;

    int k = 0;
    int m = 0;

    // open input file and read k and m
    std::ifstream f(argv[1]);
    if (!f) return -1;

    f >> k >> m;

    if (!f) {
        std::cout << "error" << std::endl;
        return -1;
    }

    // check correctness
    if ((k < 3) || (k > 10)) {
        std::cout << "error" << std::endl;
        return -1;
    }

    if (m < 2) {
        std::cout << "error" << std::endl;
        return -1;
    }

    // just in case 4^x = 2^(2*x)
    int n = 1 << (k << 1); // number of possible k-mers

    // allocate count array

    // I am using std::vector<T> for convenience
    // we could use simple dynamic memory array as well:
    // int* C = new int[n];
    // and corresponding: delete[] C; after print counts

    std::vector<int> C(n, 0); // here we will store k-mer counts
    std::vector<std::string> S(n); // and here k-mers (because I am lazy)

    // now we can read sequences and do counting
    std::string s;

    for (int i = 0; i < m; ++i) {
        s = "";
        f >> s;
        if (!f) {
            std::cout << "error" << std::endl;
            return -1;
        }
        count_kmers(s, k, C, S); // here we go!
    } // for i

    // one more line???
    s = "";
    f >> s;
    if (s.empty() == false) {
        std::cout << "error" << std::endl;
        return -1;
    }

    // close file
    f.close();

    // print counts
    for (int i = 0; i < n; ++i) {
        if (C[i] > 0) {
            std::cout << S[i] << " " << C[i] << "\n";
        }
    }

    return 0;
} // main
