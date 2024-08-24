#include <iostream>

using namespace std;

char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
char currentMarker;
int currentPlayer;

void drawBoard() {
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = currentMarker;
        return true;
    } else {
        return false;
    }
}

int checkWin() {
    for (int i = 0; i < 3; i++) {
        // Check rows
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return currentPlayer;

        // Check columns
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return currentPlayer;
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return currentPlayer;

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return currentPlayer;

    return 0;
}

void switchPlayer() {
    if (currentMarker == 'X') {
        currentMarker = 'O';
        currentPlayer = 2;
    } else {
        currentMarker = 'X';
        currentPlayer = 1;
    }
}

bool isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false;
            }
        }
    }
    return true;
}

void resetBoard() {
    char initial = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = initial++;
        }
    }
}

void game() {
    cout << "Player 1, choose your marker (X/O): ";
    char markerP1;
    cin >> markerP1;

    currentPlayer = 1;
    currentMarker = markerP1;

    if (markerP1 == 'X') {
        currentMarker = 'X';
    } else {
        currentMarker = 'O';
    }

    drawBoard();
    int winner = 0;

    while (winner == 0 && !isBoardFull()) {
        cout << "It's player " << currentPlayer << "'s turn. Enter your slot: ";
        int slot;
        cin >> slot;

        if (slot < 1 || slot > 9) {
            cout << "Invalid slot! Try again." << endl;
            continue;
        }

        if (!placeMarker(slot)) {
            cout << "Slot already taken! Try again." << endl;
            continue;
        }

        drawBoard();
        winner = checkWin();
        if (winner == 0) {
            switchPlayer();
        }
    }

    if (winner != 0) {
        cout << "Player " << winner << " wins!" << endl;
    } else {
        cout << "It's a draw!" << endl;
    }
}

int main() {
    char playAgain = 'Y';
    while (playAgain == 'Y' || playAgain == 'y') {
        resetBoard();
        game();
        cout << "Do you want to play again? (Y/N): ";
        cin >> playAgain;
    }
    cout << "Thanks for playing!" << endl;
    return 0;
}