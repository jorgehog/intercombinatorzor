#pragma once

#include <armadillo>

using namespace arma;

namespace icz
{

double interpolate(const vec &x, const vec &y, const uint point, const double xValue);

double getDerivative(const mat &xAxes, const mat &yAxes, const uint dataSetIndex, const uint dataSetLength, const uint currentPoint);

double differenceScheme(const mat &xAxes, const mat &yAxes, const uint dataSetIndex, const uint p1, const uint p0);

void findClosestCombinedX(uint &indexClosestCombinedX, const vec &combinedX, const double datasetX);

mat combine(const mat &xAxes,
                const mat &yAxes);

vec combineXAxes(const mat &xAxes);

}

