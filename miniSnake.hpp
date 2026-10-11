#pragma once
// system libs
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>

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
	Up,
	Down,
	Left,
	Right
};

struct GameData
{
	unsigned int score = 0;
	vector<Position> snake = {{3, 3}, {4, 3}};
	Direction snakeDirection = Direction::Left;
	Position fruit = {0, 0};
	bool isFruitValid = false;
	bool playing = true;
};

bool isSnake(Position pos, const vector<Position> &snake);
bool isSnakeHead(Position pos, const vector<Position> &snake);

void renderGame(const GameData &game);

void renderSnake(const vector<Position> &snake, const Position fruit, bool isFruitValid);

void handle_input(GameData &game, Keyboard &kb);
void calcNextSnakePosition(GameData &game);

bool isFruit(Position pos, Position fruitPos);
void checkForChrash(GameData &game);
bool checkCrashWithWall(Position pos, Direction dir);
