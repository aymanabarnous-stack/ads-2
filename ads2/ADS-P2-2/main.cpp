#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "MyHashTable.h"
#include "catch.h"


// Hilfsfunktion zur Passwort-"Hashung" (vereinfachte eigene Funktion)
std::string simpleHash(const std::string& input) {
    unsigned int hash = 0;
    int prime = 31;
    for (char c : input) {
        hash = hash * prime + static_cast<unsigned char>(c);
    }
    std::stringstream ss;
    ss << std::hex << hash;
    return ss.str();
}

int main() {
    MyHashTable db;
    //db.LoadFromFile("passwords.txt");
    Catch::Session().run();
    int choice;
    do {
        std::cout << "\n=== Passwortmanager ===\n"
            << "1. Neuen Eintrag hinzufuegen\n"
            << "2. Login versuchen\n"
            << "3. Webseiten anzeigen\n"
            << "4. Beenden\n> ";
        std::cin >> choice;

        if (choice == 1) {
            std::string site, user, pass;
            std::cout << "Webseite: ";
            std::cin >> site;
            std::cout << "Benutzername: ";
            std::cin >> user;
            std::cout << "Passwort: ";
            std::cin >> pass;
            std::string hashed = simpleHash(pass);
            db.insert({ user, hashed, site });
            std::cout << "Eintrag gespeichert.\n";
        }
        else if (choice == 2) {
            std::string site, user, pass;
            std::cout << "Webseite: ";
            std::cin >> site;
            std::cout << "Benutzername: ";
            std::cin >> user;
            std::cout << "Passwort: ";
            std::cin >> pass;
            std::string hashed = simpleHash(pass);
            if (db.login(site, user, hashed)) {
                std::cout << "Login erfolgreich.\n";
            }
            else {
                std::cout << "Falsche Zugangsdaten.\n";
            }
        }
        else if (choice == 3) {
            db.listEntries();
        }
    } while (choice != 4);
    std::cout << "Passwortdaten gespeichert. Tschuess!\n";
    return 0;
}