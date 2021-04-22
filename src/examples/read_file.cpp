#include <utils_cpp/UtilsCpp.hpp>

using namespace utils_cpp;

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

    return 0;
}