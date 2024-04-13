#pragma once

#include <random>
#include <stdexcept>
#include <tuple>

#include "shotgun.hh"

const int DRAW_ITEMS = 4;
const int MAX_ITEMS = 8;

enum class Items { Magnifying_Glass, Cigarette_Pack, Beer_Can, Saw, Handcuffs, Burner_Phone, Inverter, Adrenaline, Expired_Medicine };

class Player {
  private:
    unsigned int player;
    std::string name;
    int health = 3;
    std::vector<Items> items;
    bool skipTurn = false;
    Player* opponent = nullptr;
    Shotgun* s;
  public:
    Player(int player, std::string& name, Player* opponent, Shotgun* s);
    Player(int player, std::string& name, int health, Player* opponent, Shotgun* s);
    ~Player();
    void setOpponent(Player* opponent);

    // Methods
    int getHealth();
    void setHealth(int he);
    void getNewItems();
    void damageSelf(int damage);
    bool shootOpponent();
    bool shootSelf();
    bool skipStatus();
    void skipNextTurn();
    void unskipNextTurn();

    // Items
    bool itemExists(Items item);
    int useMagnifyingGlass();
    bool useCigarettePack();
    bool useBeerCan();
    bool useSaw();
    bool useHandcuffs();
    std::tuple<int, bool> useBurnerPhone();
    bool useInverter();
    bool useAdrenaline();
    bool useExpiredMedicine();
};