#pragma once

#include <algorithm>
#include <iostream>
#include <random>

class Shotgun {
  private:
    int damage = 1;
    bool sawedOff = false;
    std::vector<bool> bullets;
  public:
    Shotgun();
    ~Shotgun();

    // Methods
    std::vector<bool> generateBullets(size_t live, size_t blank);
    void shuffleBullets();
    bool getChamber();
    void popChamber();
    void sawShotgun();
    void unsawShotgun();


    // Debug
    void displayShotgun();
};