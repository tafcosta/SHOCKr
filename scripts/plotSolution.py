import cmocean
import colorcet
import cmcrameri

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors

# Read and split by truly empty lines (ignoring whitespace-only lines)
with open('../test.txt') as f:
    lines = f.readlines()

blocks = []
current_block = []

for line in lines:
    if line.strip() == '':
        if current_block:
            blocks.append(np.loadtxt(current_block))
            current_block = []
    else:
        current_block.append(line)

# Add the last block if needed
if current_block:
    blocks.append(np.loadtxt(current_block))

# Set up color mapping
cmap = cmcrameri.cm.turku
norm = mcolors.Normalize(vmin=0, vmax=len(blocks))

# Plot (excluding ghost cells: first and last rows)
plt.tick_params(
    axis='both',
    which='both',
    direction='in',
    top=True,
    right=True
)

for i in range(0, len(blocks), 5):
    block = blocks[i][1:]  # Exclude ghost cells
    x = block[:, 0]
    y = block[:, 4]  # Change this index to plot a different variable
    color = cmap(norm(i))
    plt.loglog(x, y, color=color)
    
plt.xlabel(r'$R$')
plt.ylabel(r'$\rho$')
plt.xlim(1.e-2, 1.e2)

plt.colorbar(plt.cm.ScalarMappable(norm=norm, cmap=cmap), label=r'$t$')
plt.show()
