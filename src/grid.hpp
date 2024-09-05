#ifndef GRID_HPP
#define GRID_HPP

#include <string>
#include <vector>

class Grid {
private:
	std::vector<std::string> _cells;

	std::string _o_value = "\x1B[94mO\033[0m";
	std::string _x_value = "\x1B[91mX\033[0m";
	
	int _vertex_ids[4] = {0, 2, 6, 8};
	int _side_ids[4] = {1, 3, 5, 7};
	int _center_id = 4;

	std::string _gamestate = "";

private:
	int _guess_best_spot();

	bool _check_player_win();

	bool _is_cell_ocupied(int id) {
		return (this->_cells[id] == this->_o_value || this->_cells[id] == this->_x_value);
	}
	bool _is_cell_inrange(int id) {
		return (id < this->_cells.size() && id >= 0);
	}

public:
	const std::string& gamestate() { return this->_gamestate; }

	Grid() {
		for (int i = 0; i < 9; i++) {
			this->_cells.push_back(std::to_string(i));
		}
	}

public:
	void display();
	void insert(std::string who = "player");
};

#endif
