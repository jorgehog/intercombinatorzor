#include "pythonwrapper.h"

#include <intercombinatorzor.h>

#include <boost/python.hpp>

namespace bp = boost::python;
namespace bn = boost::numpy;

using namespace arma;
using namespace std;

boost::numpy::ndarray pyicz::combine(const boost::numpy::ndarray &xInput,
                                     const boost::numpy::ndarray &yInput)
{
    //convert numpy data to armadillo
    mat x(reinterpret_cast<double*>(xInput.get_data()), xInput.shape(1), xInput.shape(0), false);
    mat y(reinterpret_cast<double*>(yInput.get_data()), yInput.shape(1), yInput.shape(0), false);

    mat result = icz::combine(x, y);

    //Convert result to numpy array
    Py_intptr_t shape[2] = {result.n_cols, result.n_rows};
    bn::ndarray numpyResult = bn::zeros(2, shape, bn::dtype::get_builtin<double>());
    std::copy(result.begin(), result.end(), reinterpret_cast<double*>(numpyResult.get_data()));

    return numpyResult;
}


BOOST_PYTHON_MODULE(icz)
{
    bn::initialize();
    bp::def("combine", pyicz::combine);
}
