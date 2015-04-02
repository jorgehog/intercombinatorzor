#include "combine.h"

#include <iostream>

#include <BADAss/badass.h>

#include <omp.h>

using namespace arma;
using namespace std;


double icz::interpolate(const vec &x, const vec &y, const uint point, const double xValue)
{
    const double xStart = x(point - 1);
    const double xEnd = x(point + 1);

    const double yStart = y(point - 1);
    const double yEnd = y(point + 1);

    const double slope = (yEnd - yStart)/(xEnd - xStart);

    return yStart + (xValue-xStart)*slope;

}


mat icz::combine(const mat &xAxis, const mat &yAxis)
{
    BADAssEqual(xAxis.size(), yAxis.size());

    const uint nAxis = xAxis.n_cols;
    const uint axisLength = xAxis.n_rows;

    const vec X = combineXAxes(xAxis);
    mat threadY(axisLength, omp_get_num_procs(), fill::zeros);

    umat threadCounts(axisLength, omp_get_num_procs(), fill::zeros);

    uint point;

#pragma omp parallel for private(point)
    for (uint axis = 0; axis < nAxis; ++axis)
    {
        uint target = 0;
        for (uint i = 0; i < axisLength; ++i)
        {
            const double &xi = xAxis(i, axis);

            while (X(target) < xi)
            {
                target++;
            }

            if (target != 0)
            {
                if (abs(X(target-1) - xi) < abs(X(target) - xi))
                {
                    target = target - 1;
                }
            }

            double Xn = X(target);

            if (Xn >= xi)
            {
                if (i == axisLength - 1 || i == 0)
                {
                    continue;
                }

                point = i;
            }

            else
            {
                if (i == 0)
                {
                    continue;
                }
                else if (i == 1)
                {
                    point = i;
                }
                else
                {
                    point = i-1;
                }

            }

            double y_new_i = interpolate(xAxis.col(axis), yAxis.col(axis), point, Xn);

            threadY(target, omp_get_thread_num()) += y_new_i;
            threadCounts(target, omp_get_thread_num())++;
        }
    }

    uvec counts = sum(threadCounts, 1);
    vec Y = sum(threadY, 1);

    uvec nonzero = find(counts != 0);
    return join_rows(X(nonzero), Y(nonzero)/counts(nonzero));

}


vec icz::combineXAxes(const mat &xAxes)
{
    const double xMin = min(xAxes.row(0));
    const double xMax = max(xAxes.row(xAxes.n_rows-1));

    return linspace(xMin, xMax, xAxes.n_rows);
}
