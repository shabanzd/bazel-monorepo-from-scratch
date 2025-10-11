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
        if (!file_.is_open()) {
            throw std::runtime_error("File is not open");
        }

        file_.seekg(data_offset_);
        std::vector<T> data(shape_[0] * shape_[1]);
        file_.read(reinterpret_cast<char*>(data.data()), data.size() * sizeof(T));
        return data;
    }

    static constexpr char kMagicString[7] = "\x93NUMPY";
private:
    std::ifstream file_;
    std::vector<int> shape_;
    std::string dtype_;
    std::string fortran_order_;
    size_t data_offset_;
    void parse_header();
};

} // namespace processing
