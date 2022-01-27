#include <iostream>
#include <string>
#include <utils_lib/CheckMalloc.hpp>
#include <vector>

struct Object {
    int x, y, z;
};

int main(int argc, char const* argv[])
{
    PrintMemoryUsage();

    {
        // Vectors is just one of the structure not calling
        // with size version of the delete operator. In this
        // case the memory usage cannot be tracked easily
        std::vector<int> temp;

        temp.push_back(1);

        PrintMemoryUsage();
    }

    PrintMemoryUsage();

    Object* obj = new Object;

    PrintMemoryUsage();

    delete obj;

    PrintMemoryUsage();

    return 0;
}