// main
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include "lattice.h"
#include "vec.h"
#include "mat.h"

struct alpha_data {
    int dim;
    double alpha;
};

// Takes in a basis B and a list of alpha values A
// It LLL reduces the basis for each alpha value 
// and it returns the smallest alpha value that produces the shortest vector
// out of all the alpha reduced basis, alpha(L). [optimal value of reduction parameter]
double alpha4lattice(const basis<double>& B, const std::vector<double>& A) {
    double alpha = std::numeric_limits<double>::max();
    double min_mag = std::numeric_limits<double>::max();
    basis<double> Bprime(B.dim);
    
    for (double a : A) {
        Bprime = LLL(B, a);
        double curr_mag = Bprime.shortest().magnitude();
        if (curr_mag < min_mag) {
            alpha = a;
            min_mag = curr_mag;
        } else if (curr_mag == min_mag && a < alpha) {
            alpha = a;
        }
    }
    return alpha;
}

// Takes in a file containing a list of (nxn) basis and a list of alpha values
// It finds the expected alpha for the set of basis S.
// expected_alpha = (1 /|S|) * sum(alpha(L)), for each L in S
double expected_alpha(const char* filename, const std::vector<double>& A, int n) {
    std::vector<double> alpha_vals;
    
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    basis<double> B(n);
    int k = 0;
    while (getline(infile, line)) {
        if (line[0] == 'b') {
            if (k == 0) continue; // does nothing on the first b in the file
            double temp_a = alpha4lattice(B, A);
            alpha_vals.push_back(temp_a);
            k = 0;
        } else {
            std::stringstream ss(line);
            vec<double> temp(n);
            for (int i = 0; i < n; i++) {
                ss >> temp[i];
            }
            B[k] = temp;
            k++;
        }
    }
    infile.close();

    double exp_alpha = 0;
    for (int i = 0; i < alpha_vals.size(); i++) {
        exp_alpha += alpha_vals[i];
    }
    if (alpha_vals.size() != 0) exp_alpha /= alpha_vals.size();
    
    return exp_alpha;
}

//
std::vector<alpha_data> expected_alpha_list(const std::vector<double>& A, int max_dimension) {
    std::vector<alpha_data> alpha_list;
    for (int i = 3; i <= max_dimension; i++) {
        std::string file = "data/n" + std::to_string(i) + ".txt";
        double temp_a = expected_alpha(file.c_str(), A, i);
        alpha_list.push_back({i, temp_a});
    }
    return alpha_list;
}

//
void write_alphas(const char* filename, const std::vector<alpha_data>& alpha_list) {
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        outfile << "dim : alpha\n";
        for (int i = 0; i < alpha_list.size(); i++) {
            outfile << alpha_list[i].dim << " : " << alpha_list[i].alpha << "\n"; 
        }
        outfile.close();
    } else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
}

// MAIN FUNCTION
int main() {
    std::cout << "computing..." << std::endl;

    std::vector<double> A = {0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95};
    std::vector<alpha_data> exp_alphas = expected_alpha_list(A, 5);
    write_alphas("expected_alphas.txt", exp_alphas);
    
    std::cout << "done." << std::endl;

    //std::cout << "expected alpha: " << expected_alpha("data/n3.txt", A, 3) << std::endl;
    
    /*
    basis<double> base(4);
    vec<double> v1({-2,7,7,-5});
    vec<double> v2({3,-2,6,-1});
    vec<double> v3({2,-8,-9,-7});
    vec<double> v4({8,-9,6,-4});
    base[0] = v1; base[1] = v2; base[2] = v3; base[3] = v4;

    std::cout << "B" << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << base[i] << std::endl;
    }
    std::cout << base.shortest().magnitude() << std::endl;
 
    basis<double> bp(4);
    bp = LLL(base, .75);
    std::cout << "Bp" << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << bp[i] << std::endl;
    }
    std::cout << bp.shortest().magnitude() << std::endl;
    
    basis<double> bp2(4);
    bp2 = LLL(base, .6);
    std::cout << "Bp2" << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << bp2[i] << std::endl;
    }
    
    std::cout << bp2.shortest().magnitude() << std::endl;
    */

    return 0;
}

