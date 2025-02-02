#include <iostream>

const int size {3};

// Function to display the present state of the board using nested for loops that handles both the printing of |, X/O placed and empty characters
void displayBoard(char board[size][size])
{
	std::cout << "----------------------" << std::endl;

	for (int i = 0; i < size; i++)
	{
		std::cout << "  |  ";

		for (int x = 0; x < size; x++)
		{
			std::cout << board[i][x] << "  |  ";
		}

		std::cout << std::endl << "----------------------" << std::endl;
	}
}

// Function comparing each winning condition through for loops and if statements, returning a bool to indicate if a winning condition has been met
bool checkIfWon(char board[size][size], char player)
{
	for (int i = 0; i < size; i++)
	{
		if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
		if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
	}

	if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
	if (board[3][0] == player && board[2][1] == player && board[1][2] == player) return true;

	return false;
}

// Function uses nested for loops to iterate through to find if there are no more empty spaces, meaning no more possible moves 
bool checkIfDraw(char board[size][size])
{
	for (int i = 0; i < size; i++)
	{
		for (int x = 0; x < size; x++)
		{
			if (board[i][x] == ' ') return false;
		}
	}

	return true;
}

int main()
{
	char board[size][size] = {
		{' ', ' ', ' '},
		{' ', ' ', ' '},
		{' ', ' ', ' '}
	};

	char playerCharacter {'X'};
	int row, column;
	bool gameOver = false;

	std::cout << "Welcome to a game of Tic Tac Toe!" << std::endl;

	while (!gameOver)
	{
		displayBoard(board);

		// Asks current player to input their row and column selection, saves it as int and checks if choice is invalid before placing the character
		std::cout << "Player " << playerCharacter << ", which row would you like to select (1-" << size << "):  ";
		std::cin >> row;
		std::cout << "Player " << playerCharacter << ", which column would you like to select (1-" << size << "):  ";
		std::cin >> column;

		if ( board[row - 1][column - 1] != ' ' || row < 1 || row > size || column < 1 || column > size)
		{
			std::cout << "Number might be out of range or the space might be occupied. Try again!" << std::endl;
			continue;
		}

		board[row - 1][column - 1] = playerCharacter;

		// if statements utilizing functions and their return types to check for wins or draws
		if (checkIfWon(board, playerCharacter))
		{
			displayBoard(board);
			std::cout << "Player " << playerCharacter << " has won the game! Congrats!" << std::endl;
			gameOver = !gameOver;
		} else if (checkIfDraw(board))
		{
			displayBoard(board);
			std::cout << "No moves left. Its a draw!" << std::endl;
			gameOver = !gameOver;
		}

		playerCharacter = (playerCharacter == 'X') ? 'O' : 'X';
	}

	return 0;
}
