// Lattice
#ifndef __lattice_h__
#define __lattice_h__

#include <cassert>
#include <iostream>
#include "vec.h"
#include "mat.h"

template<class T>
struct basis {
    std::vector< vec<T> > B;
    int dim;
    
    basis() {
        dim = 0;
    }

    basis(int n) {
        dim = n;
        B.resize(n);
        for (int i = 0; i < n; i++) {
            B[i] = vec<T>(n);
        }
    }

    
    basis(std::vector< vec<T> > in) {
        B = in;
        dim = B.size();
    }
   
    const vec<T>& operator [] (int i) const {
        return B[i];
    }

    vec<T>& operator [] (int i) {
        return B[i];
    }

    // prints basis to standard output
    void display() {
        for (int i = 0; i < dim; i++) {
            std::cout << B[i] << std::endl;
        }
    }

    // returns the vector with the smallest magnitude in the basis
    vec<T> shortest() {
        vec<T> s = B[0];
        T mag = s.magnitude();
        for (int i = 1; i < dim; i++) {
            if (B[i].magnitude() < mag) {
                mag = B[i].magnitude();
                s = B[i];
            }
        }
        return s;
    }
};

// LLL algorithm
// Meant to be used with double or float
template<class T>
basis<T> LLL(const basis<T>& in_B, T alpha) {
    int n = in_B.dim;
    basis<T> B(n);
    for (int i = 0; i < n; i++) {
        B[i] = in_B[i];
    }

    basis<T> Bstar(n);
    mat<T> mu(n);
    T gamma[n];
    for (int i = 0; i < n; i++) {
        Bstar[i] = B[i];
        for (int j = 0; j < i; j++) {
            mu(i,j) = dot(B[i],Bstar[j]) / gamma[j];
            Bstar[i] = Bstar[i] - mu(i,j) * Bstar[j];
        }
        gamma[i] = Bstar[i].magnitude_squared();    
    }
    int k = 1;
    while (k < n) {
        // reduce(k, k-1)
        if (std::abs(mu(k,k-1)) > 0.5) {
            B[k] = B[k] - std::round(mu(k,k-1)) * B[k-1];
            for (int j = 0; j < k-1; j++) mu(k,j) -= std::round(mu(k,k-1)) * mu(k-1,j);
            mu(k,k-1) -= std::round(mu(k,k-1));
        }
        if (gamma[k] >= (alpha - mu(k,k-1)*mu(k,k-1)) * gamma[k-1]) {
            for (int i = k-2; i >= 0; i--) {
                // reduce(k, i)
                if (std::abs(mu(k,i)) > 0.5) {
                    B[k] = B[k] - std::round(mu(k,i)) * B[i];
                    for (int j = 0; j < i; j++) mu(k,j) -= std::round(mu(k,i)) * mu(i,j);
                    mu(k,i) -= std::round(mu(k,i));
                }
            }
            k++;
        } else {
            // exchange 
            std::swap(B[k], B[k-1]);
            T prev_mu = mu(k,k-1);
            T delta = gamma[k] + prev_mu * prev_mu * gamma[k-1];
            mu(k,k-1) = prev_mu * gamma[k-1] / delta;
            gamma[k] = gamma[k] * gamma[k-1] / delta;
            gamma[k-1] = delta;
            for (int j = 0; j < k-1; j++) std::swap(mu(k,j), mu(k-1,j));
            for (int i = k+1; i < n; i++) {
                T temp_mu = mu(i,k);
                mu(i,k) = mu(i,k-1) - prev_mu * mu(i,k);
                mu(i,k-1) = mu(k,k-1) * mu(i,k) + temp_mu;
            }
            if (k > 1) k--;
        }
    }

    return B;
}

// MU function
template<class T>
T mu(const vec<T>& u, const vec<T>& v) {
    return dot(u,v) / v.magnitude_squared();
}

// Orthogonalizes basis using Gram-Schmidt method
template<class T>
basis<T> gram_schmidt(basis<T> B) {
    int n = B.dim;
    basis<T> Bstar(n);
    for (int k = 0; k < n; k++) Bstar[k] = B[k];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            Bstar[i] = Bstar[i] - mu(B[i], Bstar[j]) * Bstar[j];
        }
    }
    return Bstar;
}

#endif
