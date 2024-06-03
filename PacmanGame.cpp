#include <iostream>
#include <conio.h> // For _getch()
#include <cstdlib>

using namespace std;

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 9;
const char WALL = '#';
const char EMPTY = ' ';
const char PACMAN = 'C';
const char GHOST = 'G';
const char FOOD = '.';
const int MAX_FOOD = 100;

char board[BOARD_HEIGHT][BOARD_WIDTH] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', 'G', '.', '.', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '#', '#', '#', '#', '#', '#', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '#', '#', '#', '#', '#', '#', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '#', '#', '#', '#', '#', '#', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '.', 'C', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};


int pacmanX, pacmanY;
int ghostX, ghostY;


int foodX[MAX_FOOD], foodY[MAX_FOOD];
int numfood = 0;


void renderBoard() {
    system("cls"); 
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}


void initializeGame() {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (board[i][j] == PACMAN) {
                pacmanX = j;
                pacmanY = i;
            } else if (board[i][j] == GHOST) {
                ghostX = j;
                ghostY = i;
            } else if (board[i][j] == FOOD) {
                foodX[numfood] = j;
                foodY[numfood] = i;
                numfood++;
            }
        }
    }
}


void movePacman(char direction) {
    int newX = pacmanX;
    int newY = pacmanY;

    switch (direction) {
        case 'w':
            newY--;
            break;
        case 'a':
            newX--;
            break;
        case 's':
            newY++;
            break;
        case 'd':
            newX++;
            break;
    }


    if (newX >= 0 && newX < BOARD_WIDTH && newY >= 0 && newY < BOARD_HEIGHT && board[newY][newX] != WALL) {
        board[pacmanY][pacmanX] = EMPTY;
        pacmanX = newX;
        pacmanY = newY;
        board[pacmanY][pacmanX] = PACMAN;
    }
}


void moveGhost() {
    int direction = rand() % 4;

    int newX = ghostX;
    int newY = ghostY;

    switch (direction) {
        case 0:
            newY--;
            break;
        case 1:
            newX--;
            break;
        case 2:
            newY++;
            break;
        case 3:
            newX++;
            break;
    }

    if (newX >= 0 && newX < BOARD_WIDTH && newY >= 0 && newY < BOARD_HEIGHT && board[newY][newX] != WALL) {
        board[ghostY][ghostX] = EMPTY;
        ghostX = newX;
        ghostY = newY;
        board[ghostY][ghostX] = GHOST;
    }
}


void checkfoodCollision() {
    for (int i = 0; i < numfood; i++) {
        if (foodX[i] == pacmanX && foodY[i] == pacmanY) {
            board[foodY[i]][foodX[i]] = EMPTY;
    
            for (int j = i; j < numfood - 1; j++) {
                foodX[j] = foodX[j + 1];
                foodY[j] = foodY[j + 1];
            }
            numfood--;
            break;
        }
    }
}


bool GameOver() {
    if (pacmanX == ghostX && pacmanY == ghostY) {
        return true;
    }
    if (numfood == 0) {
        return true;
    }
    return false;
}

int main() {
    char input;

    initializeGame();

    while (true) {
        renderBoard();

        input = _getch();

        checkfoodCollision();

        movePacman(input);

        moveGhost();

        if (GameOver()) {
            renderBoard();
            if (pacmanX == ghostX && pacmanY == ghostY)
                cout << "Game Over! The ghost ate Pacman!" << endl;
            else
                cout << "Congratulations! You won!" << endl;
            break;
        }
    }

    return 0;
}
