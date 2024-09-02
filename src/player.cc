#include "player.hh"

Player::Player(int player, std::string& name, Player* opponent, Shotgun* s):
    player(player), name(name), health(3), items({}), skipTurn(false), opponent(opponent), s(s) {}

Player::Player(int player, std::string& name, int health, Player* opponent, Shotgun* s):
    player(player), name(name), health(health), items({}), skipTurn(false), opponent(opponent), s(s) {}

Player::~Player() {}

void Player::setOpponent(Player* op) {
    opponent = op;
}

// Virtual Methods
void Player::notify(const Event& e) {
    return;
}

// Methods
int Player::getHealth() const {
    return health;
}

void Player::setHealth(int he) {
    health = he;
}

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

void Player::damageSelf(int damage) {
    health -= damage;
}

bool Player::shootOpponent() {
    // Returns true if the opponent was successfully damaged, false otherwise.
    bool damaged;
    if (s->getChamber()) {
        opponent->damageSelf((s->sawedStatus() ? 2 : 1) * s->getDamage());
        damaged = true;
    } else {
        damaged = false;
    }
    s->unsawShotgun();
    return damaged;
}

bool Player::shootSelf() {
    // Returns true if the player was successfully damaged, false otherwise.
    bool damaged;
    if (s->getChamber()) {
        damageSelf((s->sawedStatus() ? 2 : 1) * s->getDamage());
        damaged = true;
    } else {
        damaged = false;
    }
    s->unsawShotgun();
}

bool Player::skipStatus() {
    return skipTurn;
}

void Player::skipNextTurn() {
    skipTurn = true;
}

void Player::unskipNextTurn() {
    skipTurn = false;
}

// Items
bool Player::itemExists(Items item) const {
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
        return true;
    }
}

bool Player::useHandcuffs() {
    // Causes the opponent to skip their next turn.
    if (!itemExists(Items::Handcuffs)) {
        return false;
    } else {
        opponent->skipNextTurn();
        return true;
    }
}

std::tuple<int, bool> Player::useBurnerPhone() {
    // Gives information on a random shell (except the first), such as whether it
    // is live or blank, and its position
    if (!itemExists(Items::Burner_Phone)) throw std::logic_error("Error: Burner Phone not in inventory.");
    if (s->getShellAmount() < 1) throw std::runtime_error("Error: No shells in chamber");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, s->getShellAmount() - 1);
    int randomIndex = dis(gen);
    return std::make_tuple(randomIndex, s->getIthShell(randomIndex));
}

bool Player::useInverter() {
    // Switches the polarity of the shell in the chamber.
    if (!itemExists(Items::Inverter)) {
        return false;
    } else {
        s->invertChamber();
        return false;
    }
}

bool Player::useAdrenaline(int item) {
    // Allows the user to steal an item of the opponent's, consuming it immediately.
    if ()
}

bool Player::useExpiredMedicine() {
    // 40% of resttoring two points of health, 60% of losing one
    if (!itemExists(Items::Expired_Medicine)) {
        return false;
    } else {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 99);
        int randomNumber = dis(gen);
        if (randomNumber < 40)
            health += 2;
        else
            health -= 1;
        return true;
    }
}
