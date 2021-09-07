#include <iostream>
#include <string>
#include <utils_cpp/UtilsCpp.hpp>

struct Object {
    int x, y, z;
};

int main(int argc, char const* argv[])
{
    PrintMemoryUsage();

    Object* obj = new Object;

    PrintMemoryUsage();

    delete obj;

    PrintMemoryUsage();

    return 0;
}