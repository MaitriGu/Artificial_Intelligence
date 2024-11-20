#include <iostream>
#include <vector>
using namespace std;
int possibleWins(int value, vector<int>& grid) {
if (value == 3) {
if (grid[1] * grid[2] * grid[3] == 18) {
if (grid[1] == 2) return 1;
if (grid[2] == 2) return 2;
if (grid[3] == 2) return 3;
}
if (grid[4] * grid[5] * grid[6] == 18) {
if (grid[4] == 2) return 4;
if (grid[5] == 2) return 5;
if (grid[6] == 2) return 6;
}
if (grid[7] * grid[8] * grid[9] == 18) {
if (grid[7] == 2) return 7;
if (grid[8] == 2) return 8;
if (grid[9] == 2) return 9;
}
if (grid[1] * grid[4] * grid[7] == 18) {
if (grid[1] == 2) return 1;
if (grid[4] == 2) return 4;
if (grid[7] == 2) return 7;
}
if (grid[2] * grid[5] * grid[8] == 18) {
if (grid[2] == 2) return 2;
if (grid[5] == 2) return 5;
if (grid[8] == 2) return 8;
}
if (grid[3] * grid[6] * grid[9] == 18) {
if (grid[3] == 2) return 3;
if (grid[6] == 2) return 6;
if (grid[9] == 2) return 9;
}
if (grid[1] * grid[5] * grid[9] == 18) {
if (grid[1] == 2) return 1;
if (grid[5] == 2) return 5;
if (grid[9] == 2) return 9;
}
if (grid[3] * grid[5] * grid[7] == 18) {
if (grid[3] == 2) return 3;
if (grid[5] == 2) return 5;
if (grid[7] == 2) return 7;
}
} else if (value == 5) {
if (grid[1] * grid[2] * grid[3] == 50) {
if (grid[1] == 2) return 1;
if (grid[2] == 2) return 2;

if (grid[3] == 2) return 3;
}
if (grid[4] * grid[5] * grid[6] == 50) {
if (grid[4] == 2) return 4;
if (grid[5] == 2) return 5;
if (grid[6] == 2) return 6;
}
if (grid[7] * grid[8] * grid[9] == 50) {
if (grid[7] == 2) return 7;
if (grid[8] == 2) return 8;
if (grid[9] == 2) return 9;
}
if (grid[1] * grid[4] * grid[7] == 50) {
if (grid[1] == 2) return 1;
if (grid[4] == 2) return 4;
if (grid[7] == 2) return 7;
}
if (grid[2] * grid[5] * grid[8] == 50) {
if (grid[2] == 2) return 2;
if (grid[5] == 2) return 5;
if (grid[8] == 2) return 8;
}
if (grid[3] * grid[6] * grid[9] == 50) {
if (grid[3] == 2) return 3;
if (grid[6] == 2) return 6;
if (grid[9] == 2) return 9;
}
if (grid[1] * grid[5] * grid[9] == 50) {
if (grid[1] == 2) return 1;
if (grid[5] == 2) return 5;
if (grid[9] == 2) return 9;
}
if (grid[3] * grid[5] * grid[7] == 50) {
if (grid[3] == 2) return 3;
if (grid[5] == 2) return 5;
if (grid[7] == 2) return 7;
}
}
return 0;
}
void displayGrid(vector<int> &grid) {
int count = 0;
for (int i = 1; i < 10; i++) {
if (grid[i] == 2) cout << "- ";
else if (grid[i] == 3) cout << "X ";
else cout << "O ";
count++;
if (count == 3) {
cout << endl;
count = 0;
}
}
}

void placeMove(int position, int value, vector<int> &grid) {
grid[position] = value;
}
bool checkForWin(int value, vector<int> grid) {
if (value == 3) {
return (grid[1] * grid[2] * grid[3] == 27 || grid[4] * grid[5] * grid[6] == 27 ||
grid[7] * grid[8] * grid[9] == 27 || grid[1] * grid[4] * grid[7] == 27 ||
grid[2] * grid[5] * grid[8] == 27 || grid[3] * grid[6] * grid[9] == 27 ||
grid[1] * grid[5] * grid[9] == 27 || grid[3] * grid[5] * grid[7] == 27);
} else if (value == 5) {
return (grid[1] * grid[2] * grid[3] == 125 || grid[4] * grid[5] * grid[6] == 125 ||
grid[7] * grid[8] * grid[9] == 125 || grid[1] * grid[4] * grid[7] == 125 ||
grid[2] * grid[5] * grid[8] == 125 || grid[3] * grid[6] * grid[9] == 125 ||
grid[1] * grid[5] * grid[9] == 125 || grid[3] * grid[5] * grid[7] == 125);
}
return false;
}
int makeMoveOne(vector<int> &grid) {
if (grid[5] == 2) return 5;
if (grid[2] == 2) return 2;
if (grid[4] == 2) return 4;
if (grid[6] == 2) return 6;
if (grid[8] == 2) return 8;
return 0;
}
void game(int turn, int currentPlayer, int opponent, int playerValue, int opponentValue, vector<int>
&grid) {
if (turn > 1) displayGrid(grid);
if (turn > 9) {
cout << "IT'S A DRAW!" << endl;
return;
}
if (checkForWin(opponentValue, grid)) {
if (opponent == 0) cout << "USER WINS!" << endl;
else cout << "COMPUTER WINS!" << endl;
return;
}
if (currentPlayer == 0) {
bool validMove = false;
while (!validMove) {
cout << "Enter your move: ";
int position;
cin >> position;
if (position > 0 && position < 10 && grid[position] == 2) {
placeMove(position, playerValue, grid);
validMove = true;
} else {
cout << "Invalid move, try again." << endl;
}
}
} else {

cout << "COMPUTER'S TURN" << endl;
if (turn == 1) {
placeMove(1, playerValue, grid);
} else {
int winPosition = possibleWins(playerValue, grid);
if (winPosition != 0) {
placeMove(winPosition, playerValue, grid);
} else {
int blockPosition = possibleWins(opponentValue, grid);
if (blockPosition != 0) {
placeMove(blockPosition, playerValue, grid);
} else {
int movePosition = makeMoveOne(grid);
if (movePosition != 0) {
placeMove(movePosition, playerValue, grid);
}
}
}
}
}
game(turn + 1, opponent, currentPlayer, opponentValue, playerValue, grid);
}
int main() {
int playerValue, opponentValue, currentPlayer, opponent;
cout << "Do you want to be 'X' or 'O'? (Enter X or O): ";
char userInput;
cin >> userInput;
if (userInput == 'X' || userInput == 'x') {
playerValue = 3;
opponentValue = 5;
currentPlayer = 0;
opponent = 1;
} else {
playerValue = 5;
opponentValue = 3;
currentPlayer = 1;
opponent = 0;
}
vector<int> grid(10, 2);
game(1, currentPlayer, opponent, playerValue, opponentValue, grid);
return 0;
}