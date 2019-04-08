// Matrix 
// Does not support matrix or vector multiplication
#ifndef __MAT_H__
#define __MAT_H__

#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>

template<class T>
struct mat {
    int m;
    int n;
    std::vector<T> x;
    
    mat() {
        m = 0;
        n = 0;
    }

    mat(int rows) {
        n = rows;
        m = rows;
        x.resize(n*m, 0);
    }
    
    mat(int rows, int cols) {
        m = rows;
        n = cols;
        x.resize(n*m, 0);
    }
    
    void fill(T value) {
        for (int i = 0; i < n*m; i++) x[i] = value;
    }

    T& operator () (int i, int j) {
        return x[i*n + j];
    }

    const T& operator () (int i, int j) const {
        return x[i*n + j];
    }

    void make_identity() {
        assert(m == n);
        fill(0);
        for (int i = 0; i < n*m; i += m+1) x[i] = 1;
    }
};

template<class T>
std::ostream& operator << (std::ostream& out, const mat<T>& A) {
    for (int i = 0; i < A.m; i++) {
        if (i) out << '\n';
        for (int j = 0; j < A.n; j++) {
            if (j) out << ' ';
            out << A(i, j);
        }
    }
}

#endif
