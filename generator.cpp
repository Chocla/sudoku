#include <iostream>
#include <ctime> 
#include <cstdlib>
//implement for 9x9, then 16x16

const int N = 9;
const int NR = 3; //Square root of N
//for debugging
void printBoard(int board[N][N]) {
    std::cout << std::endl;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
//checks if candidate value is unique to col,row, and box
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
bool solveBoard(int board[N][N], int excludeCell = N*N, int exlcludeVal = -1) {
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
    // std::cout << "Flags Made" << std::endl;
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
            int candidate = std::rand() % N + 1;
            if(isValid(candidate, currentCell,board) && 
                !(currentCell == excludeCell && candidate == exlcludeVal)) {
                board[row][col] = candidate;
                backtrack = false;
                break;
            }
        } 
        //zero out cell
        //decrement currentCell until flags[currentCell] is false
        // std::cout << "Current Cell:" << currentCell << std::endl;
        if(backtrack) {
            board[row][col] = 0;
            currentCell--;
            while(flags[currentCell]) {
                currentCell--;
            }
            if(currentCell < 0) {
                return false;
            }
            continue;
        }
        currentCell++;
    }
    // std::cout << "Board Solved" << std::endl;
    //board solved
    return true;
}

//TODO: fix non unique solutions problem
void removeCells(int board[N][N],int numCells) {
    int count = 0;
    while(count < numCells) {
        if(count % 5 == 0) {
            std::cout << "Removed " << count << " Cells" << std::endl;
        }
        //pick a random cell to remove
        int candidateCell = std::rand() % (N*N);
        int row = candidateCell / N;
        int col = candidateCell % N;
        int tmp = board[row][col];
        // std::cout << "Cell: " << candidateCell << std::endl;
        if(tmp == 0) {
            continue;
        }
        board[row][col] = 0;
        //if board can be solved using a value other than the removed one, solution is no longer unique
        if( !solveBoard(board, candidateCell,tmp)) {
            count++;
        } else {
            board[row][col] = tmp;
        }
    }
}
void formatBoard() {
    //TODO: Somehow put the board into a .tex file
}

int countZeros(int board[N][N]) {
    int count = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N;j++) {
            if(board[i][j] == 0 ){
                count++;
            }
        }
    }
    return count;
}

int main() {
    std::srand(unsigned(std::time(0)));
    int blank[N][N];
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            blank[i][j] = 0;
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

    solveBoard(blank);
    printBoard(blank);
    removeCells(blank,60);
    printBoard(blank);
    int count = countZeros(blank);
    std::cout << "Actual Zeros: " << count << std::endl; 
    // std::cout << solveBoard(board, 2,4);
    // printBoard(board);
}
