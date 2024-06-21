#include "Arduino.hpp"

Arduino::Arduino()
{
    hSerial = CreateFileA(
        "COM3", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Erreur lors de l'ouverture du port série" << std::endl;
        connexion = false;
        return;
    }
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Erreur lors de la récupération des paramètres du port série" << std::endl;
        CloseHandle(hSerial);
        connexion = false;
        return;
    }
    dcbSerialParams.BaudRate = CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Erreur lors de la configuration du port série" << std::endl;
        CloseHandle(hSerial);
        connexion = false;
        return;
    }
    connexion = true;
    lireDonnees(false);
}

Arduino::~Arduino()
{
    CloseHandle(hSerial);
}

bool Arduino::estConnecte()
{
    return connexion;
}

void Arduino::lireDonnees(bool afficher)
{
    DWORD octetsLus;
    char buffer[64];
    std::string donnees_str;

    ReadFile(hSerial, buffer, sizeof(buffer), &octetsLus, NULL);

    while (true) {
        if (ReadFile(hSerial, buffer, 1, &octetsLus, NULL) && octetsLus > 0) {
            if (buffer[0] == '\n') {
                break;
            } else if (buffer[0] != '\r') {
                donnees_str += buffer[0];
            }
        }
    }
    if (afficher) {
        std::cout << donnees_str << std::endl;
    }
    sscanf(donnees_str.c_str(), "rduino:%f,%f,%f,%f,%f,%f",
        &donnees.ax, &donnees.ay, &donnees.az, &donnees.gx, &donnees.gy, &donnees.gz);
}

Donnees Arduino::obtenirDonnees()
{
    lireDonnees(false);
    return donnees;
}

void Arduino::afficherDonnees()
{
    std::cout << "Accélération X: " << donnees.ax << std::endl;
    std::cout << "Accélération Y: " << donnees.ay << std::endl;
    std::cout << "Accélération Z: " << donnees.az << std::endl;
    std::cout << "Vitesse angulaire X: " << donnees.gx << std::endl;
    std::cout << "Vitesse angulaire X: " << donnees.gy << std::endl;
    std::cout << "Vitesse angulaire X: " << donnees.gz << std::endl;
}

void Arduino::verification(int n)
{
    for (int i = 0; i < n; i++) {
        std::cout << "Lecture " << i << std::endl;
        lireDonnees(true);
        std::cout << donnees.ax << ",";
        std::cout << donnees.ay << ",";
        std::cout << donnees.az << ",";
        std::cout << donnees.gx << ",";
        std::cout << donnees.gy << ",";
        std::cout << donnees.gz << "," << std::endl;
    }
}
