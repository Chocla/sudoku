#include <iostream>

//implement for 9x9, then 16x16

const int N = 9;
const int NR = 3; //Square root of N
//for debugging
void printBoard(int board[N][N]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
bool isValid(int candidate,int cell, int board[N][N]) {
    int row = cell / N;
    int col = cell % N;
    for(int i = 0; i < N; i++) {
        if(candidate == board[row][i] && i != col) {
            return false;
        }
        if(candidate == board[i][col] && i != row) {
            return false;
        }
    }
    int sqRow = row / NR;
    int sqCol = col / NR;
    for(int i = NR*sqRow; i < NR*(sqRow + 1); i++) {
        for(int j = NR*sqCol; j < NR*(sqCol + 1); j++) {
            if(candidate == board[i][j] && (i != row || j != col)) {
                return false;
            }
        }
    }
    return true;
}
void solveBoard(int board[N][N]) {
    bool flags[N*N]; //keep track of initial board values
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(board[i][j] != 0) {
                flags[N*i + j] = true;
            } else {
                flags[N*i + j] = false;
            }
        }
    }
    int currentCell = 0;
    while(currentCell < N*N) {
        if(flags[currentCell]) {
            currentCell++;
            continue;
        }
        int row = currentCell / N;
        int col = currentCell % N;
        bool backtrack = true;
        //check each number 1-9,starting at current value+1
        for(int i = board[row][col] + 1;i <= N ; i++) { //[1,N]
            //if we find one that is valid, continue to the next cell
            if(isValid(i, currentCell,board)) {
                board[row][col] = i;
                backtrack = false;
                break;
            }
        } 
        //zero out cell
        //decrement currentCell until flags[currentCell] is false
        if(backtrack) {
            board[row][col] = 0;
            currentCell--;
            while(flags[currentCell]) {
                currentCell--;
            }
            continue;
        }
        currentCell++;
    }
    //board solved
    return;
}

void formatBoard() {

}

int main() {
    int board[N][N] = {
        {5,3,0, 0,7,0, 0,0,0},
        {6,0,0, 1,9,5, 0,0,0},
        {0,9,8, 0,0,0, 0,6,0},
        
        {8,0,0, 0,6,0, 0,0,3},
        {4,0,0, 8,0,3, 0,0,1},
        {7,0,0, 0,2,0, 0,0,6},

        {0,6,0, 0,0,0, 2,8,0},
        {0,0,0, 4,1,9, 0,0,5},
        {0,0,0, 0,8,0, 0,7,9}
    };
    int solved[N][N] = {
        {5,3,4, 6,7,8, 9,1,2},
        {6,7,2, 1,9,5, 3,4,8},
        {1,9,8, 3,4,2, 5,6,7},
        
        {8,5,9, 7,6,1, 4,2,3},
        {4,2,6, 8,5,3, 7,9,1},
        {7,1,3, 9,2,4, 8,5,6},

        {9,6,1, 5,3,7, 2,8,4},
        {2,8,7, 4,1,9, 6,3,5},
        {3,4,5, 2,8,6, 1,7,9}
    };
    solveBoard(board);
    printBoard(board);
    printBoard(solved);
}
