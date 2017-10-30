#include "WorldEngine.h"

WorldEngine::WorldEngine() {
	char map_template[MAP_HEIGHT][MAP_WIDTH] = {
		"###############################",
		"#            G                #",
		"### ################ ###### ###",
		"#   #  G   #########      # ###",
		"# # #### # ##    G   #### # # #",
		"# #      # ## ######    # # # #",
		"# #### ### ## #  P   ## # # #G#",
		"# #           ##### ##### ### #",
		"# ###### ####       ##        #",
		"# #  ### ######### ####### ####",
		"# # ##                        #",
		"# # ## ############### ########",
		"#                             #",
		"###############################"
	};

	directions = new int[CHARACTERS_AMOUNT];
	character_coordinates = new int*[CHARACTERS_AMOUNT];
	for (int i = 0; i < CHARACTERS_AMOUNT; i++) {
		directions[i] = 0;
		character_coordinates[i] = new int[2];
	}


	int current_ghost_index = 1;
	apples_left = 0;
	map = new char*[MAP_HEIGHT];
	for (int y = 0; y < MAP_HEIGHT; y++) {
		map[y] = new char[MAP_WIDTH];
		for (int x = 0; x < MAP_WIDTH; x++) {
			map[y][x] = map_template[y][x];

			if (map[y][x] == 'P') {
				character_coordinates[0][0] = x;
				character_coordinates[0][1] = y;
			} else if (map[y][x] == 'G') {
				character_coordinates[current_ghost_index][0] = x;
				character_coordinates[current_ghost_index][1] = y;
				current_ghost_index++;
			} else if (map[y][x] == ' ') {
				apples_left++;
			}
		}
	}

	is_game_over = false;
}


WorldEngine::~WorldEngine() {
}


char** WorldEngine::getMap() {
	return map;
}

int ** WorldEngine::getCharacterCoordinates() {
	return character_coordinates;
}

bool WorldEngine::isGameOver() {
	return is_game_over;
}

bool WorldEngine::isPlayerWins() {
	return apples_left == 0;
}

int WorldEngine::getRandomDirection(int character_index) {
	int character_x = character_coordinates[character_index][0];
	int character_y = character_coordinates[character_index][1];
	int current_direction = directions[character_index];

	int directions[] = { VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT };
	vector<int> available_choises = {};

	if (character_y != 0 && map[character_y - 1][character_x] != '#') {
		available_choises.push_back(VK_UP);
	}
	if (character_y != MAP_HEIGHT - 1 && map[character_y + 1][character_x] != '#') {
		available_choises.push_back(VK_DOWN);
	}
	if (character_x != 0 && map[character_y][character_x - 1] != '#') {
		available_choises.push_back(VK_LEFT);
	}
	if (character_x != MAP_WIDTH - 1 && map[character_y][character_x + 1] != '#') {
		available_choises.push_back(VK_RIGHT);
	}

	if (available_choises.size() != 1) {
		switch (current_direction) {
		case VK_UP:
			available_choises.erase(remove(available_choises.begin(), available_choises.end(), VK_DOWN), available_choises.end());
			break;
		case VK_DOWN:
			available_choises.erase(remove(available_choises.begin(), available_choises.end(), VK_UP), available_choises.end());
			break;
		case VK_LEFT:
			available_choises.erase(remove(available_choises.begin(), available_choises.end(), VK_RIGHT), available_choises.end());
			break;
		case VK_RIGHT:
			available_choises.erase(remove(available_choises.begin(), available_choises.end(), VK_LEFT), available_choises.end());
			break;
		}
	}

	int choise_index = rand() % available_choises.size();
	return available_choises[choise_index];
}

void WorldEngine::tick() {
	for (int character_index = 0; character_index < CHARACTERS_AMOUNT; character_index++) {
		int character_x = character_coordinates[character_index][0];
		int character_y = character_coordinates[character_index][1];
		int character_direction = directions[character_index];
		char character_symbol = character_index == 0 ? 'P' : 'G';

		if (character_index > 0) {
			int random_ghost_direction = getRandomDirection(character_index);
			changeDirection(character_index, random_ghost_direction);
		}

		switch (character_direction) {
		case VK_UP:
			if (character_y != 0 && map[character_y - 1][character_x] != '#') {
				character_coordinates[character_index][1]--;
			}
			break;
		case VK_DOWN:
			if (character_y != MAP_HEIGHT - 1 && map[character_y + 1][character_x] != '#') {
				character_coordinates[character_index][1]++;
			}
			break;
		case VK_LEFT:
			if (character_x != 0 && map[character_y][character_x - 1] != '#') {
				character_coordinates[character_index][0]--;
			}
			break;
		case VK_RIGHT:			
			if (character_x != MAP_WIDTH - 1 && map[character_y][character_x + 1] != '#') {
				character_coordinates[character_index][0]++;
			}
			break;
		}

		if (hasGhostCollisions(PACMAN_CHARACTER_INDEX)) {
			is_game_over = true;
		}
	}

	int pacman_x = character_coordinates[PACMAN_CHARACTER_INDEX][0];
	int pacman_y = character_coordinates[PACMAN_CHARACTER_INDEX][1];
	
	if (map[pacman_y][pacman_x] = ' ') {
		map[pacman_y][pacman_x] = '_';
		apples_left--;
	}
}

void WorldEngine::changeDirection(int character_index, int direction) {
	int character_x = character_coordinates[character_index][0];
	int character_y = character_coordinates[character_index][1];

	switch (direction) {
	case VK_UP:
		if (character_y != 0 && map[character_y - 1][character_x] != '#') {
			directions[character_index] = direction;
		}
		break;
	case VK_DOWN:
		if (character_y != MAP_HEIGHT - 1 && map[character_y + 1][character_x] != '#') {
			directions[character_index] = direction;
		}
		break;
	case VK_LEFT:
		if (character_x != 0 && map[character_y][character_x - 1] != '#') {
			directions[character_index] = direction;
		}
		break;
	case VK_RIGHT:
		if (character_x != MAP_WIDTH - 1 && map[character_y][character_x + 1] != '#') {
			directions[character_index] = direction;
		}
		break;
	}
}

bool WorldEngine::hasGhostCollisions(int character_index) {
	int pacman_x = character_coordinates[character_index][0];
	int pacman_y = character_coordinates[character_index][1];

	for (int i = 1; i < CHARACTERS_AMOUNT; i++) {
		int character_x = character_coordinates[i][0];
		int character_y = character_coordinates[i][1];
	
		if (character_x == pacman_x && character_y == pacman_y) {
			return true;
		}
	}

	return false;
}
