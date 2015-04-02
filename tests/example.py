import numpy as np
from matplotlib import pylab as pl
import sys
import math

sys.path.append("..")

from intercombinatorzor import ICZ

nx = 1500
x_max = 2*math.pi

n_axes = 1000

icz = ICZ("x", "y")

pl.figure()
for n in range(n_axes):
    x = sorted(np.random.uniform(0, x_max, size=nx))
    y = np.sin(x) + 0.1*(2*np.random.uniform(size=nx) - 1)

    icz.feed(x, y)
    pl.plot(x[::10], y[::10])

X, Y = icz.intercombine("x", "y")

pl.plot(X, np.sin(X), "-k", linewidth=3)

pl.figure()
pl.plot(X, Y, "-b")
pl.plot(X, np.sin(X), "-r")
pl.show()



