#include "player.hh"

Player::Player(int player, std::string& name, Player* opponent, Shotgun* s):
    player(player), name(name), health(3), items({}), skipTurn(false), opponent(opponent), s(s) {}

void Player::setOpponent(Player* op) {
    opponent = op;
}

// Methods
void Player::getNewItems() {
    int itemsPickedUp = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 8);
    while (items.size() < MAX_ITEMS && itemsPickedUp < DRAW_ITEMS) {
        int index = dis(gen);
        Items item;
        switch (index) {
            case 0:
                item = Items::Magnifying_Glass;
                break;
            case 1:
                item = Items::Cigarette_Pack;
                break;
            case 2:
                item = Items::Beer_Can;
                break;
            case 3:
                item = Items::Saw;
                break;
            case 4:
                item = Items::Handcuffs;
                break;
            case 5:
                item = Items::Burner_Phone;
                break;
            case 6:
                item = Items::Inverter;
                break;
            case 7:
                item = Items::Adrenaline;
                break;
            case 8:
                item = Items::Expired_Medicine;
                break;
            default:
                std::cerr << "Error: Invalid index" << std::endl;
        }
        items.push_back(item);
        ++itemsPickedUp;
    }
}

// Items
bool Player::itemExists(Items item) {
    return std::find(items.begin(), items.end(), item) != items.end();
}

int Player::useMagnifyingGlass() {
    // Reveals the shell currently loaded in the shotgun.
    if (!itemExists(Items::Magnifying_Glass)) {
        return -1;
    } else {
        return static_cast<int>(s->getChamber());
    }
}

bool Player::useCigarettePack() {
    // Restores one point of health.
    if (!itemExists(Items::Magnifying_Glass)) {
        return false;
    } else {
        health += 1;
        return true;
    }
}

bool Player::useBeerCan() {
    // Racks the shotgun, ejecting the loaded shell.
    if (!itemExists(Items::Beer_Can)) {
        return false;
    } else {
        s->popChamber();
        return true;
    }
}

bool Player::useSaw() {
    // Converts the shotgun to a sawed-off shotgun for a turn, doubling its damage.
    if (!itemExists(Items::Saw)) {
        return false;
    } else {
        s->sawShotgun();
    }
}

