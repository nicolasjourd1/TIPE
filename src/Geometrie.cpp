#include "Geometrie.hpp"

Eigen::Matrix3f rotationX(float angle)
{
    Eigen::Matrix3f matrice;
    matrice << 1, 0, 0,
        0, cos(angle), -sin(angle),
        0, sin(angle), cos(angle);
    return matrice;
}

Eigen::Matrix3f rotationY(float angle)
{
    Eigen::Matrix3f matrice;
    matrice << cos(angle), 0, sin(angle),
        0, 1, 0,
        -sin(angle), 0, cos(angle);
    return matrice;
}

Eigen::Matrix3f rotationZ(float angle)
{
    Eigen::Matrix3f matrice;
    matrice << cos(angle), -sin(angle), 0,
        sin(angle), cos(angle), 0,
        0, 0, 1;
    return matrice;
}

std::vector<Eigen::Vector3f> rotation(const std::vector<Eigen::Vector3f>& points, const Eigen::Matrix3f& matriceDeRotation)
{
    std::vector<Eigen::Vector3f> resultat;
    for (const auto& point : points) {
        resultat.push_back(matriceDeRotation * point);
    }
    return resultat;
}
