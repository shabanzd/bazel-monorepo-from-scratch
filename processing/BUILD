load("@pybind11_bazel//:build_defs.bzl", "pybind_extension")
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("@rules_python//python:defs.bzl", "py_binary")

cc_library(
    name = "numpy_file_reader",
    srcs = ["numpy_file_reader.cpp"],
    hdrs = ["numpy_file_reader.hpp"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "cli",
    srcs = ["cli.cpp"],
    data = ["//processing/data:data.npy"],
    deps = [
        ":numpy_file_reader",
        "@bazel_tools//tools/cpp/runfiles",
    ],
)

pybind_extension(
    name = "numpy_cpp",
    srcs = [
        "numpy_file_reader.cpp",
        "numpy_file_reader.hpp",
        "numpy_file_reader_pybind.cpp",
    ],
    deps = [":numpy_file_reader"],
)

py_binary(
    name = "py_cli",
    srcs = ["py_cli.py"],
    data = ["//processing/data:data.npy"],
    imports = ["."],
    deps = [
        ":numpy_cpp",
        "@pypi//numpy",
    ],
)
