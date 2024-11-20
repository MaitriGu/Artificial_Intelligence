#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const vector<int> magicSquare = {0, 8, 1, 6, 3, 5, 7, 4, 9, 2};
void printGrid(const vector<int>& grid) {
for (int i = 1; i <= 9; ++i) {
if (grid[i] == 0) cout << i << " ";
else if (grid[i] == 1) cout << "X ";
else if (grid[i] == 2) cout << "O ";
if (i % 3 == 0) cout << endl;
}
cout << endl;
}
bool checkWin(const vector<int>& moves) {
vector<vector<int>> winCombos = {
{1, 2, 3}, {4, 5, 6}, {7, 8, 9},
{1, 4, 7}, {2, 5, 8}, {3, 6, 9},
{1, 5, 9}, {3, 5, 7}
};
for (const auto& combo : winCombos) {
int sum = 0;
int count = 0;
for (int pos : combo) {
if (moves[pos]) {
sum += magicSquare[pos];
count++;
}
}
if (count == 3 && sum == 15) {
return true;
}
}
return false;
}
void placeMove(int pos, int player, vector<int>& grid, vector<int>& moves) {
grid[pos] = player;
moves[pos] = 1;
}
int possibleWin(const vector<int>& aiMoves,const vector<int>& grid) {
vector<vector<int>> winCombos = {
{1, 2, 3}, {4, 5, 6}, {7, 8, 9},

{1, 4, 7}, {2, 5, 8}, {3, 6, 9},
{1, 5, 9}, {3, 5, 7}
};
for (const auto& combo : winCombos) {
int sumAI = 0;
int emptyPos = 0;
int countAI = 0;
for (int pos : combo) {
if (aiMoves[pos]) {
sumAI += magicSquare[pos];
countAI++;
} else if (grid[pos] == 0) {
emptyPos = pos;
}
}
if (countAI == 2 && emptyPos != 0) {
int missingNumber = 15 - sumAI;
if (magicSquare[emptyPos] == missingNumber) {
return emptyPos;
}
}
}
return 0;
}
int blockOpponent(const vector<int>& playerMoves, const vector<int>& grid) {
vector<vector<int>> winCombos = {
{1, 2, 3}, {4, 5, 6}, {7, 8, 9},
{1, 4, 7}, {2, 5, 8}, {3, 6, 9},
{1, 5, 9}, {3, 5, 7}
};
for (const auto& combo : winCombos) {
int sumPlayer = 0;
int emptyPos = 0;
int countPlayer = 0;
for (int pos : combo) {
if (playerMoves[pos]) {
sumPlayer += magicSquare[pos];
countPlayer++;
} else if (grid[pos] == 0) {
emptyPos = pos;
}
}
if (countPlayer == 2 && emptyPos != 0) {
int missingNumber = 15 - sumPlayer;
if (magicSquare[emptyPos] == missingNumber) {
return emptyPos;
}
}
}
return 0;
}

int bestStrategicMove(const vector<int>& grid) {
if (grid[5] == 0) return 5;
vector<int> corners = {1, 3, 7, 9};
for (int corner : corners) {
if (grid[corner] == 0) return corner;
}
vector<int> edges = {2, 4, 6, 8};
for (int edge : edges) {
if (grid[edge] == 0) return edge;
}
return 0;
}
void computerTurn(vector<int>& grid, vector<int>& aiMoves, vector<int>& playerMoves) {
int move = 0;
move = possibleWin(aiMoves, grid);
if (move) {
placeMove(move, 2, grid, aiMoves);
cout << "Computer places at position " << move << " to win." << endl;
return;
}
move = blockOpponent(playerMoves, grid);
if (move) {
placeMove(move, 2, grid, aiMoves);
cout << "Computer places at position " << move << " to block." << endl;
return;
}
move = bestStrategicMove(grid);
if (move) {
placeMove(move, 2, grid, aiMoves);
cout << "Computer places at position " << move << "." << endl;
}
}
bool isDraw(const vector<int>& grid) {
return all_of(grid.begin() + 1, grid.end(), [](int val) { return val != 0; });
}
int main() {
vector<int> grid(10, 0);
vector<int> playerMoves(10, 0);
vector<int> aiMoves(10, 0);
cout << "Welcome to Tic-Tac-Toe with Magic Square Logic!" <<endl;
printGrid(grid);
while (true) {
int playerMove;
cout << "Enter your move (1-9): ";
cin >> playerMove;
if (playerMove < 1 || playerMove > 9 || grid[playerMove] != 0) {
cout << "Invalid move! Try again." << endl;
continue;
}

placeMove(playerMove, 1, grid, playerMoves);
printGrid(grid);
if (checkWin(playerMoves)) {
cout << "Congratulations! You win!" << endl;
break;
}
if (isDraw(grid)) {
cout << "It's a draw!" << endl;
break;
}
computerTurn(grid, aiMoves, playerMoves);
printGrid(grid);
if (checkWin(aiMoves)) {
cout << "AI wins! Better luck next time." << endl;
break;
}
if (isDraw(grid)) {
cout << "It's a draw!" << endl;
break;
}
}
return 0;
}