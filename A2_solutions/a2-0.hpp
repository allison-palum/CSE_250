#ifndef A2_HPP
#define A2_HPP

#include <algorithm> // for copy

class A2 {
public:
    explicit A2(int n = 0, int m = 0) : n_(n), m_(m) {
      A_ = new double[n_ * m_];
    }

    A2(const A2& A) {
      n_ = A.n_;
      m_ = A.m_;
      A_ = new double[n_ * m_];
      std::copy(A.A_, A.A_ + n_ * m_, A_);
    }

    A2& operator=(const A2& A) {
      if (this == &A) return *this;
      delete[] A_;
      n_ = A.n_;
      m_ = A.m_;
      A_ = new double[n_ * m_];
      std::copy(A.A_, A.A_ + n_ * m_, A_);
      return *this;
    }

    ~A2() { delete[] A_; }

    double rsum(int n) const {
        double S = 0.0;
        for (int i = 0; i < m_; ++i) S += (*this)(n, i);
        return S;
    }

    double csum(int m) const {
        double S = 0.0;
        for (int i = 0; i < n_; ++i) S += (*this)(i, m);
        return S;
    }

    double& operator()(int i, int j) { return A_[i * m_ + j]; }

    const double& operator()(int i, int j) const { return A_[i * m_ + j]; }

private:
    int n_;
    int m_;
    double* A_;
}; // class A2

#endif // A2_HPP
