#include "Raquette.hpp"

Raquette::Raquette()
{
    solide = {
        { -1, -1, 0.1 }, { -1, 1, 0.1 }, { 1, 1, 0.1 }, { 1, -1, 0.1 },
        { -1, -1, -0.1 }, { -1, 1, -0.1 }, { 1, 1, -0.1 }, { 1, -1, -0.1 }
    };
    X = Axe { { -0.1, 0, 0 }, { 0.1, 0, 0 } };
    Y = Axe { { 0, -0.1, 0 }, { 0, 0.1, 0 } };
    Z = Axe { { 0, 0, -0.1 }, { 0, 0, 0.1 } };
}

void Raquette::tourner(Eigen::Matrix3f matriceDeRotation)
{
    solide = rotation(solide, matriceDeRotation);
    X = Axe { matriceDeRotation * X.debut, matriceDeRotation * X.fin };
    Y = Axe { matriceDeRotation * Y.debut, matriceDeRotation * Y.fin };
    Z = Axe { matriceDeRotation * Z.debut, matriceDeRotation * Z.fin };
}

void Raquette::afficher(SDL_Renderer* renderer, Moteur3D* moteur3D)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    moteur3D->tracerArete(X.debut, X.fin);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    moteur3D->tracerArete(Y.debut, Y.fin);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    moteur3D->tracerArete(Z.debut, Z.fin);

    moteur3D->afficher(solide);
}

Eigen::Matrix3f Raquette::calculerRotations(Donnees donnees, float dt)
{
    float roll = 0, pitch = 0, yaw = 0;
    float roll_accel = atan2(donnees.ay, donnees.az);
    float pitch_accel = atan2(-donnees.ax, sqrt(donnees.ay * donnees.ay + donnees.az * donnees.az));

    roll += donnees.gx * dt;
    pitch += donnees.gy * dt;
    yaw += donnees.gz * dt;

    float alpha = 0.98;
    roll = alpha * roll + (1 - alpha) * roll_accel;
    pitch = alpha * pitch + (1 - alpha) * pitch_accel;

    return rotationZ(yaw) * rotationY(pitch) * rotationX(roll);
}

float Raquette::determinerAngle(float zBalle)
{
    int i = solide[0](2) <= solide[4](2) ? 0 : 4;
    return atan(abs(solide[i](1) - solide[i + 1](1)) / abs(solide[i](2) - zBalle));
}
