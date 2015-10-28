#include <intercombinatorzor.h>

#include <sys/time.h>
#include <iostream>

#include <armadillo>

using namespace arma;

int main()
{
    uint size = 10;
    uint nAxes = 5;

    mat x(size, nAxes);
    mat y = randu(size, nAxes);

    for (uint axis = 0; axis < nAxes; ++axis)
    {
        x.col(axis) = linspace(0, 10 + 10*axis, size);
    }

    cout << x << endl;
    cout << y << endl;

    mat result = icz::combine(x, y);
    cout << result << endl;

    return 0;
}
