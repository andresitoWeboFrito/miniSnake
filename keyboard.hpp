#pragma once

#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

class Keyboard
{
public:
	Keyboard()
	{
		tcgetattr(STDIN_FILENO, &defaultTerminal);
		termios newTerminal = defaultTerminal;

		defaultFlags = fcntl(STDIN_FILENO, F_GETFL, 0);

		// turn off the need of enter & the showing of the keys
		newTerminal.c_lflag = newTerminal.c_lflag & ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newTerminal);

		int newFlags = defaultFlags | O_NONBLOCK;
		// Make the key input non blocking
		fcntl(STDIN_FILENO, F_SETFL, newFlags);
	}
	~Keyboard()
	{
		// Restore everything to the original state
		tcsetattr(STDIN_FILENO, TCSANOW, &defaultTerminal);
		fcntl(STDIN_FILENO, F_SETFL, defaultFlags);
	}

	char readKey()
	{
		char key;
		if (read(STDIN_FILENO, &key, 1) == 1)
		{
			return key;
		}

		return 0;
	}

private:
	termios defaultTerminal;
	int defaultFlags;
};