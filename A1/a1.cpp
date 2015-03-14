//File: a1.cpp

#include <fstream> //access to files
#include <iostream> //input from keyboard
#include <cmath> //for pow function
#include <stdlib.h> //for atoi

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "error" << std::endl;
		return -1; //error, too few args
	}

	std::ifstream f;
	std::string s;
	int numOfLines = 0;
	f.open(argv[1]); //open file specified by argv[1]
	std::getline(f, s);
	int size_ = s.size();
	if (size_ < 3) { std::cout << "error" << std::endl; return -2; }
	while (!f.eof()) {
		numOfLines = numOfLines + 1;
		std::getline(f, s);
	}
	int actualM = numOfLines - 1;

	f.close();
	f.open(argv[1]);
	int nonNumber = 0;
	std::getline(f, s);
	int stringLength = s.length();
	for (int a = 0; a < stringLength; a++) {
		if (s[a] == ' ') { nonNumber = a; break; }
	}

	int kValue;
	std::string kmerString = s.substr(0, nonNumber);
	kValue = atoi(kmerString.c_str());
	int mValue;
	std::string mString = s.substr(nonNumber + 1);
	mValue = atoi(mString.c_str());

	int power = pow(4, kValue);
	int dna_sequences[power];
	for (int b = 0; b < power - 1; b++) {
		dna_sequences[b] = 0;
	}

	if (!f) { std::cout << "file does not exist!\n"; return -2; }
	if (kValue < 3) { std::cout << "error" << std::endl; return -2; }
	if (kValue > 10) { std::cout << "error" << std::endl; return -2; }
	if (mValue <= 1) { std::cout << "error" << std::endl; return -2; }
	if (mValue != actualM) { std::cout << "error" << std::endl; return -2; }

	for (int c = 0; c < mValue; c++) {
		f >> s;
		int size = s.size();
		if (kValue > size) { f >> s; }
		//std::string dna[size];
		for (int d = 0; d < size - (kValue - 1); d++) {
			std::string kmer = s.substr(d, kValue);
			int kmerLength = kmer.length();
			//std::cout << "newkmer..." << std::endl;
			//std::cout << "Kmer: "+ kmer << std::endl;
			std::string kmerBaseFour = "";
			for (int e = 0; e < kmerLength; e++) {
				if (kmer[e] == 'A') { kmerBaseFour = kmerBaseFour + '0'; }
				else if (kmer[e] == 'C') { kmerBaseFour = kmerBaseFour + '1'; }
				else if (kmer[e] == 'G') { kmerBaseFour = kmerBaseFour + '2'; }
				else if (kmer[e] == 'T') { kmerBaseFour = kmerBaseFour + '3'; }
			}
			//std::cout << "BaseFour: "+kmerBaseFour << std::endl;
			int kmerDecimal = 0;
			for (int f = kValue - 1; f >= 0; f--) {
				int kmerNum = (kmerBaseFour[f] - '0');
				int expo = pow(4, ((kValue - f) - 1));
				kmerDecimal = (kmerDecimal + (kmerNum*expo));
			}
			//std::cout << "DecimalIndex: "+kmerDecimal << std::endl;
			dna_sequences[kmerDecimal] = dna_sequences[kmerDecimal] + 1;
			//std::cout << dna_sequences[kmerDecimal] << std::endl;
		}
	}
	for (int g = 0; g < power - 1; g++) {
		if (dna_sequences[g] != 0) {
			int baseFour = g;
			std::string finalKmer = "";
			int temp = kValue;
			while (temp > 0) {
				int mod = baseFour % 4;
				//std::cout << mod << std::endl;
				if (mod == 0) { finalKmer = finalKmer + 'A'; }
				if (mod == 1) { finalKmer = finalKmer + 'C'; }
				if (mod == 2) { finalKmer = finalKmer + 'G'; }
				if (mod == 3) { finalKmer = finalKmer + 'T'; }
				baseFour = baseFour / 4;
				temp--;
			}
			std::cout << finalKmer;
			std::cout << " ";
			std::cout << dna_sequences[g] << std::endl;
		}
	}
	f.close();
	return 0;
}