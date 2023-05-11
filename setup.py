from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup

__version__ = "0.0.1"


ext_modules = [
    Pybind11Extension("jb01",
        ["src/main.cpp", "src/lib/JB01_Compress.cpp", "src/lib/JB01_Decompress.cpp"],
        # Example: passing in the version to the compiled code
        define_macros=[('VERSION_INFO', __version__)],
        ),
]

setup(
    name="jb01",
    version=__version__,
    author="newmsk",
    author_email="newmsk97@outlook.com",
    url="https://github.com/newmsk/JB01",
    description="JB01 LZSS compression lib python bindings",
    long_description="",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
    python_requires=">=3.7",
)
