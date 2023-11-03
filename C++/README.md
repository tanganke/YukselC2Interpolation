## How to compile

1. with cmake and vcpkg

```bash
mkdir build && cd build
cmake ..
make
```

2. Alternatively, using g++/clang++:

```bash
# INCLUDE_DIR=<include path>
# LIBRARY_DIR=<library path>
# g++ main.cpp -I$INCLUDE_DIR -L$LIBRARY_DIR -lgsl -std=c++20 -o main
clang++ main.cpp -I$INCLUDE_DIR -L$LIBRARY_DIR -lgsl -std=c++20 -o main
```

where `INCLUDE_DIR` and `LIBRARY_DIR` are the paths to the include and library directories respectively.

## Usage

1. generate interpolated points

```bash
./main > result.csv
```

2. plot results

```bash
python3 result_plot.py
```
