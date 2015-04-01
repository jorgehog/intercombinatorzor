#include <intercombinatorzor.h>

#include <sys/time.h>
#include <iostream>

#include <armadillo>

using namespace arma;

int main()
{
    vec x = linspace(1, 100, 10000);
    vec y = randu(10000);

    mat result = icz::combine(x, y);
    cout << result << endl;

    return 0;
}
