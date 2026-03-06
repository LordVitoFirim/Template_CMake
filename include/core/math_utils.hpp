#pragma once
#include <Eigen/Dense>

namespace core
{
    int add(int a, int b);

    Eigen::Vector3d sum_vectors(
        const Eigen::Vector3d& a,
        const Eigen::Vector3d& b);
}