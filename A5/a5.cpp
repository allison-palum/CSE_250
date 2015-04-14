#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int findMedian(vector<int> &v) {
        int size = v.size();
        int median = v[(size / 2)];
        return median;
}//findMedian

int findMoM(vector<vector<int> > &vector2D) {
        vector<int> medians;
        int size = vector2D.size();
        for (int i = 0; i < size; i++) {
                int m = findMedian(vector2D[i]);
                medians.push_back(m);
        }
        return findMedian(medians);
}//findMoM

int medianOfMedians(const vector<int> &v, int k) {
        vector<vector<int> > vector2D;

        int count = 0;
        int countRow;
        while (count != (int)v.size()) {
                countRow = 0;
                vector<int> row;

                while ((countRow < 5) && (count < (int)v.size())) {
                        row.push_back(v[count]);
                        count++;
                        countRow++;
                }
                vector2D.push_back(row);
        }

        int m = findMoM(vector2D);
        vector<int> L1;
        vector<int> L2;
        vector<int> L3;

        //partition the list
        for (int i = 0; i < (int)vector2D.size(); i++) {
                for (int j = 0; j < (int)vector2D[i].size(); j++) {
                        if (vector2D[i][j] < m) {
                                L1.push_back(vector2D[i][j]);
                        }
                        else if (vector2D[i][j] == m) {
                                L2.push_back(vector2D[i][j]);
                        }
                        else {
                                L3.push_back(vector2D[i][j]);
                        }
                }
        }

        //recursive select based on size of L1, L2 and L3
        if (k <= (int)L1.size()) {
                return medianOfMedians(L1, k);
        }
        else if(k > ((int)L1.size() + (int)L2.size())) {
                return medianOfMedians(L3, k - (int)L1.size() - (int)L2.size());
        }
        else {
                return m;
        }

}//medianOfMedians

int main(int argc, char* argv[]) {
        int number;
        vector<int> vect;
        ifstream f(argv[1]);


        int maximum = -1;
        int minimum = -1;
        while (f >> number) {
                if (number > maximum || maximum == -1) maximum = number;
                if (number < minimum || minimum == -1) minimum = number;
                vect.push_back(number);
        }
        f.close();

        int median = medianOfMedians(vect, vect.size() / 2 + 1);

        cout << minimum << " " << median << " " << maximum << endl;
}//main
