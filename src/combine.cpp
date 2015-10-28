#include "combine.h"

#include <iostream>

#include <BADAss/badass.h>

#ifndef NO_OMP
#include <omp.h>
#endif

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

double icz::getDerivative(const mat &xAxes,
                          const mat &yAxes,
                          const uint dataSetIndex,
                          const uint dataSetLength,
                          const uint currentPoint)
{
    if (currentPoint == 0)
    {
        return differenceScheme(xAxes, yAxes, dataSetIndex, 1, 0);
    }

    else if (currentPoint == dataSetLength - 1)
    {
        return differenceScheme(xAxes, yAxes, dataSetIndex, dataSetLength - 1, dataSetLength - 2);
    }

    else
    {
        return differenceScheme(xAxes, yAxes, dataSetIndex, currentPoint + 1, currentPoint - 1);
    }
}


double icz::differenceScheme(const mat &xAxes, const mat &yAxes, const uint dataSetIndex, const uint p1, const uint p0)
{
    double dy = yAxes(p1, dataSetIndex) - yAxes(p0, dataSetIndex);
    double dx = xAxes(p1, dataSetIndex) - xAxes(p0, dataSetIndex);

    return dy/dx;
}

mat icz::combine(const mat &xAxes, const mat &yAxes)
{
    BADAssEqual(xAxes.size(), yAxes.size());

    const uint dataSetLength = xAxes.n_rows;
    const uint nDatasets = xAxes.n_cols;

    //The combined axis to which everything is projected
    const vec combinedX = combineXAxes(xAxes);

#ifndef NO_OMP
    const uint NP = omp_get_num_procs();
#else
    const uint NP = 1;
#endif

    //The combined yaxis which the interpolated results are stores.
    //One per thread, which is combined afterwards.
    mat threadY(dataSetLength, NP, fill::zeros);

    //The number of times a value has been projected to a x value.
    umat threadCounts(dataSetLength, NP, fill::zeros);

    double yNew;

#ifndef NO_OMP
#pragma omp parallel for private(yNew)
#endif
    for (uint dataset = 0; dataset < nDatasets; ++dataset)
    {
        uint indexClosestCombinedX = 0;
        for (uint xAxisIndex = 0; xAxisIndex < dataSetLength; ++xAxisIndex)
        {

            //The xValue of [dataset] at index #[xIndex]
            const double &datasetX = xAxes(xAxisIndex, dataset);
            const double &datasetY = yAxes(xAxisIndex, dataset);

            findClosestCombinedX(indexClosestCombinedX, combinedX, datasetX);

            const double &closestCombinedX = combinedX(indexClosestCombinedX);

            //The distance which is offset;
            const double interpolationDistance = closestCombinedX - datasetX;

            if (fabs(interpolationDistance) < 1e-15)
            {
                yNew = datasetY;
            }

            else
            {
                double a = getDerivative(xAxes, yAxes, dataset, dataSetLength, xAxisIndex);
                yNew = datasetY + a*interpolationDistance;
            }

            BADAssEqual(yNew, yNew); //nanCheck

#ifndef NO_OMP
            const uint ti = omp_get_thread_num();
#else
            const uint ti = 0;
#endif

            threadY(indexClosestCombinedX, ti) += yNew;
            threadCounts(indexClosestCombinedX, ti)++;
        }
    }

    uvec counts = sum(threadCounts, 1);
    vec Y = sum(threadY, 1);

    uvec nonzero = find(counts != 0);
    return join_rows(combinedX(nonzero), Y(nonzero)/counts(nonzero));

}


vec icz::combineXAxes(const mat &xAxes)
{
    const double xMin = min(xAxes.row(0));
    const double xMax = max(xAxes.row(xAxes.n_rows-1));

    return linspace(xMin, xMax, xAxes.n_rows);
}



void icz::findClosestCombinedX(uint &indexClosestCombinedX, const vec &combinedX, const double datasetX)
{

    //Search untill we find the index of the
    //combined x which is greater than [datasetX]
    while (combinedX(indexClosestCombinedX) < datasetX)
    {
        indexClosestCombinedX++;
    }

    if (indexClosestCombinedX != 0)
    {
        //if the previous was closer, we choose the previous index.
        if (fabs(combinedX(indexClosestCombinedX-1) - datasetX) < fabs(combinedX(indexClosestCombinedX) - datasetX))
        {
            indexClosestCombinedX = indexClosestCombinedX - 1;
        }
    }
}
