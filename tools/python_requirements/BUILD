load("@rules_uv//uv:pip.bzl", "pip_compile")

exports_files([
    "requirements.in",
])

pip_compile(
    name = "requirements",
    requirements_in = "requirements.in",
    requirements_txt = "requirements_lock.txt",
    tags = [
        "manual",
    ],
)