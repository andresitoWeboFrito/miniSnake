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
	renderSnake(game.snake, game.fruit);

	// Print bottom border
	cout << '+';
	for (size_t i = 0; i < WIDTH; i++)
	{
		cout << "-";
	}
	cout << "+\n";

	// Print counter

	cout << "Score: " << game.score;
}

// TODO: change name to render objects?
void renderSnake(const vector<Position> &snake, const Position fruit)
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
			else if (isFruit({x, y}, fruit))
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
		game.snakeDirection = Direction::up;
		break;
	case 's':
		game.snakeDirection = Direction::down;
		break;
	case 'a':
		game.snakeDirection = Direction::left;
		break;
	case 'd':
		game.snakeDirection = Direction::right;
		break;
	}
}

void calcNextSnakePosition(GameData &game)
{
	// calc tail position
	size_t j = game.snake.size() - 2;
	for (size_t i = game.snake.size() - 1; i > 0; i--)
	{
		game.snake[i] = game.snake[j];
		j--;
	}

	// head position
	// todo: add collision with borders
	if (game.snakeDirection == Direction::up)
	{
		game.snake[0].y = game.snake[0].y - 1;
	}
	else if (game.snakeDirection == Direction::down)
	{
		game.snake[0].y = game.snake[0].y + 1;
	}
	else if (game.snakeDirection == Direction::left)
	{
		game.snake[0].x = game.snake[0].x - 1;
	}

	else if (game.snakeDirection == Direction::right)
	{
		game.snake[0].x = game.snake[0].x + 1;
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

int main()
{
	Keyboard keyboard;
	GameData game;

	renderGame(game);
	// Main Game Loop
	while (true)
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
	return 0;
}