#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

map<string, int> names_map;
const string _alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

struct suggestion {
	string name;
	int freq;
} _suggestion;

string deletechar(string s, int index) {
	return s.substr(0, index) + s.substr(index + 1);
}

void checkSuggestion(string s) {
	if (names_map.find(s) != names_map.end()) {
		if (names_map[s] > _suggestion.freq) {
			_suggestion.name = s;
			_suggestion.freq = names_map[s];
		}
		else if (names_map[s] == _suggestion.freq) {
			if (s < _suggestion.name) {
				_suggestion.name = s;
				_suggestion.freq = names_map[s];
			}
		}
	}
}

void checkDeletion(string s) {
	string temp;
	for (int i = 0; i < s.size(); i++) {
		temp = deletechar(s, i);
		checkSuggestion(temp);
	}
}

void checkInsertion(string s) {
	string temp;
	for (int i = 0; i < _alpha.size(); i++) {
		for (int j = 0; j < s.size(); j++) {
			temp = s.substr(0, j) + _alpha[i] + s.substr(j);
			checkSuggestion(temp);
		}
		//check appending character to the end of the string
		temp = s + _alpha[i];
		checkSuggestion(temp);
	}
}

void checkSub(string s) {
	string temp;
	for (int i = 0; i < _alpha.size(); i++) {
		for (int j = 0; j < s.size() - 1; j++) {
			temp = s.substr(0, j) + _alpha[i] + s.substr(j + 1);
			checkSuggestion(temp);
		}
		//check appending character to the string - 1
		temp = s.substr(0, s.size() - 1) + _alpha[i];
		checkSuggestion(temp);
	}
}

bool editDistOneFind(string s) {
	_suggestion.name = "";
	_suggestion.freq = 0;
	checkDeletion(s);
	checkInsertion(s);
	checkSub(s);
	if (_suggestion.freq != 0) {
		return true;
	}
	return false;
}

int main(int argc, char* argv[]) {
	fstream f(argv[1]);
	string name;
	int freq;
	while (f >> name >> freq) {
		names_map[name] = freq;
	}
	string s;
	while (cin >> s) {
		//if string is found
		if (names_map.find(s) != names_map.end()) {
			cout << s << " " << names_map[s] << endl;
			names_map[s]++;
		}
		//if string is not found
		else if (editDistOneFind(s)) {
			cout << _suggestion.name << " " << _suggestion.freq << endl;
		}
		//if string is not found && edit distance > 1
		else {
			cout << "-" << endl;
			names_map[s] = 1;
		}
	}
	return 0;
} //main