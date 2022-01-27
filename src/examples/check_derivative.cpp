#include <Eigen/Core>
#include <iostream>

#include <utils_lib/DerivativeChecker.hpp>
#include <utils_lib/FileManager.hpp>

using namespace utils_lib;

template <int size>
struct Function {
    Eigen::Matrix<double, size, size> A = Eigen::MatrixXd::Identity(size, size);

    double operator()(const Eigen::Matrix<double, size, 1>& x) const
    {
        return x.transpose() * A * x;
    }
};

template <int size>
struct Gradient {
    Eigen::Matrix<double, size, size> A = Eigen::MatrixXd::Identity(size, size);

    Eigen::Matrix<double, size, 1> operator()(const Eigen::Matrix<double, size, 1>& x) const
    {
        return 2 * (A * x);
    }
};

int main(int argc, char const* argv[])
{
    constexpr int dim = 3;

    DerivativeChecker checker(dim);

    if (checker.checkGradient(Function<dim>(), Gradient<dim>()))
        std::cout << "The gradient is correct!" << std::endl;

    FileManager io_manager;
    io_manager.setFile("rsc/check_derivative.csv").write("gradient", checker.numericalGradient());
}