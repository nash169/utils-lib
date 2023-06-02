# Utils Library
Repository containing some utility frequently used inside different libraries.

## Authors/Maintainers
- Bernardo Fichera (bernardo.fichera@epfl.ch)

## Available Utils
- File Manager
- Timer
- Realtime checker
- Derivative checker

## Usage
**utils-lib** is header only library. In order to use it just include the header relative to the utils you intend to use in your project.

### File Manager

### Eigen Alias

### Check Derivatives
$E(t) = | f(tv) - f(x) - t <\text{grad} f(x), v> | = O(t^2)$ 

$\log E(t) \approx 2 \log t + \text{constant}$

<p align="center">
  <img width="40%" src="https://bernardofichera.com/images/check_gradient.png">
  <img width="40%" src="https://bernardofichera.com/images/check_hessian.png">
</p>                                                                     

## ToDo
- add memory allocation monitoring (https://en.cppreference.com/w/cpp/types/alignment_of)
- introduce retraction based taylor expansion to check derivative on manifolds

## Dependencies
This library depends on **Eigen** linear algebra library to load data into *Eigen* vectors/matrices. For various utilities the library depends on **Corrade** utility library.

*Corrade* installation:
```sh
git clone https://github.com/mosra/corrade.git (git@github.com:mosra/corrade.git)
cd corrade && mkdir build && cmake .. && make && (sudo) make install
```
*Eigen* installation:
```sh
git clone https://gitlab.com/libeigen/eigen.git (git@gitlab.com:libeigen/eigen.git)
cd eigen && mkdir build && cmake .. && (sudo) make install
```

In addition, in order to compile the project, install my [waf-tools](https://github.com/nash169/waf-tools.git).

### Installation
Compile and install using waf commands
```sh
waf (./waf) configure build
```
or
```sh
waf (./waf) configure && waf (./waf)
```
Install the library (optional)
```sh
(sudo) waf (./waf) install
```
If you want to make a clean installation
```sh
(sudo) waf (./waf) distclean configure build install
```

#### Compilation options
In order to set the desired compiler define the environment variable CXX=<g++,clang++,icpc> (gnu, clang and intel compiler respectively).

AVX support with optimization flags is active by default. If you want disable this run the configure with `debug` flag:
```sh
waf (./waf) configure --debug
```
Compile static library (default option)
```sh
waf (./waf) configure --static
```
Compile shared library
```sh
waf (./waf) configure --shared
```
Define a specific installation path
```sh
waf (./waf) configure --prefix=/path/to/install/folder
```


### Examples
Once the library is compiled all the examples can be found in
```sh
./build/src/examples/
```
