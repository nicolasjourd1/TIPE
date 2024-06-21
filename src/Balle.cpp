#include "Balle.hpp"

Balle::Balle(Eigen::Vector3f _position, Eigen::Vector3f _vitesse)
{
    position = _position;
    vitesse = _vitesse;
}

void Balle::afficher(SDL_Renderer* renderer, Moteur3D* moteur3D)
{
    std::vector<Eigen::Vector3f> scaling;
    float scale;
    if (position(2) >= 10.0) {
        scale = 10;
    } else
        scale = 10.0 / (10.0 - position(1));
    for (const auto& point : points) {
        scaling.push_back({ scale * point(0), scale * point(1), scale * point(2) });
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (const auto& arete : aretes) {
        moteur3D->tracerArete(scaling[arete(0)], scaling[arete(1)]);
    }
}

void Balle::translationX(float tx)
{
    position(0) += tx;
    for (Eigen::Vector3f& point : points) {
        point(0) += tx;
    }
}

void Balle::translationY(float ty)
{
    position(1) += ty;
    for (Eigen::Vector3f& point : points) {
        point(1) += ty;
    }
}

void Balle::translationZ(float tz)
{
    position(2) += tz;
    for (Eigen::Vector3f& point : points) {
        point(2) += tz;
    }
}

void Balle::majPosition(float dt, float angle)
{
    if (position(2) >= 3) {
        // la balle a touché le sol
        return;
    } else if (abs(position(1)) > R) {
        Eigen::Vector3f F = { 0, 0, -M * G };
        Eigen::Vector3f a = 1 / M * F;
        Eigen::Vector3f dv = a * dt;
        Eigen::Vector3f dvCorrige = { dv(0), -dv(1), -dv(2) };
        vitesse += dvCorrige;
        translation(dt * vitesse);
        position += dt * vitesse;
    } else {
        vitesse = { 0, cos(angle) * vitesse(1), -sin(angle) * vitesse(2) };
        Eigen::Vector3f F = { 0, 0, -M * G };
        Eigen::Vector3f a = 1 / M * F;
        Eigen::Vector3f dv = a * dt;
        Eigen::Vector3f dvCorrige = { dv(0), -dv(1), -dv(2) };
        vitesse += dvCorrige;
        translation(dt * vitesse);
        position += dt * vitesse;
    }
}

void Balle::translation(Eigen::Vector3f t)
{
    translationX(t(0));
    translationY(t(1));
    translationZ(t(2));
}

void Balle::donnerPosition()
{
    // std::cout << "X:" << position(0) << std::endl;
    std::cout << "Y:" << position(1) << std::endl;
    // std::cout << "Z:" << position(2) << std::endl;
}
