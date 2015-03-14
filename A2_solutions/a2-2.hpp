#ifndef A2_HPP
#define A2_HPP

#include <vector>

class A2 {
public:
    explicit A2(int n = 0, int m = 0) : n_(n), m_(m), A_(n * m) { }

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
    std::vector<double> A_;
}; // class A2

#endif // A2_HPP
