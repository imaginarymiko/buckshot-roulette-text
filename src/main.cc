#include <chrono>
#include <stdexcept>

#include "dealer.hh"
#include "inputparser.hh"
#include "player.hh"

void printHelp() {
    std::cout << std::endl;
}

void printGame(const Player& p1, const Player& p2, const Shotgun& s) {
    
}

void displayCredits() {
    std::cout << std::endl;
}

int main(int argc, char** argv) {
    std::vector<std::string> validOptions = {"-h", "-help", "-s", "-singleplayer", "-t", "-twoplayer", "-d", "-debug"};
    std::string input;
    bool debug = false; // Allows access to debug commands and disables time delays.
    bool twoPlayer = false; // Disables the AI-controlled player.
    bool endless = false;
    bool p1Turn = false;
    std::string name1;
    std::string name2;
    unsigned long score = 0;
    unsigned int round = 1;
    Shotgun s {};
    try {
        if (argc == 1) {
            std::cout << "Would you like to play singleplayer (s) or with two players (t)?" << std::endl;
            while (true) {
                std::cin >> input;
                toLowercase(input);
                if (input == "s" || input == "single" || input == "singleplayer") {
                    twoPlayer = false;
                    break;
                } else if (input == "t" || input == "two" || input == "twoplayer") {
                    twoPlayer == true;
                    break;
                } else {
                    std::cout << "Error: invalid input." << std::endl;
                    continue;
                }
            }
            std::cout << "Would you like to enable debug mode? (Y/N)" << std::endl;
            while (true) {
                std::cin >> input;
                toLowercase(input);
                if (input == "y" || input == "yes" || input == "d" || input == "debug") {
                    debug = true;
                    break;
                } else if (input == "n" || input == "no") {
                    debug = false;
                    break;
                } else {
                    std::cout << "Error: invalid input." << std::endl;
                    continue;
                }
            }
        } else if (argc > 3) {
            throw std::invalid_argument("Too many arguments");
        } else {
            InputParser ip(argc, argv, validOptions);
            if (ip.optionExists("-h") || ip.optionExists("-help")) {
                displayCredits();
                printHelp();
                return 0;
            }
            if (ip.optionExists("-s") || ip.optionExists("-singleplayer")) {
                twoPlayer = false;
            } else if (ip.optionExists("-t") || ip.optionExists("-twoplayer")) {
                twoPlayer = true;
            }
            if (ip.optionExists("-d") || ip.optionExists("-debug")) {
                debug = false;
            }
        }
        if (twoPlayer) {
            // Get names
            std::cout << "Player 1, enter your name: " << std::endl;
            while (true) {
                std::getline(std::cin, name1);
                if (input == "God" || input == "Dealer") {
                    std::cout << "Error: invalid name." << std::endl;
                    continue;
                } else {
                    name1 = input;
                    break;
                }
            }
            std::cout << "Player 2, enter your name: " << std::endl;
            while (true) {
                std::getline(std::cin, name2);
                if (input == "God" || input == "Dealer") {
                    std::cout << "Error: invalid name." << std::endl;
                    continue;
                } else if (input == name1) {
                    std::cout << "Error: same name as Player 1." << std::endl;
                    continue;
                } else {
                    name2 = input;
                    break;
                }
            }
        } else {
            std::cout << "Will you take the pills (activates endless mode)? (Y/N)" << std::endl;
            while (true) {
                std::cin >> input;
                toLowercase(input);
                if (input == "y" || input == "yes" || input == "p" || input == "pills") {
                    endless = true;
                    break;
                } else if (input == "n" || input == "no") {
                    endless = false;
                    break;
                } else {
                    std::cout << "Error: invalid input." << std::endl;
                    continue;
                }
            }
            // Get name
            std::cout << "Please sign the waiver." << std::endl;
            while (true) {
                std::getline(std::cin, name1);
                if (input == "God" || input == "Dealer") {
                    std::cout << "Error: invalid name." << std::endl;
                    continue;
                } else {
                    name1 = input;
                    name2 = "Dealer";
                    break;
                }
            }
        }
        Player p1 = Player {1, name1, nullptr, &s};
        Player p2 = Player {2, name2, &p1, &s};
        p1.setOpponent(&p2);
        do {
            while (p1.getHealth() > 0 && p2.getHealth() > 0) {
                std::cout << "Game start" << std::endl;
            }
            if (twoPlayer) {
                std::cout << "Congratulations Player " << ((p1.getHealth() > 0) ? 1 : 2) << ", you win!" << std::endl;
                break;
            }
        } while ((round <= 3) && endless);
    } catch (std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        return 1;
    } catch (std::overflow_error& e) {
        std::cerr << "Overflow error: " << e.what() << std::endl;
        return 2;
    } catch (std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        return 3;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return -1;
    }
    displayCredits();
    return 0;
}