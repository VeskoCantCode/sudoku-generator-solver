#include <iostream>
#include <vector>
#include <random>

constexpr int SIZE = 9;

bool unUsedInBox(const std::vector<std::vector<int>>& matrix, int startRow, int startCol, int num) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }
    return true;
}

bool unUsedInRow(const std::vector<std::vector<int>>&  matrix, int row, int num){
    for (int j =0; j < 9; j++) {
        if (matrix[row][j] == num) {
            return false;
        }
    }
    return true;
}

bool unUsedInColumn(const std::vector<std::vector<int>>& matrix, int col, int num) {
    for (int i = 0; i < 9; i++) {
        if (matrix[i][col] == num) {
            return false;
        }
    }
    return true;
}

bool checkValid(const std::vector<std::vector<int>>& board, int row, int col, int num) {
    return unUsedInBox(board,row - row % 3, col- col % 3, num) && unUsedInRow(board, row, num) && unUsedInColumn(board, col, num);
}

bool fillBoardWithBacktracking(std::vector<std::vector<int>>& board, const int row, const int col) {
    if (row == 9) {
        return true;
    }

    int nextRow = (col == SIZE - 1) ? row + 1 : row;
    int nextCol = (col + 1) % SIZE;


    //ALWAYS GET RANDOMLY SHUFFLED NUMBERS
    //USED SO THAT WE ALWAYS GET DIFFERENT BOARDS
    std::vector<int> numbers = {1,2,3,4,5,6,7,8,9};
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(numbers.begin(), numbers.end(), g);

    for (int num :numbers) {
        if (checkValid(board, row, col, num)) {
            board[row][col] = num;
            if (fillBoardWithBacktracking(board, nextRow, nextCol)) {
                return true;
            }
             board[row][col] = 0;
        }
    }
    return false;
}

//NULLIFIES RANDOM NUMBERS
void nullifyDigitsOnBoard(std::vector<std::vector<int>>& board, int k) {
    while (k > 0) {
        int cell = rand() % 81;
        int row = cell / 9;
        int col = cell % 9;

        if (board[row][col] != 0) {
            board[row][col] = 0;
            k--;
        }
    }
}

//SOLVES THE SUDOKU BOARD
bool solveUsingBacktracking(std::vector<std::vector<int>>& board, const int row, const int col) {
    unsigned long n = board.size();
    if (row == n)
        return true;

    if (col == n) {
        return solveUsingBacktracking(board, row + 1, 0);
    }

    if (board[row][col] != 0) {
        return solveUsingBacktracking(board, row, col + 1);
    }
    for (int num = 1; num <= n; num++) {
        if (checkValid(board, row, col, num)) {
            board[row][col] = num;
            if (solveUsingBacktracking(board, row, col + 1))
                return true;
            else board[row][col] = 0;
        }
    }
    return false;
}

class Board {
    std::vector<std::vector<int>> board;
public:
    Board();
    ~Board() = default;

    void printBoard() const;
    void generate();
    void solve();
};

Board::Board() = default;

void Board::generate() {
    for (int i = 0; i < SIZE; i++) {
        board.emplace_back();
        for (int j = 0; j < SIZE; j++) {
            board.at(i).push_back(0);
        }
    }
    int startingRow = 0;
    int startingCol = 0;
    int k = 40; //SELECTS HOW MANY NUMBERS WILL BE REMOVED(ADJUST DIFFICULTY)
    fillBoardWithBacktracking(board, startingRow, startingCol);
    nullifyDigitsOnBoard(board, k);
}

void Board::solve() {
    solveUsingBacktracking(board, 0, 0);
}

void Board::printBoard() const{
    for (int i = 0; i < board.size(); i++) {
        if (i % 3 == 0) {
            std::cout << "+-------+-------+-------+\n";
        }
        for (int j = 0; j < board[i].size(); j++) {
            if (j % 3 == 0) {std::cout << "| ";}

            std::cout << board[i][j] << " ";
        }
        std::cout << "|\n";
    }
    std::cout << "+-------+-------+-------+\n";
}

[[noreturn]] int main() {
    const auto board = std::make_unique<Board>();
    int n;

    std::cout << "WELCOME TO MY SUDOKU GENERATOR/SOLVER!\n";

    std::cout << std::endl;
    board->generate();
    board->printBoard();

    std::cout << "Enter '1' to proceed with the answer.\n";
    do {
        std::cin >> n;
    }while (n != 1);

    if (n == 1) {
        board->solve();
        board->printBoard();
    }
}