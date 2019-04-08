# Functions for producing testing data
# Generates the specified number of basis for each dimension 
# starting at the (3x3) all the way to (max_dim x max_dim)
# usage: ./generate_basis.py -d max_dim num_of_basis

import sys
import numpy as np

# generates k number of nxn matrices and writes them to a file
def generate_matrices(n, k):
    with open('data/n'+str(n)+'.txt', 'w') as f:
        for i in range(k):
            det = 0
            while (det == 0):
                M = np.random.randint(-9, 9, size=(n,n))
                det = np.linalg.det(M)
            f.write('b\n')
            for j in range(n):
                for h in range(n):
                    if (h):
                        f.write(' ')
                    f.write(str(M[j][h]))
                f.write('\n')

# creates a file with multiple basis from (3x3) to (max_dim x max_dim)
def create_basis_files(max_dim, k):
    for i in range(3, max_dim+1):
        generate_matrices(i, k)

# checks to ensure call is correct
if (len(sys.argv) == 4 and sys.argv[1] == '-d'):
    max_dim = int(sys.argv[2])
    num_of_basis = int(sys.argv[3])
    print('writing to files...')
    create_basis_files(max_dim, num_of_basis)
    print('done')
else:
    print('usage: ./generate_basis.py -d [max_dim] [num_of_basis]')

