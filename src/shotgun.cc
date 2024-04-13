#include "shotgun.hh"

Shotgun::Shotgun():
    damage(1), sawedOff(false), shells({}) {}

Shotgun::~Shotgun() {}

// Methods
int Shotgun::getDamage() {
    return damage;
}

std::vector<bool> Shotgun::getShells() {
    return shells;
}

int Shotgun::getShellAmount() {
    return shells.size();
}

bool Shotgun::getIthShell(int i) {
    return shells[i];
}

std::vector<bool> Shotgun::generateShells(size_t live, size_t blank) {
    // Generates a vector of bools (where true represents a live shell, and
    // false represents a blank shell).
    std::vector<bool> shellsVector(live + blank);
    std::fill(shellsVector.begin(), shellsVector.begin() + live, true); 
    std::fill(shellsVector.begin() + live, shellsVector.end(), false); 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(shellsVector.begin(), shellsVector.end(), gen);
    shells = shellsVector;
    return shellsVector;
}

void Shotgun::shuffleShells() {
    // Shuffle the shells in the shotgun.
    // Should only be called when the generated bullets from generateBullets() 
    // are "loaded" into the gun.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(shells.begin(), shells.end(), gen);
}

bool Shotgun::getChamber() {
    // Returns the shell currently in the chamber.
    if (shells.empty()) throw std::runtime_error("Error: No shells in chamber");
    return shells.front();
}

void Shotgun::popChamber() {
    if (shells.empty()) throw std::runtime_error("Error: No shells in chamber");
    shells.erase(shells.begin());
}

void Shotgun::invertChamber() {
    if (shells.empty()) throw std::runtime_error("Error: No shells in chamber");
    shells.front() = !shells.front();
}

void Shotgun::sawShotgun() {
    sawedOff = true;
}

void Shotgun::unsawShotgun() {
    sawedOff = false;
}

bool Shotgun::sawedStatus() {
    return sawedOff;
}

// Debug
void Shotgun::displayShotgun() {
    if (shells.empty()) throw std::runtime_error("Error: No shells in chamber");
    std::cout << "[ ";
    for (size_t i = 0; i < shells.size() - 1; ++i) {
        if (shells[i]) {
            std::cout << "Live,";
        } else {
            std::cout << "Blank,";
        }
    }
    if (shells[shells.size() - 1]) std::cout << "Live " << std::endl;
    else std::cout << "Blank " << std::endl;
}