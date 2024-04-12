#include "shotgun.hh"

// Methods
std::vector<bool> Shotgun::generateBullets(size_t live, size_t blank) {
    // Generates a vector of bools (where true represents )
    std::vector<bool> bulletsVector(live + blank);
    std::fill(bulletsVector.begin(), bulletsVector.begin() + live, true); 
    std::fill(bulletsVector.begin() + live, bulletsVector.end(), false); 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(bulletsVector.begin(), bulletsVector.end(), gen);
    bullets = bulletsVector;
    return bulletsVector;
}

void Shotgun::shuffleBullets() {
    // Shuffle the bullets in the shotgun.
    // Should only be called when the generated bullets from generateBullets() 
    // are "loaded" into the gun.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(bullets.begin(), bullets.end(), gen);
}

bool Shotgun::getChamber() {
    // Returns 
    if (bullets.size() < 1) throw std::runtime_error("Error: No bullets in chamber");
    return bullets.front();
}

void Shotgun::popChamber() {
    if (bullets.size() < 1) throw std::runtime_error("Error: No bullets in chamber");
    bullets.erase(bullets.begin());
}

void Shotgun::sawShotgun() {
    sawedOff = true;
}

void Shotgun::unsawShotgun() {
    sawedOff = false;
}

// Debug
void Shotgun::displayShotgun() {
    if (bullets.size() < 1) throw std::runtime_error("Error: No bullets in chamber");
    std::cout << "[ ";
    for (size_t i = 0; i < bullets.size() - 1; ++i) {
        if (bullets[i]) {
            std::cout << "Live,";
        } else {
            std::cout << "Blank,";
        }
    }
    if (bullets[bullets.size() - 1]) std::cout << "Live " << std::endl;
    else std::cout << "Blank " << std::endl;
}