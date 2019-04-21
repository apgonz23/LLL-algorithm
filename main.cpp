// Main functionality for testing different alpha values on multiple basis
#include "LLL.h"
#include "vec.h"
#include "mat.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <cstring>


// Used to store the dimension and the alpha for that dimension together
struct alphaData {
    int dimension;
    double alpha;
};


// Function declarations
std::vector<double> create_test_alphas(double start, double end, double step);
double find_best_alpha(const basis_d& B, const std::vector<double>& A);
double calc_expected_alpha(const char* filename, const std::vector<double>& A, int n);
std::vector<alphaData> create_expected_alpha_list(const std::vector<double>& A, int min_dim, int max_dim);
void save_alphas(const char* filename, const std::vector<alphaData>& alpha_list);


/////////////////////
/// MAIN FUNCTION ///
/////////////////////
int main(int argc, char** argv) {
    // ensures proper usage
    if (argc != 4) {
        std::cout << "usage: ./LLL <output_file> <min_dim> <max_dim>" << std::endl;
        return 0;
    }

    std::string filename = argv[1];
    int min_dim = std::stoi(argv[2], nullptr, 10); 
    int max_dim = std::stoi(argv[3], nullptr, 10);
    
    // list of alpha values that will be tested in the LLL algorithm
    std::vector<double> test_alphas = create_test_alphas(0.35, 0.95, 0.05);

    std::cout << "computing..." << std::endl; 
    std::vector<alphaData> expected_alphas = create_expected_alpha_list(test_alphas, min_dim, max_dim);
    save_alphas(filename.c_str(), expected_alphas);
    std::cout << "done." << std::endl;

    return 0;

}


// returns a list of alphas to use for testing 
// from [start, end] inclusive with the specified step size
std::vector<double> create_test_alphas(double start, double end, double step) {
    std::vector<double> test_alphas;
    for (double i = start; i <= end; i += step) 
        test_alphas.push_back(i);

    return test_alphas;
}


// Takes in a basis B and a list of alpha values A
// It LLL reduces the basis for each alpha value 
// and it returns the smallest alpha value that produces the shortest vector
// out of all the alpha reduced basis, alpha(L). [optimal value of reduction parameter]
double find_best_alpha(const basis_d& B, const std::vector<double>& A) {
    double alpha = std::numeric_limits<double>::max();
    double min_mag = std::numeric_limits<double>::max();
    basis_d Bprime(B.size());
    
    for (double a : A) {
        // calculates LLL
        Bprime = LLL(B, a);
        // finds the magnitude of the shortest vector in Bprime 
        double curr_mag = shortest_vector(Bprime).magnitude();
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
// It finds the expected alpha for the set of basis S
// expected_alpha = (1 /|S|) * sum(alpha(L)), for each L in S
double calc_expected_alpha(const char* filename, const std::vector<double>& A, int n) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<double> calculated_alphas;

    basis_d B(n);
    int k = 0;
    std::string line;
    while (getline(infile, line)) {
        if (line[0] == 'b') {
            if (k == 0) continue; // does nothing on the first b in the file
            double atemp = find_best_alpha(B, A);
            calculated_alphas.push_back(atemp);
            k = 0;
        } else {
            // assigns values for basis B
            std::stringstream ss(line);
            vec<double> row(n);
            for (int i = 0; i < n; i++) {
                ss >> row[i];
            }
            B[k] = row;
            k++;
        }
    }
    infile.close();

    double expected_alpha = 0;
    for (int i = 0; i < calculated_alphas.size(); i++) {
        expected_alpha += calculated_alphas[i];
    }
    if (calculated_alphas.size() != 0) expected_alpha /= calculated_alphas.size();
    
    return expected_alpha;
}


// Reads from files data/n[dim].txt and calculates the expected alpha for each file
std::vector<alphaData> create_expected_alpha_list(const std::vector<double>& A, int min_dim, int max_dim) {
    std::vector<alphaData> output_list;
    for (int i = min_dim; i <= max_dim; i++) {
        std::cout << "calculating " << i << " x " << i << " ... ";
        
        std::string file = "data/n" + std::to_string(i) + ".txt";
        double temp_alpha = calc_expected_alpha(file.c_str(), A, i);
        output_list.push_back({i, temp_alpha});
        
        std::cout << "finished" << std::endl;
    }
    return output_list;
}


// writes expected alpha values to the input filename
void save_alphas(const char* filename, const std::vector<alphaData>& alpha_list) {
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        std::cout << "saving to disk ... ";
        outfile << "dim\t:\talpha\n";
        for (int i = 0; i < alpha_list.size(); i++) 
            outfile << alpha_list[i].dimension << "\t:\t" << alpha_list[i].alpha << "\n"; 
        outfile.close();
        std::cout << "finished" << std::endl;
    } else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
}

