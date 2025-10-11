load("@rules_cc//cc:defs.bzl", "cc_library", "cc_binary")
cc_library(
    name = "numpy_file_reader",
    srcs = ["numpy_file_reader.cpp"],
    hdrs = ["numpy_file_reader.hpp"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "cli",
    srcs = ["cli.cpp"],
    deps = [":numpy_file_reader"],
    data = [":data/data.npy"],
)