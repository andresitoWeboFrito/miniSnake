#pragma once

#include <iostream>
#include <vector>

using namespace std;

constexpr unsigned int WIDTH = 10;
constexpr unsigned int HEIGHT = 10;

typedef struct
{
	size_t x;
	size_t y;
} Position;

bool isSnake(Position pos, const vector<Position> &snake);
void renderGame(const vector<Position> &snake);

void renderSnake(const vector<Position> &snake);
