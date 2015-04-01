class ICZAxis:
    def __init__(self):
        self.data = []

    def compact(self):
        min_value = min(self.data, key=lambda x: x[0])[0]
        max_value = max(self.data, key=lambda x: x[-1])[-1]

        length = len(self.data[0])

        return np.linspace(min_value, max_value, length)

    def append(self, array):

        if self.data:
            if len(self.data[-1]) != len(array):
                raise NotImplemented("Uneven array lengths is not implemented.")

        self.data.append(array)

class ICZ:

    def __init__(self, *args):

        self.n_axis = len(args)
        self.key_map = {}
        self.axes = []

        for index, name in enumerate(args):
            self.key_map[name] = index
            self.axes.append(ICZAxis())

    def __getitem__(self, name):
        return self.axes[self.key_map[name]]

    def intercombine(self, x_axis, y_axis, compact_x = True, roughen = False):
        return combine_results(self.axes[self.key_map[x_axis]].data,
                               self.axes[self.key_map[y_axis]].data)

