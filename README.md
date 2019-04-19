# LLL-algorithm
The LLL algorithm is used for lattice basis reduction and has many practical applications in integer programming, cryptography, and other areas.

The algorithm is implemented in the LLL header and cpp files. There is a python script for generating new bases in the data folder.

Example usage:
 - ./generate_basis.py -d 3 10 1000
 - ./LLL.exe "expected_alphas.txt" 3 10
 - ./graph_alphas.py "expected_alphas.txt"

The above commands create 10 files with 1000 bases each (one for 3x3 bases, 4x4 bases, ... , 12x12 bases). Then they are reduced with the LLL algorithm. The resulting expected alphas (the average of the best alpha for each individual basis in the set) are written to the file "expected_alphas.txt". Then the values are graphed on a scatter plot.

The purpose of this program is to observe the impact that different alpha values may have on the basis reduction for lattices of different dimensions.
