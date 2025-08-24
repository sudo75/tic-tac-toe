#include <iostream>

using std::cin;
using std::cout;

void drawBoard(char *spaces);
void playerMove(char *spaces, char player);
void computerMove(char *spaces, char computer);

bool checkWin(char *spaces, char player, char computer);
bool checkTie(char *spaces);

bool run_game_player(char *spaces, char player, char computer);
bool run_game_computer(char *spaces, char player, char computer);


int main() {

    cout << "******** Tic-Tac-Toe ********" << '\n';

    char spaces[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

    // Define player/computer characters
    char player;
    char computer;

    do {
        cout << "Play as (x/o):";
        cin >> player;

        // Since player is a char, if a user inputs a string of chars
        // The first char will be read; the following chars stay in the buffer
        // To avoid the next iteration of cin reading the buffered char, it shall be reset

        cin.ignore(1024, '\n');

    } while (player != 'x' && player != 'o');

    if (player == 'x') {
        computer = 'o';
    } else if (player == 'o' ){
        computer = 'x';
    }

    // Start game
    bool running = true;
    drawBoard(spaces);

    while (running) {
        if (player == 'x') {
            running = run_game_player(spaces, player, computer);
            if (!running) break;
            running = run_game_computer(spaces, player, computer);
        } else {
            running = run_game_computer(spaces, player, computer);
            if (!running) break;
            running = run_game_player(spaces, player, computer);
        }
        
    }

    
    return 0;
}

bool run_game_player(char *spaces, char player, char computer) {
    playerMove(spaces, player);
    drawBoard(spaces);
    if (checkWin(spaces, player, computer)) {
        
        std::cout << "You win!" << '\n';

        return false;
    }
    if (checkTie(spaces)) {

        std::cout << "Tie!" << '\n';
        return false;
    }

    return true;
}

bool run_game_computer(char *spaces, char player, char computer) {
    computerMove(spaces, computer);
    drawBoard(spaces);
    if (checkWin(spaces, player, computer)) {
        
        std::cout << "You lose!" << '\n';

        return false;
    }
    if (checkTie(spaces)) {

        std::cout << "Tie!" << '\n';
        return false;
    }

    return true;
}

void drawBoard(char *spaces) {
    cout << '\n';

    cout << "   |   |   " << '\n';
    cout << " " << spaces[0] << " | " << spaces[1] << " | " << spaces[2] << '\n';
    cout << "___|___|___" << '\n';
    cout << "   |   |   " << '\n';
    cout << " " << spaces[3] << " | " << spaces[4] << " | " << spaces[5] << '\n';
    cout << "___|___|___" << '\n';
    cout << "   |   |   " << '\n';
    cout << " " << spaces[6] << " | " << spaces[7] << " | " << spaces[8] << '\n';
    cout << "   |   |   " << '\n';

    cout << '\n';
}

void playerMove(char *spaces, char player) {
    int space = -1;
    do {
        cout << "Input a space to fill (1-9): ";
        cin >> space; 

        // cin will log all chars ex. {'a' 'b' '/n'}
        // cin reads the chars but leaves '\n' in the buffer; if the input fails, the '\n' must be cleared too
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n'); // discard 1000 chars or up to last enter key

            space = -1;
            continue;
        }

        space--;

        if (spaces[space] == ' ') {
            spaces[space] = player;
            break;
        } else {
            space = -1;
        }
    } while (space < 0 || space > 8);
}

void computerMove(char *spaces, char computer) {
    srand(time(0));

    int space;

    while(true) {
        space = rand() % 9;

        if (spaces[space] == ' ') {
            spaces[space] = computer;
            break;
        }
    }
}

bool checkWin(char *spaces, char player, char computer) {
    bool win = false;
    for (int row = 0; row < 3; row++) {
        // check rows
        char col0 = spaces[row * 3];
        char col1 = spaces[row * 3 + 1];
        char col2 = spaces[row * 3 + 2];
        if (col0 == col1 && col0 == col2 && (col0 == player || col0 == computer)) {
            return true;
        }
    }

    for (int col = 0; col < 3; col++) {
        // check rows
        char row0 = spaces[col];
        char row1 = spaces[3 + col];
        char row2 = spaces[6 + col];
        if (row0 == row1 && row0 == row2 && (row0 == player || row0 == computer)) {
            return true;
        }
    }

    return false;

}

bool checkTie(char *spaces) {
    int filled = 0;

    for (int i = 0; i < 9; i++) {
        if (spaces[i] == ' ') {
            filled++;
        }
    }

    if (filled == 9) return true;

    return false;

}