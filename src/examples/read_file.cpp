#include <utils_cpp/UtilsCpp.hpp>

using namespace utils_cpp;

int main(int argc, char const* argv[])
{
    FileManager io_manager;

    Eigen::MatrixXd X = io_manager.setFile("rsc/torus_mesh.mesh").read<Eigen::MatrixXd>("elements", 2),
                    Y = io_manager.setFile("rsc/joints_icub.csv").read<Eigen::MatrixXd>();

    std::cout << "First file begin" << std::endl;
    std::cout << X.block(0, 0, 5, 5) << std::endl;
    std::cout << "First file end" << std::endl;
    std::cout << X.block(X.rows() - 5, 0, 5, 5) << std::endl;

    std::cout << "Second file" << std::endl;
    std::cout << Y.block(0, 0, 5, 5) << std::endl;
    std::cout << "Second file end" << std::endl;
    std::cout << Y.block(Y.rows() - 5, Y.cols() - 5, 5, 5) << std::endl;

    return 0;
}