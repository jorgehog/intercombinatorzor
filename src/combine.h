#pragma once

#include <armadillo>

using namespace arma;

namespace icz
{

double interpolate(const vec &x, const vec &y, const uint point, const double xValue);

mat combine(const mat &xAxis,
                const mat &yAxis);

vec combineXAxes(const mat &xAxes);

}

