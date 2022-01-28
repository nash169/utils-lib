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

#ifndef utils_lib_GRADIENT_CHECKER_HPP
#define utils_lib_GRADIENT_CHECKER_HPP

#include <Eigen/Core>
#include <iostream>

namespace utils_lib {
    class DerivativeChecker {
    public:
        DerivativeChecker(const size_t& dim = 1, const size_t& res = 51) : _dim(dim), _res(res) {}

        DerivativeChecker& setResolution(const size_t& res)
        {
            _res = res;
            return *this;
        }

        DerivativeChecker& setDimension(const size_t& dim)
        {
            _dim = dim;
            return *this;
        }

        Eigen::MatrixXd numericalGradient()
        {
            Eigen::MatrixXd M(_t.rows(), 2);
            M << _t, _G;

            return M;
        }

        Eigen::MatrixXd numericalHessian()
        {
            Eigen::MatrixXd M(_t.rows(), 2);
            M << _t, _H;

            return M;
        }

        // template <typename Function, typename Gradient>
        // bool checkGradient(const Function& f, const Gradient& g)
        // {
        //     // Init G
        //     _G = Eigen::VectorXd::Zero(_res);

        //     // Generate log spaced perturbation intensities
        //     _t = Eigen::VectorXd::LinSpaced(_res, -8, 0);
        //     for (size_t i = 0; i < _t.rows(); i++)
        //         _t(i) = std::pow(10, _t(i));

        //     // Generate random test point and perturbation direction
        //     Eigen::VectorXd x = Eigen::VectorXd::Random(_dim), v = Eigen::VectorXd::Random(_dim);

        //     // Calculate first order Taylor expansion
        //     for (size_t i = 0; i < _t.rows(); i++)
        //         _G(i) = std::abs(f(x + _t(i) * v) - f(x) - _t(i) * g(x).dot(v));

        //     // Transform to log space
        //     _t = _t.array().log();
        //     _G = _G.array().log();

        //     // Calculate mean slope for central values
        //     double mean_slope = 0, num_points = 0;

        //     for (size_t i = 20; i < _res - 20; i++) {
        //         mean_slope = mean_slope + (_G(i + 1) - _G(i)) / (_t(i + 1) - _t(i));
        //         num_points++;
        //     }

        //     mean_slope /= num_points;

        //     std::cout << "First order Taylor expansion slope: " << mean_slope << " - It should be approximately equal to 2.0" << std::endl;

        //     return (std::abs(mean_slope - 2.0) <= 1e-3) ? true : false;
        // }

        template <typename Function, typename Gradient>
        bool checkGradient(Function f, Gradient g, const Eigen::VectorXd& x, const Eigen::VectorXd& v)
        {
            // Init G
            _G = Eigen::VectorXd::Zero(_res);

            // Generate log spaced perturbation intensities
            _t = Eigen::VectorXd::LinSpaced(_res, -8, 0);
            for (size_t i = 0; i < _t.rows(); i++)
                _t(i) = std::pow(10, _t(i));

            // Calculate first order Taylor expansion
            for (size_t i = 0; i < _t.rows(); i++)
                _G(i) = std::abs(f(x + _t(i) * v) - f(x) - _t(i) * g(x).dot(v));

            // Transform to log space
            _t = _t.array().log();
            _G = _G.array().log();

            // Calculate mean slope for central values
            double mean_slope = 0, num_points = 0;

            for (size_t i = 20; i < _res - 20; i++) {
                mean_slope = mean_slope + (_G(i + 1) - _G(i)) / (_t(i + 1) - _t(i));
                num_points++;
            }

            mean_slope /= num_points;

            std::cout << "First order Taylor expansion slope: " << mean_slope << " - It should be approximately equal to 2.0" << std::endl;

            return (std::abs(mean_slope - 2.0) <= 1e-3) ? true : false;
        }

        template <typename Function, typename Gradient>
        bool checkGradient(Function f, Gradient g)
        {
            // Init G
            _G = Eigen::VectorXd::Zero(_res);

            // Generate log spaced perturbation intensities
            _t = Eigen::VectorXd::LinSpaced(_res, -8, 0);
            for (size_t i = 0; i < _t.rows(); i++)
                _t(i) = std::pow(10, _t(i));

            // Generate random test point and perturbation direction
            Eigen::VectorXd x = Eigen::VectorXd::Random(_dim), v = Eigen::VectorXd::Random(_dim);

            // Calculate first order Taylor expansion
            for (size_t i = 0; i < _t.rows(); i++)
                _G(i) = std::abs(f(x + _t(i) * v) - f(x) - _t(i) * g(x).dot(v));

            // Transform to log space
            _t = _t.array().log();
            _G = _G.array().log();

            // Calculate mean slope for central values
            double mean_slope = 0, num_points = 0;

            for (size_t i = 20; i < _res - 20; i++) {
                mean_slope = mean_slope + (_G(i + 1) - _G(i)) / (_t(i + 1) - _t(i));
                num_points++;
            }

            mean_slope /= num_points;

            std::cout << "First order Taylor expansion slope: " << mean_slope << " - It should be approximately equal to 2.0" << std::endl;

            return (std::abs(mean_slope - 2.0) <= 1e-3) ? true : false;
        }

        template <typename Function, typename Gradient, typename Hessian>
        bool checkHessian(const Function& f, const Gradient& g, const Hessian& h)
        {
            // Init G
            _H = Eigen::VectorXd::Zero(_res);

            // Generate log spaced perturbation intensities
            _t = Eigen::VectorXd::LinSpaced(_res, -8, 0);
            for (size_t i = 0; i < _t.rows(); i++)
                _t(i) = std::pow(10, _t(i));

            // Generate random test point and perturbation direction
            Eigen::VectorXd x = Eigen::VectorXd::Random(_dim), v = Eigen::VectorXd::Random(_dim);

            // Calculate second order Taylor expansion
            for (size_t i = 0; i < _t.rows(); i++)
                _H(i) = std::abs(f(x + _t(i) * v) - f(x) - _t(i) * (g(x).transpose() * v));

            // Transform to log space
            _t = _t.array().log();
            _H = _H.array().log();

            // Calculate mean slope for central values
            double mean_slope = 0, num_points = 0;

            for (size_t i = 20; i < _res - 20; i++) {
                mean_slope = mean_slope + (_H(i + 1) - _H(i)) / (_t(i + 1) - _t(i));
                num_points++;
            }

            mean_slope /= num_points;

            std::cout << "Second order Taylor expansion slope: " << mean_slope << " - It should be approximately equal to 3.0" << std::endl;

            return (std::abs(mean_slope - 3.0) <= 1e-3) ? true : false;
        }

    protected:
        size_t _dim, _res;

        Eigen::VectorXd _t, _G, _H;
    };
} // namespace utils_lib

#endif // utils_lib_GRADIENT_CHECKER_HPP