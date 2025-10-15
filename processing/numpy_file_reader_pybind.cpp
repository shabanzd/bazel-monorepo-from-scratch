#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "processing/numpy_file_reader.hpp"

namespace py = pybind11;
using namespace processing;

PYBIND11_MODULE(numpy_cpp, m) {
    py::class_<NumpyFileReader>(m, "NumpyFileReader")
        .def(py::init<const std::string&>())
        .def("is_open", &NumpyFileReader::is_open)
        .def("shape", &NumpyFileReader::shape)
        .def("dtype", &NumpyFileReader::dtype)
        .def("read_data_int", &NumpyFileReader::read_data<int64_t>)
        .def("read_data_float", &NumpyFileReader::read_data<float>);
}
