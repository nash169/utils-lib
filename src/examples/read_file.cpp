#include <utils_cpp/UtilsCpp.hpp>

using namespace utils_cpp;

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

    // Eigen::MatrixXd X = io_manager.setFile("rsc/sphere_mesh.mesh").read<Eigen::MatrixXd>("elements", 2),
    //                 Y = io_manager.setFile("rsc/joints_icub.csv").read<Eigen::MatrixXd>(),
    //                 Z = io_manager.setFile("rsc/sphere.msh").read<Eigen::MatrixXd>("$Nodes", 2, "$EndNodes");

    // Eigen::VectorXd v = io_manager.setFile("rsc/sphere_mode_01").read<Eigen::MatrixXd>();

    // std::cout << "First file begin" << std::endl;
    // std::cout << X.block(0, 0, 5, 5) << std::endl;
    // std::cout << "First file end" << std::endl;
    // std::cout << X.block(X.rows() - 5, 0, 5, 5) << std::endl;

    // std::cout << "Second file begin" << std::endl;
    // std::cout << Y.block(0, 0, 5, 5) << std::endl;
    // std::cout << "Second file end" << std::endl;
    // std::cout << Y.block(Y.rows() - 5, Y.cols() - 5, 5, 5) << std::endl;

    // std::cout << "Third file begin" << std::endl;
    // std::cout << Z.block(0, 0, 4, 4) << std::endl;
    // std::cout << "Second file end" << std::endl;
    // std::cout << Z.block(Z.rows() - 5, 0, 5, 4) << std::endl;

    // std::cout << "Fourth file begin" << std::endl;
    // std::cout << v.segment(0, 5) << std::endl;
    // std::cout << "Fourth file end" << std::endl;
    // std::cout << v.segment(v.rows() - 5, 5) << std::endl;

    // Sigmoid f, g;

    // g._a = 5;
    // g._k = 3;
    // g._m = 30;
    Gaussian f;

    size_t res = 200;
    Eigen::VectorXd x = Eigen::VectorXd::LinSpaced(res, -50, 50), y(res);

    for (size_t i = 0; i < res; i++)
        y(i) = f(x(i));
    // y(i) = (x(i) <= 10 ? f(x(i)) : g(x(i)));

    io_manager.setFile("rsc/temp.csv").write("X", x, "Y", y);

    return 0;
}