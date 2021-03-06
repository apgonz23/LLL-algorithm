# Graphs expected alpha values
# Usage: python graph_alphas.py <input_file>
# Reads the dimensions and expected alphas from the input file
# and plots them on a scatter plot
import sys
import matplotlib.pyplot as plt

if (len(sys.argv) != 2):
    print('usage: ./graph_alphas.py <input_file>')
    sys.exit()

dimensions = []
alphas = []

infile = sys.argv[1]
with open(infile) as f:
    for line in f:
        tokens = line.strip().split()
        if (len(line.strip()) == 0):
            continue
        if (tokens[0] != 'dim' and line[0] != '#'):
            dimensions.append(int(tokens[0]))
            alphas.append(float(tokens[2]))

plt.scatter(dimensions, alphas)
plt.xlabel('Dimension')
plt.ylabel('Expected alpha value')
plt.title('Optimal alpha value by dimension')

plt.savefig('alphaGraph.png', bbox_inches='tight')
plt.show()
