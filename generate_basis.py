# Functions for producing testing data
# Generates the specified number of basis for each dimension 
# starting at the (min_dim x min_dim) all the way to (max_dim x max_dim)
# usage: ./generate_basis.py [-d/-s] min_dim max_dim num_of_basis
# using -s may speed up processing for basis of higher dimensions
# using -d ensures that all the bases created are linearly independent

import sys
import numpy as np

# generates k number of nxn matrices and writes them to a file
def generate_matrices(n, k, check_determinant=True):
    with open('data/n'+str(n)+'.txt', 'w') as f:
        for i in range(k):
            det = 0
            while (det == 0):
                M = np.random.randint(-100, 100, size=(n,n))
                det = np.linalg.det(M)

            f.write('b\n')
            for j in range(n):
                for h in range(n):
                    if (h):
                        f.write(' ')
                    f.write(str(M[j][h]))
                f.write('\n')

# creates a file with multiple basis from (3x3) to (max_dim x max_dim)
def create_basis_files(min_dim, max_dim, k, check=True):
    for i in range(min_dim, max_dim+1):
        generate_matrices(i, k, check)

# checks to ensure call is correct
if (len(sys.argv) == 5 and (sys.argv[1] == '-d' or sys.argv[1] == '-s')):
    print('writing to files...')
    min_dim = int(sys.argv[2])
    max_dim = int(sys.argv[3])
    num_of_basis = int(sys.argv[4])
    if (sys.argv[1] == '-s'):
        create_basis_files(min_dim, max_dim, num_of_basis, False)
    else:
        create_basis_files(min_dim, max_dim, num_of_basis, True)
    print('done')
else:
    print('usage: ./generate_basis.py [-d/-s] <min_dim> <max_dim> <num_of_basis>')
    print('       -d : checks that every basis is linearly independent')
    print("       -s : generates bases without checking linear independence")

