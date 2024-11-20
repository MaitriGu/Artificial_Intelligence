#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

const int MAX_SCORE = 10;
const int MIN_SCORE = -10;
const int SIZE = 3;

int evaluate_board(const vector<vector<int>> &board)
{
    int score = 0;

    for (int i = 0; i < SIZE; i++)
    {
        int row_sum = board[i][0] + board[i][1] + board[i][2];
        int col_sum = board[0][i] + board[1][i] + board[2][i];

        if (row_sum == SIZE)
            return MAX_SCORE;
        if (row_sum == -SIZE)
            return MIN_SCORE;
        if (abs(row_sum) == SIZE - 1)
            score += row_sum > 0 ? 5 : -5;

        if (col_sum == SIZE)
            return MAX_SCORE;
        if (col_sum == -SIZE)
            return MIN_SCORE;
        if (abs(col_sum) == SIZE - 1)
            score += col_sum > 0 ? 5 : -5;
    }

    int diag1_sum = board[0][0] + board[1][1] + board[2][2];
    int diag2_sum = board[0][2] + board[1][1] + board[2][0];

    if (diag1_sum == SIZE)
        return MAX_SCORE;
    if (diag1_sum == -SIZE)
        return MIN_SCORE;
    if (abs(diag1_sum) == SIZE - 1)
        score += diag1_sum > 0 ? 5 : -5;

    if (diag2_sum == SIZE)
        return MAX_SCORE;
    if (diag2_sum == -SIZE)
        return MIN_SCORE;
    if (abs(diag2_sum) == SIZE - 1)
        score += diag2_sum > 0 ? 5 : -5;

    if (board[1][1] != 0)
        score += board[1][1] * 3;

    return score;
}

bool is_terminal(const vector<vector<int>> &board)
{
    int score = evaluate_board(board);
    if (score == MAX_SCORE || score == MIN_SCORE)
    {
        return true;
    }

    for (const auto &row : board)
    {
        if (find(row.begin(), row.end(), 0) != row.end())
        {
            return false;
        }
    }
    return true;
}

int minmax(vector<vector<int>> &board, int depth, int color)
{
    if (depth == 0 || is_terminal(board))
        return color * evaluate_board(board);

    int best_score = MIN_SCORE;
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (board[i][j] == 0)
            {
                board[i][j] = color;
                int score = -minmax(board, depth - 1, -color);
                board[i][j] = 0;
                best_score = max(best_score, score);
            }
        }
    }
    return best_score;
}

pair<int, int> get_best_move(vector<vector<int>> &board, int depth, int color)
{
    int best_score = MIN_SCORE;
    int best_row = -1, best_col = -1;

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (board[i][j] == 0)
            {
                board[i][j] = color;

                int score = -minmax(board, depth - 1, -color);
                board[i][j] = 0;
                if (score > best_score)
                {
                    best_score = score;
                    best_row = i;
                    best_col = j;
                }
            }
        }
    }
    return make_pair(best_row, best_col);
}

void display_board(const vector<vector<int>> &board)
{
    for (const auto &row : board)
    {
        for (int cell : row)
            cout << (cell == 1 ? 'X' : cell == -1 ? 'O'
                                                  : '.') << ' ';
        cout << endl;
    }
}

void play_game()
{
    vector<vector<int>> board(SIZE, vector<int>(SIZE, 0));
    int depth;

    cout << "Enter AI search depth (1-9): ";
    cin >> depth;

    depth = max(1, min(depth, 9));
    cout << "Enter 1 to start first or -1 for computer to start first" << endl;
    int player;
    cin >> player;

    bool game_over = false;

    while (!is_terminal(board))
    {
        display_board(board);
        if (player == 1)
        {
            int row, col;
            cout << "Enter your move (row and column): ";
            cin >> row >> col;
            if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != 0)
            {
                cout << "Invalid move! Try again.\n";
                continue;
            }
            board[row][col] = player;
        }
        else
        {
            pair<int, int> best_move = get_best_move(board, depth, player);
            board[best_move.first][best_move.second] = player;
            cout << "AI plays: (" << best_move.first << ", " << best_move.second << ")\n";
        }

        if (evaluate_board(board) == MAX_SCORE)
        {
            display_board(board);
            cout << "Player 'X' wins!\n";
            game_over = true;
            break;
        }
        else if (evaluate_board(board) == MIN_SCORE)
        {
            display_board(board);
            cout << "Player 'O' (AI) wins!\n";
            game_over = true;
            break;
        }

        bool is_tie = true;
        for (const auto &row : board)
        {
            for (int cell : row)
            {
                if (cell == 0)
                {
                    is_tie = false;
                    break;
                }
            }
            if (!is_tie)
                break;
        }

        if (is_tie)
        {
            display_board(board);
            cout << "It's a tie!\n";
            game_over = true;
            break;
        }

        player = -player;
    }
}

int main()
{
    cout << "Welcome to Tic-Tac-Toe!\n";
    play_game();
    return 0;
}