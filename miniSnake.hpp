#pragma once
// system libs
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

// user libs
#include "keyboard.hpp"

using namespace std;

constexpr unsigned int WIDTH = 10;
constexpr unsigned int HEIGHT = 10;

typedef struct
{
	size_t x;
	size_t y;
} Position;

enum class Direction
{
	up,
	down,
	left,
	right
};

typedef struct GameData
{
	unsigned int score = 0;
	vector<Position> snake = {{3, 3}, {3, 4}};
	Direction snakeDirection = Direction::left;
};

bool isSnake(Position pos, const vector<Position> &snake);
void renderGame(const vector<Position> &snake);

void renderSnake(const vector<Position> &snake);

void handle_input(GameData &game, const Keyboard &kb);
