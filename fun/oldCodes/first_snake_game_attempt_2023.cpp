#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

enum Direction { NONE, UP, DOWN, LEFT, RIGHT };

int GAMESPEED = 250;

void clearcmd() {
	system("cls");
}

void sleep(int ms) { // milliseconds
	Sleep(ms);
}

Direction getArrowKey() {
	if (_kbhit()) { // Check if a key has been pressed
		int ch = _getch(); // Get the key code
		if (ch == 0 || ch == 224) { // Arrow keys return a two-part code: 0 or 224 followed by the actual key code
			ch = _getch(); // Get the actual key code
			switch (ch) {
			case 72: return UP;    
			case 80: return DOWN;  
			case 75: return LEFT;  
			case 77: return RIGHT; 
			default: return NONE;  
			}
		}
		else {
			return NONE; // Some other key
		}
	}
	return NONE; // No key pressed
}

class SnakeGame {
private:
	std::random_device rd;
	std::uniform_int_distribution<int> uid, uid2;
	
	std::vector< std::vector<int> > board;
	std::vector< std::pair<int, int> > tailParts;
	std::string ground;
	int headPos[2];
	int snakeLen;

public:
	SnakeGame(int xDim, int yDim) :board(yDim, std::vector<int>(xDim, 0)), snakeLen(1) {

		uid = std::uniform_int_distribution<int>(1, xDim - 1); // to start from 1 block inside the board
		uid2 = std::uniform_int_distribution<int>(1, yDim - 1);

		headPos[0] = uid(rd); // x 
		headPos[1] = uid2(rd); // y 

		tailParts.push_back({ headPos[0] - 1, headPos[1] });

		board[headPos[1]][headPos[0]] = 1; 
		board[tailParts[0].second][tailParts[0].first] = 2; 

		for (int y = 0; y < board[0].size(); y++) {
			ground.append("|___");
		}
		ground.append("|\n");

		foodspawn();
		board_render();
	}

	int* foodspawn() {
		uid = std::uniform_int_distribution<int>(0, board[0].size() - 1);
		uid2 = std::uniform_int_distribution<int>(0, board.size() - 1);
		int* foodPos = new int[2];

		foodPos[0] = uid(rd); 
		foodPos[1] = uid2(rd); 

		while (board[foodPos[1]][foodPos[0]] != 0) {
			foodPos[0] = uid(rd); 
			foodPos[1] = uid2(rd); 
		}

		board[foodPos[1]][foodPos[0]] = 3;
		return foodPos;
	}

	void updateBoard(Direction dir) {

		int previousPart[2] = { headPos[0], headPos[1] };//the one that will be moved to heads old place


		for (size_t i = 0; i < snakeLen; i++) {
			std::pair<int, int>& currentPart = tailParts[i];
			int temp[2] = { currentPart.first, currentPart.second };
			currentPart = { previousPart[0], previousPart[1] };
			previousPart[0] = temp[0];
			previousPart[1] = temp[1];
		}

		if (dir == UP) {
			headPos[1]--;
		}
		else if (dir == DOWN) {
			headPos[1]++;
		}
		else if (dir == RIGHT) {
			headPos[0]++;
		}
		else if (dir == LEFT) {
			headPos[0]--;
		}

		if (checkGameState()) {

			if (board[headPos[1]][headPos[0]] == 3) { // food is eaten, snake will gain +1 part
				// std::pair<int, int>& pt = tailParts.back();
				tailParts.push_back({ previousPart[0],previousPart[1] }); // coordinates don't matter; it will be placed behind the last part when the loop is done
				snakeLen++;
				int* preFood = foodspawn();
				//board[*(preFood)][*(preFood + 1)] = 0; // removing old food is not really neccesary  beacuse the tails go over it and it vanishes anyway
				//(but removing it feels safer)
			}

			// Clear previous head and tail positions
			board[previousPart[1]][previousPart[0]] = 0;
			for (size_t i = 0; i < snakeLen; i++) {
				board[tailParts[i].second][tailParts[i].first] = 0;
			}

			// Update board with new head and tail positions
			board[headPos[1]][headPos[0]] = 1;
			for (size_t i = 0; i < snakeLen; i++) {
				board[tailParts[i].second][tailParts[i].first] = 2;

			}
		}
		else {
			return;
		}
	}

	boolean checkGameState() {

		if (headPos[0] >= board[0].size() || headPos[0] < 0 || headPos[1] >= board.size() || headPos[1] < 0
			|| board[headPos[1]][headPos[0]] == 2) {//if you go out of the map or eat your tail you lose

			std::cout << "\tSorry you have lost \n \t  Your score:" << snakeLen + 1;
			return false;

		}
		else if (snakeLen == board[0].size() * board.size() - 1) {
			std::cout << "\tCongrats you WIN !\n \t  Your score:" << snakeLen + 1;
			return false;
		}
		else {
			return true;
		}

	}

	void board_render() {
		for (int y = 0; y < board[0].size() + 3; y++) {
			std::cout << " __";
		}
		std::cout << "\n";

		for (int x = 0; x < board.size(); x++) {
			for (int y = 0; y < board[0].size(); y++) {
				if (board[x][y] == 0) {
					std::cout << "|   ";
				}
				else if (board[x][y] == 1) {
					std::cout << "| \033[38;5;208m0\033[0m "; // Head - Orange
				}
				else if (board[x][y] == 2) {
					std::cout << "| \033[32m-\033[0m "; // Body - Green
				}
				else if (board[x][y] == 3) {
					std::cout << "| \033[38;5;196m*\033[0m "; // Food - Red
				}
			}
			std::cout << "|\n";
			std::cout << ground;
		}
	}

	void run() {
		std::cout << "\n\n\tPRESS AN ARROW KEY TO START";
		Direction preDir;
		Direction dir = NONE;

		while (dir == NONE) {
			dir = getArrowKey();
			sleep(10);
		}

		while (true) {

			if (dir != NONE) {
				preDir = dir;
			}

			dir = getArrowKey();

			if (checkGameState()) {

				if (dir != NONE && dir != preDir) {//if you press the same key it will call 1 more time so it will move 1 more block this should be like that
					updateBoard(dir);
				}
				else if (dir == NONE) {//no arrow keys is used it will move along with previous direction  
					updateBoard(preDir);
				}

				sleep(GAMESPEED);//adjust the speed here 
				clearcmd();
				board_render();

			}

			else { 
				return;
			}


		}


	}

};

int main() {

	SnakeGame* game;
	int x, y;
	char choice;
	
	do{
		std::cout << "\nEnter  x dimension: ";
		std::cin >> x;
		std::cout << "Enter y dimension: ";
		std::cin >> y;
		std::cout << "Enter game speed (recommended speed is 200-300) ";
		std::cin >> GAMESPEED;

		game = new SnakeGame(x, y);
		game->run();

		delete game; 

		std::cout << "\nDo you want to play again? (y/n): ";
		choice = getch();
	} while (choice == 'y' || choice == 'Y');

	return 0;
}
