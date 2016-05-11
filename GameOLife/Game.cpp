#include "stdafx.h"
#include "Game.h"
#include "rlutil.h"
#include <random>
using namespace Biendeo;
using namespace rlutil;

Game::Game(int width, int height) {
	this->height = height;
	this->width = width;
	grid.resize(width);
	for (std::vector<bool> &v : grid) {
		v.resize(height);
	}
}


Game::~Game() {

}


int Game::GetWidth() {
	return width;
}


int Game::GetHeight() {
	return height;
}

bool Game::GetSpace(int x, int y) {
	if (!IsOutOfBound(x, y)) {
		return grid.at(x).at(y);
	} else {
		return false;
	}
}

bool Game::IsOutOfBound(int x, int y) {
	if (x < 0 || x >= width || y < 0 || y >= height) {
		return true;
	} else {
		return false;
	}
}


void Game::NextGeneration() {
	std::vector<std::vector<bool>> nextGeneration = grid;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			int neighbours = 0;
			if (GetSpace(x - 1, y)) {
				neighbours++;
			}
			if (GetSpace(x + 1, y)) {
				neighbours++;;
			}
			if (GetSpace(x, y - 1)) {
				neighbours++;;
			}
			if (GetSpace(x, y + 1)) {
				neighbours++;;
			}
			if (GetSpace(x - 1, y - 1)) {
				neighbours++;
			}
			if (GetSpace(x + 1, y - 1)) {
				neighbours++;
			}
			if (GetSpace(x - 1, y + 1)) {
				neighbours++;
			}
			if (GetSpace(x + 1, y + 1)) {
				neighbours++;
			}

			if (GetSpace(x, y) && (neighbours < 2 || neighbours > 3)) {
				nextGeneration.at(x).at(y) = false;
			} else if (!GetSpace(x, y) && neighbours == 3) {
				nextGeneration.at(x).at(y) = true;
			}
		}
	}
	grid = nextGeneration;
}


void Game::Randomise() {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 2);
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (dist(mt) % 2 == 0) {
				grid.at(x).at(y) = false;
			} else {
				grid.at(x).at(y) = true;
			}
		}
	}
}

bool Game::Toggle(int x, int y) {
	if (!IsOutOfBound(x, y)) {
		if (grid.at(x).at(y)) {
			grid.at(x).at(y) = false;
		} else {
			grid.at(x).at(y) = true;
		}
		return grid.at(x).at(y);
	} else {
		return false;
	}
}

void Game::Draw() {
	locate(1, 1);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (grid.at(x).at(y)) {
				std::cout << "#";
			} else {
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}
}
