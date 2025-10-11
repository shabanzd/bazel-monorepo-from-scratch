import numpy_cpp as my_np
import numpy as np
from bazel_tools.tools.python.runfiles import runfiles

if __name__ == "__main__":
    r = runfiles.Create()
    filename = r.Rlocation("_main/processing/data/data.npy")

    reader = my_np.NumpyFileReader(filename)
    print(f"File opened successfully: {filename}")
    print(f"Array shape: {reader.shape()}")
    print(f"Array dtype: {reader.dtype()}")
    data = reader.read_data_int()


    # compare with numpy
    array = np.load(filename)
    assert array.dtype == reader.dtype()
    assert array.shape == tuple(reader.shape())
    assert np.all(array.flatten() == data)
    print("C++ numpy reader output matches official numpy output.")
