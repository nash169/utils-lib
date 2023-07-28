# Utils Library
Repository containing some utility frequently used inside different libraries.

## Authors/Maintainers
- Bernardo Fichera (bernardo.fichera@epfl.ch)

## Available Utils
- File Manager
- Timer
- Eigen Memory Allocation checker
- Derivative checker

## ToDo
- add memory allocation monitoring (https://en.cppreference.com/w/cpp/types/alignment_of)
- introduce retraction based taylor expansion to check derivative on manifolds

## Usage
**utils-lib** is header only library. In order to use it just include the header relative to the utils you intend to use in your project.

### File Manager
In order to read/write from/to a given file create and instance of the `FileManager` object and set the path to the file you want to operate on
```c++
utils_lib::FileManager file_manager;
file_manager.setFile("path/to/file");
```
In case you want to write on the file, if either the file or the folder(s) in the path do not exist they will be automatically created. To write on the file call the `write` passing the elements you want to write. The utility uses variadic template techniques in order to allow to write onto a file an arbitrary number of elements in sequence. For instance
```c++
constexpr int dim = 100;
Eigen::VectorXd x = Eigen::VectorXd::Random(dim), y = Eigen::VectorXd::Random(dim);
file_manager.write("x", x, "y", y);
```
The above snippet shows how to write the vectors $x$ and $y$ preceded by their respective labels. The algorithm will write down on the file the label followed by a space and then the vector passed. To append to a file
```c++
file_manager.append("x", x, "y", y)
```
In order to read from file you can just call the `read` method specializing the template to the type of object you want to read. In addition you can specify and specific string present in the file from which starting to read as well as an end string where to stop reading. If no end key is specifying the algorithm will stop reading at the first blank line encountered. Sometime after you want to ignore reading a bunch of lines; set the second argument in the `read` method to achieve that (`read<object_type>(key_start, num_lines_to_ignore, key_end)`). The utility supports methods chaining technique. So in case you want to read from a new file you can set it and read from it in one line.
```c++
Eigen::VectorXd x, y;
x = file_manager.setFile("path/to/new/file").read<Eigen::MatrixXd>("x", 2);
y = file_manager.setFile("path/to/new/file").read<Eigen::MatrixXd>("y", 2);
```
When you specify a key start you want to ignore this line itself and the space after it; therefore the number $2$ set ad number of lines to ignore. Check the example `read_write.cpp` to find out more.


### Timer
The timer utility measures the time in between the creation and the destruction of the `Timer` object. Place the piece of code you want to benchmark within the same scope of the `Timer` object. For instance
```c++
constexpr int dim = 100;

    Eigen::Matrix<double, dim, dim> A = Eigen::Matrix<double, dim, dim>::Random();
    Eigen::Matrix<double, dim, 1> x = Eigen::Matrix<double, dim, 1>::Random(), b = Eigen::Matrix<double, dim, 1>::Zero();

    {
        utils_lib::Timer timer;
        for (size_t i = 0; i < dim; i++)
            for (size_t j = 0; j < dim; j++)
                b(i) += A(i, j) * x(j);
    }

    {
        utils_lib::Timer timer;
        b = A * x;
    }
```
As soon as `Timer` goes out of scope it will print the duration in time (in us, ms and s). Check the example `time_benchmark.cpp` to find out more.

### Eigen Memory Allocation Check
In scenarios where we want to run application in real-time maintaining consistent frequency, runtime memory allocation is an important aspect. This is an utility based on Eigen Linear Algebra Library. It is inspired from [this](https://github.com/stulp/eigenrealtime) repo. Whenever you need to check if eigen is allocating memory at runtime include the utility header **before** including `Eigen`.

```c++
#include <utils_lib/RealtimeChecker.hpp>
#include <Eigen/Core>
```

Place the code where you want to avoid runtime memory allocation in between the macros `ENTERING_REAL_TIME_CRITICAL_CODE` and `EXITING_REAL_TIME_CRITICAL_CODE`. For instance

```c++
Eigen::MatrixXd a = Eigen::MatrixXd::Random(5, 5), b = Eigen::MatrixXd::Random(5, 5), c = Eigen::MatrixXd::Random(5, 5);

ENTERING_REAL_TIME_CRITICAL_CODE

// no memory allocation
a.noalias() += b * c;


// memory allocation
a += b * c;

EXITING_REAL_TIME_CRITICAL_CODE
```
The code will go through the first operation while it will crash in the second one where memory allocations happens. Check the example `eigen_malloc.cpp` to find out more.

### Check Derivatives
This utility helps in numerically checking derivatives (up to second order). In order to check the gradient, the algorithm simply check that the taylor expansion up to the first derivative 
$$E(t) = | f(tv) - f(x) - t <\text{grad} f(x), v> | = O(t^2)$$
has a slope of approximately $2$ 
$$\log E(t) \approx 2 \log t + \text{constant}.$$
For the hessian check the taylor expansion up to the second derivative
$$E(t) = | f(tv) - f(x) - t <\text{grad} f(x), v> -\frac{t^2}{2} <\text{Hess} f(x)[v], v >| = O(t^3)$$
should approximately have a slope of $3$
$$\log E(t) \approx 3 \log t + \text{constant}.$$

First define your function and the derivative of it.
```c++
template <int size>
struct Function {
    double operator()(const Eigen::Matrix<double, size, 1>& x) const
    {
        return x(0) * x(0) * x(0);
    }
};

// grad f(x)
template <int size>
struct Gradient {
    Eigen::Matrix<double, size, 1> operator()(const Eigen::Matrix<double, size, 1>& x) const
    {
        return 3 * x * x;
    }
};
```
The utility is fully templated; you have the freedom to define your functions as structures with overloaded `()` operators, as shown above, lambda functions, `std::functions` wrapper or raw pointers. Define an instance of the utility (specifying the problem dimension) and then call the `checkGradient` method.
```c++
constexpr int dim = 1;
utils_lib::DerivativeChecker<long double> checker(dim);

bool grad_is_correct = checker.checkGradient(Function<dim>(), Gradient<dim>());
```
Check the example `check_derivative.cpp` to find out more.


<p align="center">
  <img width="40%" src="media/check_gradient.png">
  <img width="40%" src="media/check_hessian.png">
</p>                                                                     

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

## Installation
Compile and install using waf commands
```sh
waf configure build
```
or
```sh
waf configure && waf
```
Install the library (optional)
```sh
(sudo) waf install
```
If you want to make a clean installation
```sh
(sudo) waf distclean configure build install
```

### Compilation options
In order to set the desired compiler define the environment variable CXX=<g++,clang++,icpc> (gnu, clang and intel compiler respectively).

AVX support with optimization flags is active by default. If you want disable this run the configure with `debug` flag:
```sh
waf configure --debug
```
Compile static library (default option)
```sh
waf configure --static
```
Compile shared library
```sh
waf configure --shared
```
Define a specific installation path
```sh
waf configure --prefix=/path/to/install/folder
```

## Examples
Once the library is compiled all the examples can be run with
```sh
./build/src/examples/<name_example>
```
