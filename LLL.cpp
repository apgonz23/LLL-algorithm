// LLL algorithm
#include "LLL.h"
#include "vec.h"
#include "mat.h"
#include <iostream>
#include <cassert>

// LLL algorithm
basis_d LLL(const basis_d& input_basis, double alpha) {
    int n = input_basis.size();
    basis_d B(n);
    for (int i = 0; i < n; i++) {
        B[i] = input_basis[i];
    }

    basis_d Bstar(n);
    mat_d mu(n);
    double gamma[n];
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
            double prev_mu = mu(k,k-1);
            double delta = gamma[k] + prev_mu * prev_mu * gamma[k-1];
            mu(k,k-1) = prev_mu * gamma[k-1] / delta;
            gamma[k] = gamma[k] * gamma[k-1] / delta;
            gamma[k-1] = delta;
            for (int j = 0; j < k-1; j++) std::swap(mu(k,j), mu(k-1,j));
            for (int i = k+1; i < n; i++) {
                double temp_mu = mu(i,k);
                mu(i,k) = mu(i,k-1) - prev_mu * mu(i,k);
                mu(i,k-1) = mu(k,k-1) * mu(i,k) + temp_mu;
            }
            if (k > 1) k--;
        }
    }

    return B;
}

// Gram-Schmidt MU function
double mu(const vec_d& u, const vec_d& v) {
    return dot(u,v) / v.magnitude_squared();
}

// Orthogonalizes basis using Gram-Schmidt method
basis_d gram_schidt(const basis_d& B) {
    int n = B.size();
    basis_d Bstar(n);
    for (int k = 0; k < n; k++) Bstar[k] = B[k];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            Bstar[i] = Bstar[i] - mu(B[i], Bstar[j]) * Bstar[j];
        }
    }
    return Bstar;
}

// finds the vector with the smallest magnitude in the basis
vec_d shortest_vector(const basis_d& B) {
    int n = B.size();
    vec_d s = B[0];
    double mag = s.magnitude();
    for (int i = 1; i < n; i++) {
        if (B[i].magnitude() < mag) {
            mag = B[i].magnitude();
            s = B[i];
        }
    }
    return s;
}

// Prints a basis to standard output
void display_basis(const basis_d& B) {
    int n = B.size();
    for (int i = 0; i < n; i++) {
        std::cout << B[i] << std::endl;
    }
}

