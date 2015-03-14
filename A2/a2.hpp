#ifndef A2_HPP
#define A2_HPP

#include <algorithm>
#include <cassert> //for assert()

class A2 {
public:
	int N, M;
	A2() {
		pointer = new double[0];
	}	
	A2(int x, int y) : N(x), M(y) {
		if (arrSize == 0) { pointer = 0; }
		else { pointer = new double[arrSize]; }
	}//A2

	A2(const A2& A) : arrSize(A.arrSize) {
		if (arrSize == 0) { pointer = 0; }
		else {
			pointer = new double[arrSize];
			std::copy(A.pointer, A.pointer + arrSize, pointer);
		}
	}//A2 copy

	A2& operator=(const A2& A) {
		if (this != &A) {
			std::size_t sizeNew = A.arrSize;
			double* pointerNew = sizeNew ? new double[sizeNew]() : 0;
			std::copy(A.pointer, A.pointer + sizeNew, pointerNew);

			delete[] pointer;
			arrSize = sizeNew;
			pointer = pointerNew;
		}
		return *this;
	} //operator=
	
	double& operator()(const int nRow, const int mCol)const { 
		return pointer[nRow*M + mCol];
	} //operator()

	double rsum(int n) {
		int rowAlgo = ((n*M) + N);
		double sum = 0.0;
		for (int row = n*M; row < rowAlgo; row++) {
			sum = sum + pointer[row];
		}
		return sum;
	} // rsum

	double csum(int m) {
		int colAlgo = (((N - 1)*M) + (m + 1));
		double sum = 0.0;
		for (int col = m; col < colAlgo; col++) {
			sum = sum + pointer[col];
		}
		return sum;
	} // csum
	
	~A2() {
		delete[] pointer;
	} //destructor

private:
	int arrSize;
	double* pointer;
}; // class A2
#endif // A2_HPP