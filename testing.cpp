// Testing file
#include "LLL.h"
#include <iostream>

int main() {
    // Test basis 1
    basis_d B1 = {vec_d({1,1,1}), 
                  vec_d({-1,0,2}), 
                  vec_d({3,5,6})};
    
    std::cout << "B1:" << std::endl;
    display_basis(B1);
    vec_d shortest1 = shortest_vector(B1);
    std::cout << "Shortest vector in B1: " << shortest1 << std::endl;
    std::cout << "Magnitude of shortest in B1: " << shortest1.magnitude() << std::endl;
    basis_d S1 = LLL(B1, 0.75);
    std::cout << "reduced-B1:" << std::endl;
    display_basis(S1);
    shortest1 = shortest_vector(S1);
    std::cout << "Shortest vector in red-B1: " << shortest1 << std::endl;
    std::cout << "Magnitude of shortest in red-B1: " << shortest1.magnitude() << std::endl;
    
    std::cout << std::endl;
    std::cout << std::endl;
   
    // Test basis 2
    basis_d B2 = {vec_d({-2,7,7,-5}),
                  vec_d({3,-2,6,-1}),
                  vec_d({2,-8,-9,-7}),
                  vec_d({8,-9,6,-4})};

    std::cout << "B2:" << std::endl;
    display_basis(B2);
    vec_d shortest2 = shortest_vector(B2);
    std::cout << "Shortest vector in B2: " << shortest2 << std::endl;
    std::cout << "Magnitude of shortest in B2: " << shortest2.magnitude() << std::endl;
    basis_d S2 = LLL(B2, 0.75);
    std::cout << "reduced-B2:" << std::endl;
    display_basis(S2);
    shortest2 = shortest_vector(S2);
    std::cout << "Shortest vector in red-B2: " << shortest2 << std::endl;
    std::cout << "Magnitude of shortest in red-B2: " << shortest2.magnitude() << std::endl;
    // Expected output for reduced-B2:
    //  2  3  1  1
    //  2  0 -2 -4 
    // -2  2  3 -3
    //  3 -2  6 -1

}
