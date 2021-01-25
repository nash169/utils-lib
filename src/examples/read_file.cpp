#include <utils_cpp/UtilsCpp.hpp>

using namespace utils_cpp;

int main(int argc, char const* argv[])
{
    FileManager io_manager;

    // Load data
    Eigen::MatrixXd X = io_manager.read<Eigen::MatrixXd>("rsc/joints_icub.csv");

    return 0;
}