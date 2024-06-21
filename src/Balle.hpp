#ifndef BALLE_HPP_
#define BALLE_HPP_

#include <SDL2/SDL.h>
#include <cmath>
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <vector>

#include "Moteur3D.hpp"

const float R = 0.2;
const float COSP4 = cos(M_PI / 4);
const float SINP4 = sin(M_PI / 4);
const float G = 9.81 / 7;
const float M = 0.0027;

class Balle {
public:
    Balle(Eigen::Vector3f position, Eigen::Vector3f vitesse);
    void majPosition(float dt, float angle);
    void translationX(float tx);
    void translationY(float tz);
    void translationZ(float ty);
    void translation(Eigen::Vector3f t);
    void afficher(SDL_Renderer* renderer, Moteur3D* moteur3D);
    float hauteur() { return position(2); };
    void donnerPosition();

private:
    Eigen::Vector3f position;
    Eigen::Vector3f vitesse;
    std::vector<Eigen::Vector3f> points = {
        { R, 0, 0 }, { R * COSP4, 0, R* SINP4 }, { 0, 0, R }, { -R * COSP4, 0, R* SINP4 },
        { -R, 0, 0 }, { -R * COSP4, 0, -R* SINP4 }, { 0, 0, -R }, { R * COSP4, 0, -R* SINP4 },
        { R, 0, 0 }, { R * COSP4, R* SINP4, 0 }, { 0, R, 0 }, { -R * COSP4, R* SINP4, 0 },
        { -R, 0, 0 }, { -R * COSP4, -R* SINP4, 0 }, { 0, -R, 0 }, { R * COSP4, -R* SINP4, 0 }
    };
    const std::vector<Eigen::Vector2i> aretes = {
        { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 0 },
        { 8, 9 }, { 9, 10 }, { 10, 11 }, { 11, 12 }, { 12, 13 }, { 13, 14 }, { 14, 15 }, { 15, 8 }
    };
};

#endif // BALLE_HPP_
