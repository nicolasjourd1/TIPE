#include <SDL2/SDL.h>
#include <chrono>
#include <eigen3/Eigen/Dense>
#include <iostream>

#include "Arduino.hpp"
#include "Balle.hpp"
#include "Geometrie.hpp"
#include "Moteur3D.hpp"
#include "Raquette.hpp"

int main(int argc, char** argv)
{
    Arduino arduino = Arduino();
    if (!arduino.estConnecte()) {
        std::cerr << "Arduino non connectée !" << std::endl;
        return 1;
    }
    arduino.verification(10);

    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

    Raquette raquette = Raquette();
    // Paramètres à changer (position initiale , vitesse initiale)
    Balle balle = Balle({ 0, 0, 0 }, { 0, 0, 0 });

    bool execution = true;
    SDL_Window* window;
    SDL_Renderer* renderer;
    window = SDL_CreateWindow("TIPE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Moteur3D moteur3D = Moteur3D(window, renderer);

    // Test de contact de la balle en fonction de l'angle.
    // float angleContact = M_PI / 6;
    // Eigen::Matrix3f rotationContact = rotationZ(0) * rotationY(0) * rotationX(angleContact);
    // raquette.tourner(rotationContact);

    while (execution) {
        Donnees donnees = arduino.obtenirDonnees();
        auto t2 = std::chrono::steady_clock::now();
        float dt = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        t1 = t2;

        raquette.tourner(raquette.calculerRotations(donnees, dt / 1000));
        balle.majPosition(dt / 1000, raquette.determinerAngle(balle.hauteur()));

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        raquette.afficher(renderer, &moteur3D);
        balle.afficher(renderer, &moteur3D);

        SDL_RenderPresent(renderer);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_r) {
                    raquette = Raquette();
                }
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    execution = false;
                    // balle.donnerPosition();
                    break;
                }
            } else if (event.type == SDL_QUIT) {
                execution = false;
                // balle.donnerPosition();
                break;
            }
        }
    }

    return 0;
}
