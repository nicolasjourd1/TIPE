#ifndef MOTEUR3D_HPP_
#define MOTEUR3D_HPP_

#include <SDL2/SDL.h>
#include <cmath>
#include <eigen3/Eigen/Dense>
#include <vector>

class Moteur3D {
public:
    Moteur3D(SDL_Window* window, SDL_Renderer* renderer);
    void afficher(std::vector<Eigen::Vector3f> solide);
    void tracerArete(Eigen::Vector3f a, Eigen::Vector3f b, float z = 0.0);
    Eigen::Vector2f projection(Eigen::Vector3f point);

private:
    float d = 10.0; // distance au solide
    int wx, wy; // longueur et largeur de la fenêtre
    /*
               1 -- -- -- -- 2
              /|            /|
             / |           / |
            0 -| -- -- -- 3  |
            |  5 -- -- -- |- 6
            | /           | /
            |/            |/
            4 -- -- -- -- 7
    */
    const std::vector<Eigen::Vector2i> aretesPaveDroit = {
        { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 }, // face 1
        { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 }, // face 2
        { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 }, // laison des faces
    };
    SDL_Renderer* renderer;
};

#endif // MOTEUR3D_HPP_
