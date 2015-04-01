#include "combine.h"

#include <iostream>

using namespace arma;
using namespace std;


mat icz::combine(const vec &x, const vec &y)
{
    /*

def interpolate(x_start, x_end, y_start, y_end, x):
    slope = (y_end - y_start)/(x_end - x_start)

    return y_start + (x-x_start)*slope


def combine_results(all_x, all_y):

    n_runs = len(all_x)
    size = len(all_x[0])

    min_x = min(all_x, key=lambda z: z[0])[0]
    max_x = max(all_x, key=lambda z: z[-1])[-1]

    new_x = np.linspace(min_x, max_x, size)

    new_y = np.zeros_like(new_x)
    counts = np.zeros_like(new_x)

    for count, (x, y) in enumerate(zip(all_x, all_y)):

        print "%d / %d" % (count+1, n_runs)

        for i, xi in enumerate(x):

            closest_x_new = 0
            minimum_gap = 10000000
            loc = size+1
            for j, x_new_i in enumerate(new_x):
                gap = abs(x_new_i - xi)

                if gap < minimum_gap:
                    minimum_gap = gap
                    closest_x_new = x_new_i
                    loc = j

            if closest_x_new >= xi:

                start = i
                end = i + 1

                if end == size:
                    start = i - 1
                    end = i

            else:
                start = i-1
                end = i

                if start == -1:
                    start = 0
                    end = 1

            y_new_i = interpolate(x[start], x[end], y[start], y[end], closest_x_new)

            new_y[loc] += y_new_i
            counts[loc] += 1

    nonzero_slice = np.where(counts != 0)

    figure()
    plot(new_x, counts)

    new_x = new_x[nonzero_slice]
    new_y = new_y[nonzero_slice]/counts[nonzero_slice]


    return new_x, new_y
    */


    return join_rows(x, y);
}
