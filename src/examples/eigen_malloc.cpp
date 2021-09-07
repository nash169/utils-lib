#include <utils_cpp/UtilsCpp.hpp>

// Source: https://github.com/stulp/tutorials/blob/master/test.md

int main(int argc, char const* argv[])
{
    Eigen::MatrixXd a = Eigen::MatrixXd::Random(5, 5), b = Eigen::MatrixXd::Random(5, 5), c = Eigen::MatrixXd::Random(5, 5), prealloc;

    ENTERING_REAL_TIME_CRITICAL_CODE
    b += c;

    // a.noalias() += b * c;
    a += b * c;

    prealloc.noalias() = b * c;

    c = prealloc;
    EXITING_REAL_TIME_CRITICAL_CODE

    return 0;
}