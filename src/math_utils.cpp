#include "core/math_utils.hpp"
#include <thread>

namespace core
{
    int add(int a, int b)
    {
        return a + b;
    }

    Eigen::Vector3d sum_vectors(
        const Eigen::Vector3d& a,
        const Eigen::Vector3d& b)
    {
        return a + b;
    }
}