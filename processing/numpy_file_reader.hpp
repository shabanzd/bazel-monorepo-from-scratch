#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstring>

namespace processing {

class NumpyFileReader {
public:
    NumpyFileReader(const std::string& filename);
    ~NumpyFileReader();

    bool is_open() const;
    std::vector<int> shape() const;
    std::string dtype() const;
    template<typename T>
    std::vector<T> read_data() {
        if (dtype_ != dtype_string<T>()) {
            throw std::runtime_error("Data type mismatch");
        }
        if (shape_.size() != 2) {
            throw std::runtime_error("Only 2D arrays are supported");
        }
        if (!file_.is_open()) {
            throw std::runtime_error("File is not open");
        }

        file_.seekg(data_offset_);
        std::vector<T> data(shape_[0] * shape_[1]);
        file_.read(reinterpret_cast<char*>(data.data()), data.size() * sizeof(T));
        return data;
    }

    static constexpr char kMagicString[7] = "\x93NUMPY";
    template <typename T>
    static std::string dtype_string(){
        if (std::is_same<T, float>::value) {
            return "<f4";
        } else if (std::is_same<T, double>::value) {
            return "<f8";
        } else if (std::is_same<T, int32_t>::value) {
            return "<i4";
        } else if (std::is_same<T, int64_t>::value) {
            return "<i8";
        } else {
            throw std::runtime_error("Unsupported data type");
        }
    }
private:
    std::ifstream file_;
    std::vector<int> shape_;
    std::string dtype_;
    std::string fortran_order_;
    size_t data_offset_;
    void parse_header();
};

} // namespace processing
