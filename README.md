# multilinear-model-tools
[![Build Status](https://travis-ci.org/m2ci-msp/multilinear-model-tools.svg?branch=master)](https://travis-ci.org/m2ci-msp/multilinear-model-tools)

## Building

For each component in `ema-tracker`, `fit-model`, and `model-builder`, run `cmake cmake` inside that component's directory.

### Prerequisites

You will need [CMake](https://cmake.org/) and a standard GCC or LLVM toolchain installed. In addition, the following dependencies are required:

- [Armadillo](http://arma.sourceforge.net/)
- [ANN](http://www.cs.umd.edu/~mount/ANN/)
- [JsonCpp](https://github.com/open-source-parsers/jsoncpp)
- [Asio](https://think-async.com/Asio)
- [yaml-cpp](https://github.com/jbeder/yaml-cpp)
- [ITK](https://itk.org/)
- [VTK](http://www.vtk.org/) (only needed for newer versions of ITK)

On OSX with [Homebrew](http://brew.sh/), install these dependencies with
```
$ brew install armadillo ann jsoncpp asio yaml-cpp insighttoolkit vtk
```

On Ubuntu, install these dependencies with
```
$ sudo apt-get install libarmadillo-dev libann-dev libjsoncpp-dev libasio-dev libyaml-cpp-dev libinsighttoolkit4-dev
```
