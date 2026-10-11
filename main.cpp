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
void renderGame(const GameData &game)
{
	// clear the screen
	cout << "\033[2J\033[H" << flush;
	// Print top border
	cout << '+';
	for (size_t i = 0; i < WIDTH; i++)
	{
		cout << "-";
	}
	cout << "+\n";

	// print board
	renderSnake(game.snake, game.fruit, game.isFruitValid);

	// Print bottom border
	cout << '+';
	for (size_t i = 0; i < WIDTH; i++)
	{
		cout << "-";
	}
	cout << "+\n";

	// Print counter

	cout << "Score: " << game.score << "\n";
}

// TODO: change name to render objects?
void renderSnake(const vector<Position> &snake, const Position fruit, bool isFruitValid)
{
	for (size_t y = 0; y < HEIGHT; y++)
	{
		cout << '|';
		for (size_t x = 0; x < WIDTH; x++)
		{
			if (isSnakeHead({x, y}, snake))
			{
				cout << "Ö";
			}
			else if (isSnake({x, y}, snake))
			{
				cout << "s";
			}
			else if (isFruit({x, y}, fruit) && isFruitValid)
			{
				cout << "*";
			}
			else
			{
				cout << " ";
			}
		}
		cout << "|\n";
	}
}
void handle_input(GameData &game, Keyboard &kb)
{
	char key = kb.readKey();

	switch (key)
	{
	case 'w':
		game.snakeDirection = Direction::Up;
		break;
	case 's':
		game.snakeDirection = Direction::Down;
		break;
	case 'a':
		game.snakeDirection = Direction::Left;
		break;
	case 'd':
		game.snakeDirection = Direction::Right;
		break;
	}
}

void calcNextSnakePosition(GameData &game)
{
	// Last position of the vector is vector[ vector.size - 1]
	// calc tail position
	size_t j = game.snake.size() - 2;
	for (size_t i = game.snake.size() - 1; i > 0; i--)
	{
		game.snake[i] = game.snake[j];
		j--;
	}

	// head position
	if (checkCrashWithWall(game.snake[0], game.snakeDirection))
	{
		game.playing = false;
		return;
	}
	else
	{
		if (game.snakeDirection == Direction::Up)
		{
			game.snake[0].y = game.snake[0].y - 1;
		}
		else if (game.snakeDirection == Direction::Down)
		{
			game.snake[0].y = game.snake[0].y + 1;
		}
		else if (game.snakeDirection == Direction::Left)
		{
			game.snake[0].x = game.snake[0].x - 1;
		}

		else if (game.snakeDirection == Direction::Right)
		{
			game.snake[0].x = game.snake[0].x + 1;
		}
	}
}

void generateFruit(GameData &game)
{
	// Generate the fruit at a random usign the rand()
	// todo? change it to use the more modern <random> lib?

	game.fruit.x = rand() % WIDTH;
	game.fruit.y = rand() % HEIGHT;

	game.isFruitValid = true;
}

bool isFruit(Position pos, Position fruitPos)
{
	if (pos.x == fruitPos.x && pos.y == fruitPos.y)
	{
		return true;
	}
	return false;
}

void updateFruit(GameData &game)
{
	// check for collision between the fruit and the snake
	if (game.fruit.x == game.snake[0].x && game.fruit.y == game.snake[0].y)
	{
		game.isFruitValid = false;
		// the idea is to add one segment more to the snake, but the position shouldn't matter as it will be overwriten when calculating the new nake position
		game.snake.push_back({0, 0});
		game.score++;
	}
}

bool isSnakeHead(Position pos, const vector<Position> &snake)
{
	if (pos.x == snake[0].x && pos.y == snake[0].y)
		return true;
	return false;
};

void checkForChrash(GameData &game)
{
	// check if the snake chrased into itself or into the wall

}

bool checkCrashWithWall(Position pos, Direction dir)
{
	if (pos.y == 0 && dir == Direction::Up)
		return true;
	else if (pos.y == HEIGHT && dir == Direction::Down)
		return true;
	else if (pos.x == 0 && dir == Direction::Left)
		return true;
	else if (pos.x == WIDTH && dir == Direction::Right)
		return true;
	else
		return false;
}
int main()
{
	Keyboard keyboard;
	GameData game;

	// Main Game Loop
	renderGame(game);

	while (game.playing)
	{
		// parse user input
		handle_input(game, keyboard);

		//  check the fruit is eaten? and make the snake bigger
		updateFruit(game);

		// new snake position / points
		calcNextSnakePosition(game);

		// generate the Fruit?
		if (!game.isFruitValid)
		{
			generateFruit(game);
		}

		// render game
		renderGame(game);

		this_thread::sleep_for(chrono::milliseconds(500));
	}

	// Gameover message:
	cout << "Game over! Your score is: " << game.score << endl;

	return 0;
}
