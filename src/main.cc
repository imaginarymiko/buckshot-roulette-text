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
            throw std::invalid_argument("Too many arguments. Argument count: " + argc);
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
            std::cout << "PLAYER 1, SIGN THE WAIVER: " << std::endl;
            while (true) {
                std::getline(std::cin, name1);
                std::string name1lower = name1;
                std::transform(name1lower.begin(), name1lower.end(), name1lower.begin(),
                               [](unsigned char c) -> unsigned char { return std::tolower(c); });
                if (name1lower == "dealer" || name1lower == "god" || name1lower == "satan")
                    std::cout << "INVALID NAME." << std::endl;
                else
                    break;
            }
            std::cout << "PLAYER 2, SIGN THE WAIVER: " << std::endl;
            while (true) {
                std::getline(std::cin, name2);
                std::string name2lower = name2;
                std::transform(name2lower.begin(), name2lower.end(), name2lower.begin(),
                               [](unsigned char c) -> unsigned char { return std::tolower(c); });
                if (name2lower == "dealer" || name2lower == "god" || name2lower == "satan") {
                    std::cout << "INVALID NAME." << std::endl;
                    continue;
                } else if (input == name1) {
                    std::cout << "INVALID NAME: SAME NAME AS PLAYER 1." << std::endl;
                    continue;
                } else {
                    name2 = input;
                    break;
                }
            }
        } else {
            std::cout << "Consume pills (activates endless mode - not recommended for first playthrough)? (Y/N)" << std::endl;
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
            std::cout << "PLEASE SIGN THE WAIVER." << std::endl;
            while (true) {
                std::getline(std::cin, name1);
                if (input == "god" || input == "dealer" || input == "satan") {
                    std::cout << "INVALID NAME." << std::endl;
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
            std::cout << "Game start" << std::endl;
            while (p1.getHealth() > 0 && p2.getHealth() > 0) {
                std::cout << "Receive 4 items" << std::endl;
                p1.getNewItems();
                p2.getNewItems();
            }
            if (twoPlayer) {
                std::cout << "Congratulations Player " << ((p1.getHealth() > 0) ? 1 : 2) << ", you win!" << std::endl;
                break;
            }
        } while ((round <= 3) && endless);
    } catch (std::overflow_error& e) {
        std::cerr << "Overflow error: " << e.what() << std::endl;
        return 1;
    } catch (std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
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