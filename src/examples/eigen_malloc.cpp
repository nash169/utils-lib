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

#include <utils_lib/RealtimeChecker.hpp>

#include <Eigen/Core>

// Source: https://github.com/stulp/eigenrealtime/tree/master

int main(int argc, char const* argv[])
{
    Eigen::MatrixXd a = Eigen::MatrixXd::Random(5, 5), b = Eigen::MatrixXd::Random(5, 5), c = Eigen::MatrixXd::Random(5, 5), prealloc(5, 5);

    ENTERING_REAL_TIME_CRITICAL_CODE
    // no memory allocation even without noalias
    b += c;

    // no memory allocation
    a.noalias() += b * c;

    // memory allocation (code crashes)
    a += b * c;

    // memory allocation and not possible to noalias (code crashes)
    c += b * c;

    // using pre-allocation to avoid allocating in real time application
    prealloc.noalias() = b * c;
    c = prealloc;

    EXITING_REAL_TIME_CRITICAL_CODE

    return 0;
}