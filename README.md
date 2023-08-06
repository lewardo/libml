# libml

yet another C++ machine learning library

```sh
# make build directory
mkdir build && cd build
# generate cmake files
cmake ..
# build library and tests
cmake --build . --target libml-test
# run tests
ctest --verbose --build-config "Debug"
# install library (currently only local)
cmake --build . --target install
```
