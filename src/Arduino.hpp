#ifndef ARDUINO_HPP_
#define ARDUINO_HPP_

#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>

struct Donnees {
    float ax, ay, az, gx, gy, gz;
};

class Arduino {
public:
    Arduino();
    ~Arduino();

    bool estConnecte();
    Donnees obtenirDonnees();
    void lireDonnees(bool afficher);
    void afficherDonnees();
    void verification(int n);

private:
    HANDLE hSerial;
    DCB dcbSerialParams = { 0 };
    bool connexion;
    Donnees donnees;
};

#endif // ARDUINO_HPP_
