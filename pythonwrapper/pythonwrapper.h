#pragma once

#include <boost/numpy.hpp>

namespace pyicz
{

boost::numpy::ndarray combine(const boost::numpy::ndarray &xInput,
                              const boost::numpy::ndarray &yInput);

}
