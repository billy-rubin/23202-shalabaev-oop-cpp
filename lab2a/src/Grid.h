#ifndef TASK_2_GRID_H
#define TASK_2_GRID_H

#include "iostream"
#include "vector"

using namespace std;

class Grid{
private:
    vector<vector<bool>> grid;
    int rows;
    int cols;
public:
    explicit Grid(int rows, int cols);
    Grid();
    void setCell(int row, int col, bool value);
    bool getCell(int row, int col) const;
    int getNeighborsNum(int x, int y);
    int getRows() const;
    int getCols() const;
};
#endif //TASK_2_GRID_H
