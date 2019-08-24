#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime> 
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>

//implement for 9x9, then 16x16
const int N = 9;
const int NR = 3; //Square root of N
//for debugging
void printBoard(std::vector<std::vector<int>> board) {
    std::cout << std::endl;
    for(std::vector<int> row : board) {
        for(int i: row) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
//checks if candidate value is unique to col,row, and box
bool isValid(int candidate,int cell, std::vector<std::vector<int>> board) {
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

bool isUnique(int board[N][N]) {

}
//TODO: Rewrite to use a pointer to the board, so that we don't have to pass it back and forth, 
//and can instead pass a bool indicating that it was solved
void solveBoard(std::vector<std::vector<int>> &board) {
    printBoard(board);
    std::vector<bool> flags(N*N);

    std::vector<int> cellVals; //for shuffling
    for (int i = 1; i <= N; i++) cellVals.push_back(i);
    std::random_shuffle(cellVals.begin(),cellVals.end());
    // std::cout << cellVals[0] << cellVals[4];
    for(int i = 0; i < N*N; i++) {
        if(board[i / N][i % N] != 0) {
            flags[i] = true;
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

        int index;
        if(board[row][col] == 0 ){
            index = -1;
        } else {
            auto q = std::find(cellVals.begin(),cellVals.end(),board[row][col]) ;
            index = q - cellVals.begin();
        }
        for(int i = index + 1; i < N; i++) {
            int candidate = cellVals[i];
            if(isValid(candidate,currentCell,board)) {
                board[row][col] = candidate;
                backtrack = false;
                break;
            }
        }

        if(backtrack) {
            board[row][col] = 0;
            currentCell--;
            while(flags[currentCell]) {
                currentCell--;
            }
            if (currentCell < 0) {
                //return board; //failure, TODO: figure out how to indicate this
            }
            continue;
        }
        currentCell++;
    }
    // printBoard(board);
}
std::vector<std::vector<int>> fillBoard() {
    std::vector<std::vector<int>> blank(N,std::vector<int>(N));
    //seed board with numbers 1-9 twice in random positions
    for(int i = 0; i < 18; i++) {
        int val = (i % N) + 1;
        int cell = std::rand() %(N*N);
        while(!isValid(val,cell,blank)) {
            cell = std::rand() % (N*N);
        }
        
        blank[cell / N][cell % N] = val;
    }
    solveBoard(blank);
    printBoard(blank);
}
//TODO: fix non unique solutions problem
// void removeCells(int board[N][N],int numCells) {
//     int puzzleBoard[N][N];
//     std::copy(&board[0][0],&board[0][0]+(N*N), &puzzleBoard[0][0]);
//     std::vector<int> changedCells(numCells);
//     std::vector<int> changedVals(numCells);

//     int count = 0;
//     while(count < numCells) {
//         if(count % 5 == 0) {
//             std::cout << "Removed " << count << " Cells" << std::endl;
//         }
//         int candidatecell = std::rand() % (N*N);
//         int row = candidatecell / N;
//         int col = candidatecell % N;
//         int tmp = board[row][col];
//         if(tmp == 0) {
//             continue; //repeated cell
//         }
//         board[row][col] = 0;
//         if (!solveBoard(board,candidatecell,tmp)) {
//             count++;
//             changedCells[count] = candidatecell;
//             changedVals[count] = tmp;
//         } else {
//             board[row][col] = tmp;
//         }
//         for(int i : changedCells) {
//                 board[i / N][i % N] = 0;
//         }
//     }
// }

// "\setrow{ROWNUM}{ {1}, {2},.....{9}}"
std::vector<std::string> formatBoard(std::vector<std::vector<int>> board) {
    std::vector<std::string> rowStrings(N);

    for(int i = 0; i < N; i++) {
        std::string line = "\\setrow";
        line += "{" + std::to_string(N - i) + "}{";
        for(int j = 0; j < N; j++) {
            if(board[i][j] == 0) {
                line += "{},";
            } else {
                line += "{" + std::to_string(board[i][j]) + "},";
            }
        }
        line.pop_back();
        line += "}";
        rowStrings[i] = line;
    }

    return rowStrings;
}
void createTexFile() {
    std::ifstream infile("6_sudoku_template.tex");
    std::string line;
    std::ofstream outfile("new.tex");
    while(std::getline(infile,line)) {
        outfile << line << std::endl;
        if (line.compare("    \\begin{lpsudoku}") == 0) {
            //GENERATE PUZZLE
            std::vector<std::vector<int>> board = {
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
            
            //FORMAT THE STRING
            std::vector<std::string> rows = formatBoard(board);
            for(std::string i : rows) {
                outfile << i << std::endl;
            }
            //INSERT
            // std::cout << line << std::endl;
        }
    }
    return;
}

int main() {
    std::srand(unsigned(std::time(0)));
    std::vector<std::vector<int>> blank(N,std::vector<int>(N));
    std::vector<std::vector<int>> board = {
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
    std::vector<std::vector<int>> solved = {
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
    // solveBoard(board);
    fillBoard();
    // std::vector<std::string> rows = formatBoard(board);

    // printBoard(board);
    // printBoard(solved);

    // solveBoard(blank);
    // printBoard(blank);
    // removeCells(blank,40);
    // printBoard(blank);

    // createTexFile();
}
