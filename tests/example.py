from numpy import *
from sys import argv, exit

import pyblockzor

if len(argv) < 4:
    print "Error: Invalid use. Supply minbs maxbs nbs as cmlargs"

minbs, maxbs, nbs = [int(x) for x in argv[1:]] 

N = 1000000

if not pyblockzor.consistencyCheck(minbs, maxbs, nbs, N, False):
    exit()

a = zeros(N)

delta = 1.0

for i in range(1, N):
    a[i] = a[i-1] + delta*(1 - 2*random.random())/i

blocks, sigmas = pyblockzor.block(a, minbs, maxbs, nbs)

print "blocks", blocks
print "sigmas", sigmas

from matplotlib.pylab import *

plot(blocks, sigmas)
show()
