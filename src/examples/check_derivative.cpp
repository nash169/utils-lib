/*
    This file is part of utils-lib.

    Copyright (c) 2020, 2021, 2022 Bernardo Fichera <bernardo.fichera@gmail.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include <utils_lib/DerivativeChecker.hpp>
#include <utils_lib/FileManager.hpp>

using namespace utils_lib;

// f(x)
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

// Hess f(x) [v]
template <int size>
struct Hessian {
    Eigen::Matrix<double, size, 1> operator()(const Eigen::Matrix<double, size, 1>& x, const Eigen::Matrix<double, size, 1>& v) const
    {
        return 6 * x * v;
    }
};

int main(int argc, char const* argv[])
{
    constexpr int dim = 1;

    DerivativeChecker<long double> checker(dim);

    if (checker.checkGradient(Function<dim>(), Gradient<dim>()))
        std::cout << "The gradient is CORRECT!" << std::endl;
    else
        std::cout << "The gradient is NOT correct!" << std::endl;

    if (checker.checkHessian(Function<dim>(), Gradient<dim>(), Hessian<dim>()))
        std::cout << "The hessian is CORRECT!" << std::endl;
    else
        std::cout << "The hessian is NOT correct!" << std::endl;

    FileManager io_manager;
    io_manager.setFile("outputs/check_derivative.csv").write("gradient", checker.numericalGradient(), "hessian", checker.numericalHessian());
}

// // f(x)
// template <int size>
// struct Function {
//     Eigen::Matrix<double, size, size> A = Eigen::MatrixXd::Identity(size, size);

//     double operator()(const Eigen::Matrix<double, size, 1>& x) const
//     {
//         return x.transpose() * A * x;
//     }
// };

// // grad f(x)
// template <int size>
// struct Gradient {
//     Eigen::Matrix<double, size, size> A = Eigen::MatrixXd::Identity(size, size);

//     Eigen::Matrix<double, size, 1> operator()(const Eigen::Matrix<double, size, 1>& x) const
//     {
//         return 2 * (A * x);
//     }
// };

// // Hess f(x) [v]
// template <int size>
// struct Hessian {
//     Eigen::Matrix<double, size, size> A = Eigen::MatrixXd::Identity(size, size);

//     Eigen::Matrix<double, size, 1> operator()(const Eigen::Matrix<double, size, 1>& x, const Eigen::Matrix<double, size, 1>& v) const
//     {
//         return 2 * (A * v);
//     }
// };