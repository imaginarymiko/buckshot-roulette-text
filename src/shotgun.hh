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
    int getDamage() const;
    std::vector<bool> getShells() const;
    int getShellAmount() const;
    bool getIthShell(int i) const;
    std::vector<bool> generateShells(size_t live, size_t blank);
    void shuffleShells();
    bool getChamber() const;
    void popChamber();
    void invertChamber();
    void sawShotgun();
    void unsawShotgun();
    bool sawedStatus() const;


    // Debug
    void displayShotgun();
};