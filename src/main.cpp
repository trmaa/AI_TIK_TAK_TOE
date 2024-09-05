#include "grid.hpp"
#include <cstdlib>
#include <iostream>

void play_game() {
    Grid grid;
    grid.display();

    for (int i = 0; i < 5; i++) {
        grid.insert("player");
        grid.display();

        if (grid.gamestate() == "won") {
            std::cout << "\x1B[94mPLAYER WINS\033[0m" << std::endl;
            return;
        }

        grid.insert("ai");
        grid.display();

        if (i > 2) {
            std::cout << "\x1B[94mDRAW\033[0m" << std::endl;
            return;
        }
        if (grid.gamestate() == "lost") {
            std::cout << "\x1B[91mPLAYER LOSES\033[0m" << std::endl;
            return;
        }
    }
}

int main() {
    char play_again;
    do {
        play_game();
        std::cout << "Do you want to play again? (Y/n): ";
        std::cin >> play_again;
    } while (play_again != 'n');

    std::cout << "Thanks for playing!" << std::endl;
}
