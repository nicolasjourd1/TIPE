#ifndef GEOMETRIE_HPP_
#define GEOMETRIE_HPP_

#include <cmath>
#include <eigen3/Eigen/Dense>
#include <vector>

struct Axe {
    Eigen::Vector3f debut, fin;
};

Eigen::Matrix3f rotationX(float angle);
Eigen::Matrix3f rotationY(float angle);
Eigen::Matrix3f rotationZ(float angle);

std::vector<Eigen::Vector3f> rotation(const std::vector<Eigen::Vector3f>& points, const Eigen::Matrix3f& matriceDeRotation);

float distance(Eigen::Vector3f a, Eigen::Vector3f b);

#endif // GEOMETRIE_HPP_
