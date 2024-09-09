#include <iostream>
using namespace std;

const int rows = 6;
const int cols = 7;
char board[rows][cols];

void initializeBoard() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            board[i][j] = '.';
        }
    }
}

void printBoard() {
    cout << " 1  2  3  4  5  6  7\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << " " << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool placeMarker(int col, char marker) {
    if (col < 0 || col >= cols || board[0][col] != '.') {
        return false;
    }
    for (int i = rows - 1; i >= 0; i--) {
        if (board[i][col] == '.') {
            board[i][col] = marker;
            return true;
        }
    }
    return false;
}

bool checkWin(int row, int col, char marker) {
    // Check horizontal
    int count = 0;
    for (int j = 0; j < cols; j++) {
        count = (board[row][j] == marker) ? count + 1 : 0;
        if (count == 4) return true;
    }

    // Check vertical
    count = 0;
    for (int i = 0; i < rows; i++) {
        count = (board[i][col] == marker) ? count + 1 : 0;
        if (count == 4) return true;
    }

    // Check diagonal (top-left to bottom-right)
    count = 0;
    for (int i = -3; i <= 3; i++) {
        int r = row + i;
        int c = col + i;
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            count = (board[r][c] == marker) ? count + 1 : 0;
            if (count == 4) return true;
        }
    }

    // Check diagonal (top-right to bottom-left)
    count = 0;
    for (int i = -3; i <= 3; i++) {
        int r = row + i;
        int c = col - i;
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            count = (board[r][c] == marker) ? count + 1 : 0;
            if (count == 4) return true;
        }
    }

    return false;
}

int main() {
    initializeBoard();
    char playerMarker[2] = {'X', 'O'};
    int currentPlayer = 0;

    cout << "Welcome to Connect Four!\n";
    printBoard();

    for (int turn = 0; turn < rows * cols; turn++) {
        int col;
        cout << "Player " << currentPlayer + 1 << " (" << playerMarker[currentPlayer] << "), enter a column (1-7): ";
        cin >> col;
        col--;  // Adjust for 0-indexed array

        if (col < 0 || col >= cols || !placeMarker(col, playerMarker[currentPlayer])) {
            cout << "Invalid move! Try again.\n";
            turn--;
            continue;
        }

        // Find the row where the marker was placed
        int row = 0;
        for (int i = 0; i < rows; i++) {
            if (board[i][col] == playerMarker[currentPlayer]) {
                row = i;
                break;
            }
        }

        printBoard();

        if (checkWin(row, col, playerMarker[currentPlayer])) {
            cout << "Player " << currentPlayer + 1 << " (" << playerMarker[currentPlayer] << ") wins!\n";
            break;
        }

        currentPlayer = 1 - currentPlayer;  // Swap between 0 and 1
    }

    if (rows * cols == 42) {
        cout << "It's a draw!\n";
    }

    return 0;
}

