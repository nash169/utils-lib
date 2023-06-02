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

#include <utils_lib/FileManager.hpp>

using namespace utils_lib;

struct Sigmoid {
    double _a = 2, // lower asymptote
        _b = 1,
           _k = 5, // upper asymptote
        _m = -10,
           _c = 1, _q = 1, _ni = 1;

    double operator()(const double& t)
    {
        return _a + (_k - _a) / std::pow(_c + _q * std::exp(-_b * (t - _m)), 1 / _ni);
    }
};

struct Gaussian {
    double _b = 5, _m = 1, _k = 5;

    double operator()(const double& t)
    {
        return _k * std::exp(-0.5 * std::pow((t - _m) / _b, 2));
    }
};

int main(int argc, char const* argv[])
{
    FileManager io_manager;

    Eigen::MatrixXd X = io_manager.setFile("rsc/sphere_mesh.mesh").read<Eigen::MatrixXd>("elements", 2),
                    Y = io_manager.setFile("rsc/joints_icub.csv").read<Eigen::MatrixXd>(),
                    Z = io_manager.setFile("rsc/sphere.msh").read<Eigen::MatrixXd>("$Nodes", 2, "$EndNodes");

    Eigen::VectorXd v = io_manager.setFile("rsc/sphere_mode_01").read<Eigen::MatrixXd>();

    std::cout << "First file begin" << std::endl;
    std::cout << X.block(0, 0, 5, 5) << std::endl;
    std::cout << "First file end" << std::endl;
    std::cout << X.block(X.rows() - 5, 0, 5, 5) << std::endl;

    std::cout << "Second file begin" << std::endl;
    std::cout << Y.block(0, 0, 5, 5) << std::endl;
    std::cout << "Second file end" << std::endl;
    std::cout << Y.block(Y.rows() - 5, Y.cols() - 5, 5, 5) << std::endl;

    std::cout << "Third file begin" << std::endl;
    std::cout << Z.block(0, 0, 4, 4) << std::endl;
    std::cout << "Second file end" << std::endl;
    std::cout << Z.block(Z.rows() - 5, 0, 5, 4) << std::endl;

    std::cout << "Fourth file begin" << std::endl;
    std::cout << v.segment(0, 5) << std::endl;
    std::cout << "Fourth file end" << std::endl;
    std::cout << v.segment(v.rows() - 5, 5) << std::endl;

    // Sigmoid f, g;
    Gaussian f;

    size_t res = 200;
    Eigen::VectorXd x = Eigen::VectorXd::LinSpaced(res, -50, 50), y(res);

    for (size_t i = 0; i < res; i++)
        y(i) = f(x(i));

    io_manager.setFile("outputs/write_file.csv").write("X", x, "Y", y);

    return 0;
}