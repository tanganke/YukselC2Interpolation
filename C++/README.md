## How to compile

1. with cmake and vcpkg

```bash
mkdir build && cd build
cmake ..
make
```

2. Alternatively, using g++/clang++:

```bash
# g++ main.cpp -I$INCLUDE_DIR -L$LIBRARY_DIR -lgsl -std=c++20 -o main
clang++ main.cpp -I$INCLUDE_DIR -L$LIBRARY_DIR -lgsl -std=c++20 -o main
```

where INCLUDE_DIR and LIBRARY_DIR are the paths to the include and library directories respectively.
