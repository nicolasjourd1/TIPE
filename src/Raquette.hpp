#ifndef RAQUETTE_HPP_
#define RAQUETTE_HPP_

#include <SDL2/SDL.h>
#include <cmath>
#include <eigen3/Eigen/Dense>
#include <vector>
#include <iostream>

#include "Arduino.hpp"
#include "Geometrie.hpp"
#include "Moteur3D.hpp"

class Raquette {
public:
    Raquette();
    void afficher(SDL_Renderer* renderer, Moteur3D* moteur3D);
    void tourner(Eigen::Matrix3f matriceDeRotation);
    Eigen::Matrix3f calculerRotations(Donnees donnees, float dt);
    float determinerAngle(float zBalle);

private:
    std::vector<Eigen::Vector3f> solide;
    Axe X, Y, Z;
};

#endif // RAQUETTE_HPP_
