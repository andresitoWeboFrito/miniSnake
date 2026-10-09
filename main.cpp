#include "miniSnake.hpp"

bool isSnake(Position pos, const vector<Position> &snake)
{
	for (size_t i = 0; i < snake.size(); i++)
	{
		if (pos.x == snake[i].x && pos.y == snake[i].y)
			return true;
	}
	return false;
}
void renderGame(const vector<Position> &snake)
{

	// Print top border
	cout << '+';
	for (size_t i = 0; i < WIDTH; i++)
	{
		cout << "-";
	}
	cout << "+\n";

	// print board
	renderSnake(snake);

	// Print bottom border
	cout << '+';
	for (size_t i = 0; i < WIDTH; i++)
	{
		cout << "-";
	}
	cout << "+\n";
}

void renderSnake(const vector<Position> &snake)
{
	for (size_t y = 0; y < HEIGHT; y++)
	{
		cout << '|';
		for (size_t x = 0; x < WIDTH; x++)
		{
			if (isSnake({x, y}, snake))
			{
				cout << "s";
			}
			else
			{
				cout << " ";
			}
		}
		cout << "|\n";
	}
}

int main()
{
	// get new snake position
	vector<Position> snake = {{2, 3}, {3, 3}, {4, 3}, {4, 4}};

	while (true)
	{
		renderGame(snake);
	}
	return 0;
}