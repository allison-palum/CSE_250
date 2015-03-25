#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
 
using namespace std;

//find minimum value
int min(int first, int last) {
	int minimum = first;
	for (; first != last; first++) {
		if (first < minimum) minimum = first;
	}
	return minimum;
}

//find maximum value
int max(int first, int last) {
	int maximum = first;
	for (; first != last; first++) {
		if (first > maximum) maximum = first;
	}
	return maximum;
}

int main(int argc, char* argv[]) {
	int number;
	int sum;
	vector<int> vect;
	ifstream f(argv[1]);

	while (f >> number) {
		sum += number;
		vect.push_back(number);
	}

	f.close();

	//sort vector
	sort(vect.begin(), vect.end());

	int first = 0; //position of minimum value in vector
	int last = vect.size() - 1; //position of maximum value in vector
	int middle = (vect.size() - 1) / 2;

	int minimum = vect[first];
	int maximum = vect[last];
	int median = vect[middle];

	cout << minimum << " " << median << " " << maximum << endl;
}