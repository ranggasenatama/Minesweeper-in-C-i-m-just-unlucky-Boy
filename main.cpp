#include <iostream>
#include <stdlib.h>

using namespace std;

int nBoard, flag = 1;
bool clicked[100][100] = {0};
int board[100][100];

bool isNotUnderZeroIndex(int row, int column, int rowIndex, int columnIndex, int eightSide[]) {
    return ((row+eightSide[rowIndex] >= 0 || column+eightSide[columnIndex] >= 0) &&
            (rowIndex != row && columnIndex != column));
}

void generateNumberBesideBomb(int row, int column) {
    int eightSide[3] = {-1, 0, 1};
    int rowIndex = 0, columnIndex=0;
    
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            bool isNotBomb = board[row+eightSide[rowIndex]][column+eightSide[columnIndex]] >= 0 ? 1 : 0;
            
            if(isNotBomb &&
                isNotUnderZeroIndex(row, column, rowIndex, columnIndex, eightSide)) {
                    board[row+eightSide[rowIndex]][column+eightSide[columnIndex]] += 1;
            }
            
            rowIndex++;
        }
        rowIndex = 0;
        columnIndex++;
    }
}

int randomNumber() {
    int resultRandom = rand() % nBoard;
    return resultRandom;
}

void setMine(int nBomb) {
    srand(time(NULL));
    while (nBomb>0) {
        int row = randomNumber();
        int column = randomNumber();
        if(board[row][column] != -1) {
            board[row][column] = -1;
            generateNumberBesideBomb(row,column);
            nBomb--;
        }
    }
    return ;
}

void greetingCard() {
    cout << "Pilih Board format: row column" << endl << "Ex(mulai dari 0): 1 2" << endl;
}

void printBomb() {
    cout << "$";
}

void printUnexploredBoard() {
    cout << "*";
}

void currentBoard(int row, int column) {
    cout << board[row][column];
}

void displayBoard(int checkAll = 0) {
    for (int i=0; i<nBoard; i++) {
        for (int j=0; j<nBoard; j++) {
            bool isBomb = board[i][j] == -1 ? 1 : 0;
            
            if (checkAll == 1) {
                if(isBomb) { printBomb();}
                else { currentBoard(i, j); }
            } else if(checkAll) {
                if (isBomb) { printBomb(); }
                else if(!clicked[i][j]) { printUnexploredBoard(); }
                else if(clicked[i][j]) {
                    if(isBomb) { printBomb(); }
                    else { currentBoard(i, j); }
                }
            } else {
                if(!clicked[i][j]) { printUnexploredBoard(); }
                else if(clicked[i][j]) {
                    if(isBomb) { printBomb(); }
                    else { currentBoard(i, j); }
                }
            }
        }
        cout << endl;
    }
    cout << endl;
}

void checkAroundSelected(int x, int y) {
    if (clicked[x][y] == 1) { return; }
    clicked[x][y] = 1;
    if(board[x][y] == -1) flag = 0;
    if(board[x][y] > 0 || board[x][y] == -1) { return; }
    
    if (x - 1 >= 0 && board[x-1][y] > -1) {
        checkAroundSelected(x-1, y);
        
        if(y - 1 >= 0 && board[x-1][y-1] > -1) { checkAroundSelected(x-1, y-1); }
        if(y + 1 < nBoard && board[x-1][y+1] > -1) { checkAroundSelected(x-1, y+1); }
    }
    
    if (x + 1 < nBoard && board[x+1][y] > -1) {
        checkAroundSelected(x+1,y);
        
        if(y - 1 >= 0 && board[x+1][y-1] > -1) { checkAroundSelected(x+1, y-1); }
        if(y + 1 < nBoard && board[x+1][y+1] > -1) { checkAroundSelected(x+1, y+1); }
    }
    
    if (y + 1 < nBoard && board[x][y+1] > -1) { checkAroundSelected(x, y+1); }

    if (y - 1 >= 0 && board[x][y-1] > -1) { checkAroundSelected(x, y-1); }
}

bool isDone() {
    for (int i=0; i<nBoard; i++) {
        for (int j=0; j<nBoard; j++) {
            if(clicked[i][j] == 0 && board[i][j] != -1) { return false; }
        }
    }
    return true;
}

int main() {
    int nBomb, row, column;
    cin >> nBoard;
    cin >> nBomb;
    setMine(nBomb);
    displayBoard(1);
    greetingCard();
    while (flag) {
        displayBoard();
        cin >> row;
        cin >> column;
        checkAroundSelected(row,column);
        if(isDone()) {
            break;
        }
        greetingCard();
    }
    if (flag == 0) {
        displayBoard(2);
        cout << "GAME OVER" << endl;
    } else {
        displayBoard();
        cout << "Congratz You Win Dude" << endl;
    }
}
