#include <fstream>
#include <vector>
#include <string>
#include "processing/numpy_file_reader.hpp"
#include <stdexcept>
#include <cstring>
#include <cstdint>

namespace processing {
NumpyFileReader::NumpyFileReader(const std::string& filename) : file_(filename, std::ios::binary) {
    if (!file_.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    parse_header();
}

NumpyFileReader::~NumpyFileReader() {
    if (file_.is_open()) {
        file_.close();
    }
}

bool NumpyFileReader::is_open() const {
    return file_.is_open();
}

std::vector<int> NumpyFileReader::shape() const {
    return shape_;
}

std::string NumpyFileReader::dtype() const {
    return dtype_;
}



void NumpyFileReader::parse_header() {
    /**
    The first 6 bytes are a magic string: exactly \x93NUMPY.
    The next 1 byte is an unsigned byte: the major version number of the file format, e.g. \x01.
    The next 1 byte is an unsigned byte: the minor version number of the file format, e.g. \x00. 
    The next 2 bytes form a little-endian unsigned short int: the length of the header data HEADER_LEN.
    The next HEADER_LEN bytes form the header data describing the array’s format.
      It is an ASCII string which contains a Python literal expression of a dictionary.
      It is terminated by a newline (\n) and padded with spaces (\x20) to make the
      total of len(magic string) + 2 + len(length) + HEADER_LEN be evenly divisible by 64 for alignment purposes.
      “descr” dtype.descr
        An object that can be passed as an argument to the numpy.dtype constructor to create the array’s dtype.
      “fortran_order” bool
        Whether the array data is Fortran-contiguous or not. Since Fortran-contiguous arrays are a common
        form of non-C-contiguity, we allow them to be written directly to disk for efficiency.
      “shape” tuple of int
        The shape of the array.
     */

    // validate magic string
    char magic_string[6];
    file_.read(magic_string, 6);
    if (std::memcmp(magic_string, kMagicString, 6) != 0) {
        throw std::runtime_error("Not a valid .npy file");
    }

    // read major and minor version
    char version[2];
    file_.read(version, 2);

    // read header length
    uint16_t header_len;
    file_.read(reinterpret_cast<char*>(&header_len), sizeof(header_len));

    // read header data
    std::vector<char> header(header_len);
    file_.read(header.data(), header_len);
    std::string header_str(header.data(), header_len);

    // Simple parsing of the header string to extract dtype, shape and fortran_order
    std::string descr_string = "'descr': '";
    auto dtype_pos = header_str.find(descr_string) + descr_string.length();
    auto dtype_end = header_str.find("'", dtype_pos);
    dtype_ = header_str.substr(dtype_pos, dtype_end - dtype_pos);

    std::string fortran_order_string = "'fortran_order': ";
    auto fortran_order_pos = header_str.find(fortran_order_string) + fortran_order_string.length();
    auto fortran_order_end = header_str.find(",", fortran_order_pos);
    fortran_order_ = header_str.substr(fortran_order_pos, fortran_order_end - fortran_order_pos);
    if (fortran_order_ == "True") {
        throw std::runtime_error("Fortran order arrays are not supported");
    }

    std::string shape_string = "'shape': (";
    auto shape_pos = header_str.find(shape_string) + shape_string.length();
    auto shape_end = header_str.find(")", shape_pos);
    std::string shape_str = header_str.substr(shape_pos, shape_end - shape_pos);
    
    // parse shape
    size_t pos = 0;
    while ((pos = shape_str.find(',')) != std::string::npos) {
        shape_.push_back(std::stoi(shape_str.substr(0, pos)));
        shape_str.erase(0, pos + 1);
    }
    if (!shape_str.empty()) {
        shape_.push_back(std::stoi(shape_str));
    }

    data_offset_ = 10 + header_len; // 6 (magic) + 2 (version) + 2 (header length) + header length
}

} // namespace processing
