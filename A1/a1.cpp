//File: a1.cpp

#include <fstream> //access to files
#include <iostream> //input from keyboard
#include <cmath> //for pow function
#include <stdlib.h> //for atoi
#include <string>
#include <vector>
using namespace std;

static bool debug = false;

inline int toBaseFour(char ch) {
	switch (ch) {
//	case 'A': return 0;
	case 'C': return 1;
	case 'G': return 2;
	case 'T': return 3;
	default: return 0; //captures A
	}
}

int kmertoDecimal(int kValue, std::string kmer) {
	int temp = 0;
	for (int z = kValue-1; z >= 0; z--) {
		temp = temp + pow(4, (kValue-z-1))* toBaseFour(kmer[z]);
	}
	return temp;
}

int main(int argc, char* argv[]) {

	if (argc < 2) {
		cout << "error: no file input" << endl;
		return -1; //error, too few args
	}

	ifstream f;
	string s;
	int numOfLines = 0;
	int kValue;
	int mValue;
	
	f.open(argv[1]); //open file specified by argv[1]
	if (!f) { cout << "file does not exist!\n" << endl; return -2; }
	else f >> kValue >> mValue;
	if (kValue < 3) { cout << "error: kVlaue less than 3" << endl; return -2; }
	if (kValue > 10) { cout << "error: kValue greater than 10" << endl; return -2; }
	if (mValue <= 1) { cout << "error: mValue less than or equal to 1" << endl; return -2; }

	if (debug) { cout << "The k value is: " << kValue << endl; }

	const int power = pow(4, kValue);
	int* dna_sequences = new int[power];
	
	vector<string> kmer_sequences(power);

	for (int b = 0; b < power - 1; b++) {
		dna_sequences[b] = 0;
	}

	for (int c = 0; c < mValue; c++) {
		f >> s;
		if (!f) { cout << "error: # of lines less than mValue" << endl; return -2; }
		int size = s.size();
		if (kValue > size) { f >> s; }

		for (int d = 0; d < size - (kValue - 1); d++) {
			string kmer = s.substr(d, kValue);
			int kmerDecimal = kmertoDecimal(kValue, kmer);
			dna_sequences[kmerDecimal] = dna_sequences[kmerDecimal] + 1;
			if (kmer_sequences[kmerDecimal].empty()) { kmer_sequences[kmerDecimal] = kmer; }
		}
	}

	char* finalKmer = new char[kValue + 1];
	finalKmer[kValue] = '\0';
	for (int g = 0; g < power - 1; g++) {
		if (dna_sequences[g] != 0) {
			cout << kmer_sequences[g] << " " << dna_sequences[g] << endl;
		}
	}
	delete[] finalKmer;
	delete[] dna_sequences;
	f.close();
	return 0;
}