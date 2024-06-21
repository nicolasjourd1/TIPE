#include "Moteur3D.hpp"

Moteur3D::Moteur3D(SDL_Window* _window, SDL_Renderer* _renderer)
{
    SDL_GetWindowSize(_window, &wx, &wy);
    renderer = _renderer;
}

void Moteur3D::afficher(std::vector<Eigen::Vector3f> solide)
{
    // afficherAxes(solide);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (auto& arete : aretesPaveDroit) {
        tracerArete(solide[arete(0)], solide[arete(1)]);
    }
}

void Moteur3D::tracerArete(Eigen::Vector3f a, Eigen::Vector3f b, float z)
{
    Eigen::Vector2f debut = projection(b);
    Eigen::Vector2f fin = projection(a);
    SDL_RenderDrawLine(renderer, debut(0) + z, debut(1) + z, fin(0) + z, fin(1) + z);
}

Eigen::Vector2f Moteur3D::projection(Eigen::Vector3f point)
{
    return { wx / 2 + (d * point(0)) / (d + point(1)) * 200,
        wy / 2 + (d * point(2)) / (d + point(1)) * 200 };
}
