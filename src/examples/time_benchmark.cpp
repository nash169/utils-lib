/*
    This file is part of utils-lib.

    Copyright (c) 2020, 2021, 2022, 2023 Bernardo Fichera <bernardo.fichera@gmail.com>

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

#include <Eigen/Core>
#include <utils_lib/Timer.hpp>

using namespace utils_lib;

int main(int argc, char const* argv[])
{
    constexpr int dim = 100;

    Eigen::Matrix<double, dim, dim> A = Eigen::Matrix<double, dim, dim>::Random();
    Eigen::Matrix<double, dim, 1> x = Eigen::Matrix<double, dim, 1>::Random(), b = Eigen::Matrix<double, dim, 1>::Zero();

    {
        Timer timer;
        for (size_t i = 0; i < dim; i++)
            for (size_t j = 0; j < dim; j++)
                b(i) += A(i, j) * x(j);
    }

    {
        Timer timer;
        b = A * x;
    }

    return 0;
}
