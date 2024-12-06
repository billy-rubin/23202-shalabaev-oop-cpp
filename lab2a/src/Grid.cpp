#include "Grid.h"

Grid::Grid() {
    rows = 0;
    cols = 0;
    grid = vector<vector<bool>>(rows, vector<bool>(cols, false));
}

Grid::Grid(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    grid = vector<vector<bool>>(rows, vector<bool>(cols, false));
}

void Grid::setCell(int row, int col, bool value) {
    if(row >= 0 && row < rows && col >= 0 && col < cols) {
        grid[row][col] = value;
    }
}

bool Grid::getCell(int row, int col) const {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        return grid[row][col];
    }
    return false;
}

int Grid::getNeighborsNum(int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue;
            }
            const int rowNum = (row + i + rows) % rows;
            const int colNum = (col + j + cols) % cols;
            count += getCell(rowNum, colNum);
        }
    }
    return count;
}

int Grid::getCols() const {
    return cols;
}

int Grid::getRows() const {
    return rows;
}