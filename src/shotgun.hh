#pragma once

#include <algorithm>
#include <iostream>
#include <random>

class Shotgun {
  private:
    int damage = 1;
    bool sawedOff = false;
    std::vector<bool> shells;
  public:
    Shotgun();
    ~Shotgun();

    // Methods
    int getDamage();
    std::vector<bool> getShells();
    int getShellAmount();
    bool getIthShell(int i);
    std::vector<bool> generateShells(size_t live, size_t blank);
    void shuffleShells();
    bool getChamber();
    void popChamber();
    void invertChamber();
    void sawShotgun();
    void unsawShotgun();
    bool sawedStatus();


    // Debug
    void displayShotgun();
};