#include <cstdlib>
#include <iostream>
#include <string>
#include "grid.hpp"

void Grid::display() {
    std::system("clear");

    std::cout << "                 ";
    std::cout << "     |     |     " << std::endl;
    std::cout << "                 ";
    std::cout << "  " << this->_cells[0] << "  |  " << this->_cells[1] << "  |  " << this->_cells[2] << "  " << std::endl;
    std::cout << "                 ";
    std::cout << "     |     |     " << std::endl;
    std::cout << "                 ";
    std::cout << "-----------------" << std::endl;
    std::cout << "                 ";
    std::cout << "     |     |     " << std::endl;
    std::cout << "                 ";
    std::cout << "  " << this->_cells[3] << "  |  " << this->_cells[4] << "  |  " << this->_cells[5] << "  " << std::endl;
    std::cout << "                 ";
    std::cout << "     |     |     " << std::endl;
    std::cout << "                 ";
    std::cout << "-----------------" << std::endl;
    std::cout << "                 ";
    std::cout << "     |     |     " << std::endl;
    std::cout << "                 ";
    std::cout << "  " << this->_cells[6] << "  |  " << this->_cells[7] << "  |  " << this->_cells[8] << "  " << std::endl;
    std::cout << "                 ";
    std::cout << "     |     |     " << std::endl; 
}

void Grid::insert(std::string who) {
    int id;
    if (who == "player") {
        std::cout << "Pick one: ";
        std::cin >> id;
    } else {
        id = this->_guess_best_spot();
    }

    if (this->_is_cell_inrange(id)) {
        if (this->_is_cell_ocupied(id)) {
            std::cerr << who << ", that is already picked" << std::endl;
            this->insert(who);
        }
        this->_cells[id] = who == "player" ? this->_o_value : this->_x_value;

        if (who == "player") {
            if (this->_check_player_win()) {
                this->_gamestate = "won";
                return;
            }
        }
    } else {
        std::cerr << who << ", id out of range!!!" << std::endl;
        this->insert(who);
    }
}

bool Grid::_check_player_win() {
    int winning_combinations[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    for (const auto& combination : winning_combinations) {
        int a = combination[0], b = combination[1], c = combination[2];
        if (this->_cells[a] == this->_o_value && this->_cells[b] == this->_o_value && this->_cells[c] == this->_o_value) {
            return true;
        }
    }
    return false;
}

int Grid::_guess_best_spot() {
    int winning_combinations[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    for (const auto& combination : winning_combinations) {
        int a = combination[0], b = combination[1], c = combination[2];
        if (this->_cells[a] == this->_x_value && this->_cells[b] == this->_x_value && !_is_cell_ocupied(c)) {
            this->_gamestate = "lost";
            return c;
        }
        if (this->_cells[a] == this->_x_value && this->_cells[c] == this->_x_value && !_is_cell_ocupied(b)) {
            this->_gamestate = "lost";
            return b;
        }
        if (this->_cells[b] == this->_x_value && this->_cells[c] == this->_x_value && !_is_cell_ocupied(a)) {
            this->_gamestate = "lost";
            return a;
        }
    }

    for (const auto& combination : winning_combinations) {
        int a = combination[0], b = combination[1], c = combination[2];
        if (this->_cells[a] == this->_o_value && this->_cells[b] == this->_o_value && !_is_cell_ocupied(c)) {
            return c;
        }
        if (this->_cells[a] == this->_o_value && this->_cells[c] == this->_o_value && !_is_cell_ocupied(b)) {
            return b;
        }
        if (this->_cells[b] == this->_o_value && this->_cells[c] == this->_o_value && !_is_cell_ocupied(a)) {
            return a;
        }
    }

    for (int side : this->_side_ids) {
        if (_is_cell_ocupied(side)) {
            if (!_is_cell_ocupied(this->_center_id)) {
                return this->_center_id;
            }
        }
    }
    
    for (int vertex : this->_vertex_ids) {
        if (_is_cell_ocupied(vertex)) {
            for (int vertex2 : this->_vertex_ids) {
                if (!_is_cell_ocupied(vertex2)) {
                    return vertex2;
                }
            }
        }
    }

    if (!_is_cell_ocupied(this->_center_id)) {
        return this->_center_id;
    }

    for (int vertex : this->_vertex_ids) {
        if (!_is_cell_ocupied(vertex)) {
            return vertex;
        }
    }

    for (int side : this->_side_ids) {
        if (!_is_cell_ocupied(side)) {
            return side;
        }
    }

    return -1;
}
