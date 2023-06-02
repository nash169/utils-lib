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

#ifndef utils_lib_GRADIENT_CHECKER_HPP
#define utils_lib_GRADIENT_CHECKER_HPP

#include <Eigen/Core>
#include <iostream>

namespace utils_lib {
    template <typename Precision = double>
    class DerivativeChecker {
    public:
        DerivativeChecker(const size_t& in = 1, const size_t& out = 1, const size_t& res = 51) : _in(in), _out(out), _res(res) {}

        DerivativeChecker& setResolution(const size_t& res)
        {
            _res = res;
            return *this;
        }

        DerivativeChecker& setInputDimension(const size_t& dim)
        {
            _in = dim;
            return *this;
        }

        DerivativeChecker& setOutputDimension(const size_t& dim)
        {
            _out = dim;
            return *this;
        }

        Eigen::Matrix<Precision, Eigen::Dynamic, Eigen::Dynamic> numericalGradient()
        {
            Eigen::Matrix<Precision, Eigen::Dynamic, Eigen::Dynamic> M(_t.rows(), 2);
            M << _t, _G;

            return M;
        }

        Eigen::Matrix<Precision, Eigen::Dynamic, Eigen::Dynamic> numericalHessian()
        {
            Eigen::Matrix<Precision, Eigen::Dynamic, Eigen::Dynamic> M(_t.rows(), 2);
            M << _t, _H;

            return M;
        }

        template <typename Function, typename Gradient>
        bool checkGradientMulti(Function f, Gradient g)
        {
            // Generate random test point and perturbation direction
            Eigen::VectorXd x = Eigen::VectorXd::Random(_in), v = Eigen::VectorXd::Random(_in);

            // Init G
            Eigen::MatrixXd G(_out, _res);

            // Generate log spaced perturbation intensities
            _t = Eigen::Matrix<Precision, Eigen::Dynamic, 1>::LinSpaced(_res, -8, 0);
            for (size_t i = 0; i < _t.rows(); i++)
                _t(i) = std::pow(10, _t(i));

            // Calculate first order Taylor expansion
            for (size_t i = 0; i < _t.rows(); i++)
                G.col(i) = f(x + _t(i) * v) - f(x) - _t(i) * g(x) * v;

            // Transform to log space
            _t = _t.array().log();
            G = G.array().abs().log();

            // Calculate mean slope for central values
            Precision mean_slope = 0, num_points = 0;

            for (size_t i = 20; i < _res - 20; i++) {
                mean_slope = mean_slope + (G.col(i + 1) - G.col(i)).mean() / (_t(i + 1) - _t(i));
                num_points++;
            }

            mean_slope /= num_points;

            std::cout << "First order Taylor expansion slope: " << mean_slope << " - It should be approximately equal to 2.0" << std::endl;

            return (std::abs(mean_slope - 2.0) <= 1e-3) ? true : false;
        }

        template <typename Function, typename Gradient, typename Hessian>
        bool checkHessianMulti(Function f, Gradient g, Hessian h)
        {
            // Generate random test point and perturbation direction
            Eigen::VectorXd x = Eigen::VectorXd::Random(_in), v = Eigen::VectorXd::Random(_in);

            // Init H
            Eigen::MatrixXd H(_out, _res);

            // Generate log spaced perturbation intensities
            _t = Eigen::Matrix<Precision, Eigen::Dynamic, 1>::LinSpaced(_res, -8, 0);
            for (size_t i = 0; i < _t.rows(); i++)
                _t(i) = std::pow(10, _t(i));

            // Calculate second order Taylor expansion
            for (size_t i = 0; i < _t.rows(); i++)
                H.col(i) = f(x + _t(i) * v) - f(x) - _t(i) * g(x) * v - 0.5 * std::pow(_t(i), 2) * h(x, v) * v;

            // Transform to log space
            _t = _t.array().log();
            H = H.array().abs().log();

            // Calculate mean slope for central values
            Precision mean_slope = 0, num_points = 0;

            for (size_t i = 30; i < _res - 10; i++) {
                mean_slope = mean_slope + (H.col(i + 1) - H.col(i)).mean() / (_t(i + 1) - _t(i));
                num_points++;
            }

            mean_slope /= num_points;

            std::cout << "Second order Taylor expansion slope: " << mean_slope << " - It should be approximately equal to 3.0" << std::endl;

            return (std::abs(mean_slope - 3.0) <= 1e-3) ? true : false;
        }

        template <typename Function, typename Gradient>
        bool checkGradient(Function f, Gradient g, const Eigen::VectorXd& x, const Eigen::VectorXd& v)
        {
            // Init G
            _G.setZero(_res);

            // Generate log spaced perturbation intensities
            _t = Eigen::Matrix<Precision, Eigen::Dynamic, 1>::LinSpaced(_res, -8, 0);
            for (size_t i = 0; i < _t.rows(); i++)
                _t(i) = std::pow(10, _t(i));

            // Calculate first order Taylor expansion
            for (size_t i = 0; i < _t.rows(); i++)
                _G(i) = std::abs(f(x + _t(i) * v) - f(x) - _t(i) * g(x).dot(v));

            // Transform to log space
            _t = _t.array().log();
            _G = _G.array().log();

            // Calculate mean slope for central values
            Precision mean_slope = 0, num_points = 0;

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
            // Generate random test point and perturbation direction
            Eigen::VectorXd x = Eigen::VectorXd::Random(_in), v = Eigen::VectorXd::Random(_in);

            // Init G
            _G.setZero(_res);

            // Generate log spaced perturbation intensities
            _t = Eigen::Matrix<Precision, Eigen::Dynamic, 1>::LinSpaced(_res, -8, 0);
            for (size_t i = 0; i < _t.rows(); i++)
                _t(i) = std::pow(10, _t(i));

            // Calculate first order Taylor expansion
            for (size_t i = 0; i < _t.rows(); i++)
                _G(i) = std::abs(f(x + _t(i) * v) - f(x) - _t(i) * g(x).dot(v));

            // Transform to log space
            _t = _t.array().log();
            _G = _G.array().log();

            // Calculate mean slope for central values
            Precision mean_slope = 0, num_points = 0;

            for (size_t i = 20; i < _res - 20; i++) {
                mean_slope = mean_slope + (_G(i + 1) - _G(i)) / (_t(i + 1) - _t(i));
                num_points++;
            }

            mean_slope /= num_points;

            std::cout << "First order Taylor expansion slope: " << mean_slope << " - It should be approximately equal to 2.0" << std::endl;

            return (std::abs(mean_slope - 2.0) <= 1e-3) ? true : false;
        }

        template <typename Function, typename Gradient, typename Hessian>
        bool checkHessian(Function f, Gradient g, Hessian h, const Eigen::VectorXd& x, const Eigen::VectorXd& v)
        {
            // Init H
            _H.setZero(_res);

            // Generate log spaced perturbation intensities
            _t = Eigen::Matrix<Precision, Eigen::Dynamic, 1>::LinSpaced(_res, -8, 0);
            for (size_t i = 0; i < _t.rows(); i++)
                _t(i) = std::pow(10, _t(i));

            // Calculate second order Taylor expansion
            for (size_t i = 0; i < _t.rows(); i++)
                _H(i) = std::abs(f(x + _t(i) * v) - f(x) - _t(i) * g(x).dot(v) - 0.5 * std::pow(_t(i), 2) * h(x, v).dot(v));

            // Transform to log space
            _t = _t.array().log();
            _H = _H.array().log();

            // Calculate mean slope for central values
            Precision mean_slope = 0, num_points = 0;

            for (size_t i = 30; i < _res - 10; i++) {
                mean_slope = mean_slope + (_H(i + 1) - _H(i)) / (_t(i + 1) - _t(i));
                num_points++;
            }

            mean_slope /= num_points;

            std::cout << "Second order Taylor expansion slope: " << mean_slope << " - It should be approximately equal to 3.0" << std::endl;

            return (std::abs(mean_slope - 3.0) <= 1e-3) ? true : false;
        }

        template <typename Function, typename Gradient, typename Hessian>
        bool checkHessian(Function f, Gradient g, Hessian h)
        {
            // Generate random test point and perturbation direction
            Eigen::VectorXd x = Eigen::VectorXd::Random(_in), v = Eigen::VectorXd::Random(_in);

            // Init H
            _H.setZero(_res);

            // Generate log spaced perturbation intensities
            _t = Eigen::Matrix<Precision, Eigen::Dynamic, 1>::LinSpaced(_res, -8, 0);
            for (size_t i = 0; i < _t.rows(); i++)
                _t(i) = std::pow(10, _t(i));

            // Calculate second order Taylor expansion
            for (size_t i = 0; i < _t.rows(); i++)
                _H(i) = std::abs(f(x + _t(i) * v) - f(x) - _t(i) * g(x).dot(v) - 0.5 * std::pow(_t(i), 2) * h(x, v).dot(v));

            // Transform to log space
            _t = _t.array().log();
            _H = _H.array().log();

            // Calculate mean slope for central values
            Precision mean_slope = 0, num_points = 0;

            for (size_t i = 30; i < _res - 10; i++) {
                mean_slope = mean_slope + (_H(i + 1) - _H(i)) / (_t(i + 1) - _t(i));
                num_points++;
            }

            mean_slope /= num_points;

            std::cout << "Second order Taylor expansion slope: " << mean_slope << " - It should be approximately equal to 3.0" << std::endl;

            return (std::abs(mean_slope - 3.0) <= 1e-3) ? true : false;
        }

    protected:
        size_t _in, _out, _res;

        Eigen::Matrix<Precision, Eigen::Dynamic, 1> _t, _G, _H;
    };
} // namespace utils_lib

#endif // utils_lib_GRADIENT_CHECKER_HPP