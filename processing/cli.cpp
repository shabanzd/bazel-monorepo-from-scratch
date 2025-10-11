#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdexcept>
#include <cstring>
#include <fstream>
#include "processing/numpy_file_reader.hpp"
#include <unistd.h>

int main(){
    std::string filename = "processing/data/data.npy"; // Replace with your .npy file path
    try {
        processing::NumpyFileReader reader(filename);
        if (!reader.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return EXIT_FAILURE;
        }

        std::cout << "File opened successfully: " << filename << std::endl;
        std::cout << "Array shape: ";
        for (const auto& dim : reader.shape()) {
            std::cout << dim << " ";
        }
        std::cout << std::endl;

        std::cout << "Data type: " << reader.dtype() << std::endl;

        // Assuming the data type is float64 (double)
        auto data = reader.read_data<double>();
        std::cout << "First 10 elements of the array:" << std::endl;
        for (size_t i = 0; i < std::min(data.size(), size_t(10)); ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}