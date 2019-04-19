// LLL algorithm
#ifndef __LLL_H__
#define __LLL_H__

#include <iostream>
#include <vector>
#include "vec.h"

typedef std::vector< vec<double> > basis_d;

// LLL algorithm
basis_d LLL(const basis_d& in_basis, double alpha);

// Gram-Schmidt MU function
double mu(const vec_d& u, const vec_d& v);

// Orthogonalizes basis using Gram-Schmidt method
basis_d gram_schidt(const basis_d& B);

// finds the vector with the smallest magnitude in the basis
vec_d shortest_vector(const basis_d& B); 

// Prints a basis to standard output
void display_basis(const basis_d& B);

#endif
