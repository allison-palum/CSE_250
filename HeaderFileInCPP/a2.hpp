#ifndef A2_HPP
#define A2_HPP

#include <algorithm>
#include <cassert> //for assert()
#include <vector>

using namespace std;

class A2 {
public:
	A2(int x = 0, int y = 0) : N(x), M(y), A_(x*y) { }
	
	double& operator()(int nRow, int mCol) { 
		return A_[nRow*M + mCol];
	} //operator()

	const double& operator()(int nRow, int mCol) const {
		return A_[nRow*M + mCol];
	}

	double rsum(int n) {
		double sum = 0.0;
		for (int i = 0; i < M; i++) {
			sum = sum + (*this)(n, i);
		}
		return sum;
	} // rsum

	double csum(int m) {
		double sum = 0.0;
		for (int i = 0; i < N; i++) {
			sum = sum + (*this)(i, m);
		}
		return sum;
	} // csum

private:
	vector<double> A_;
	int N, M;
}; // class A2
#endif // A2_HPP