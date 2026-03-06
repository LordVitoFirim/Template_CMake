#include <iostream>
#include "core/math_utils.hpp"

int main()
{
    std::cout << "2 + 3 = "
              << core::add(2, 3)
              << std::endl;

    Eigen::Vector3d a(1,2,3);
    Eigen::Vector3d b(4,5,6);

    auto c = core::sum_vectors(a, b);

    std::cout << "Vector sum: "
              << c.transpose()
              << std::endl;

    return 0;
}