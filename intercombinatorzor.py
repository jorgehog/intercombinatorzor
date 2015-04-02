import sys
import os
import inspect

import numpy as np

this_dir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
sys.path.append(os.path.join(this_dir, "lib"))

import icz

class ICZAxis:
    def __init__(self):
        self.data = []

    def append(self, array):

        if self.data:
            if len(self.data[-1]) != len(array):
                raise NotImplemented("Uneven array lengths is not implemented.")

        self.data.append(array)

    def __len__(self):
        if not self.data:
            return 0

        return len(self.data[0])

    def sort(self):
        for i in range(len(self.data)):
            self.data[i] = sorted(self.data[i])

class ICZ:

    def __init__(self, *args):

        self.n_axis = len(args)
        self.key_map = {}
        self.axes = []

        for index, name in enumerate(args):
            self.key_map[name] = index
            self.axes.append(ICZAxis())

    def __len__(self):
        if not self.axes:
            return 0

        return len(self.axes[0].data)

    def feed(self, *args):

        if len(args) != self.n_axis:
            raise RuntimeError("Invalid number of feedings.")

        for i, arg in enumerate(args):
            self.axes[i].append(np.asarray(arg))

    def __getitem__(self, name):
        return self.axes[self.key_map[name]]

    def intercombine(self, x_label, y_label, assume_sorted=True):

        if not assume_sorted:
            self.axes[self.key_map[x_label]].sort()

        return icz.combine(np.asarray(self.axes[self.key_map[x_label]].data),
                           np.asarray(self.axes[self.key_map[y_label]].data))



