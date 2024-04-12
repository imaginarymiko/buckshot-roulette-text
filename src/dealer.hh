#pragma once

#include "player.hh"

class Dealer {
  private:
    Player& p;
  public:
    Dealer(Player& p);
};