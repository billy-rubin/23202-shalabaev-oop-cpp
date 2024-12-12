#include "Universe.h"

Universe:: Universe() {
    field = Grid();
    generation = 0;
    name = "DefaultUniverse";
    rules = Rules();
}
Universe:: Universe(const int& rows, const int& cols, const string& name, const Rules& rule){
    field = Grid(rows, cols);
    this->name = name;
    this->rules = rule;
    generation = 1;
}

Grid Universe::computeNextGeneration(Grid &current_generation) {
    for (int row = 0; row < current_generation.getRows(); ++row) {
        for (int col = 0; col < current_generation.getCols(); ++col) {
            int neighbors_num = current_generation.getNeighborsNum( row, col);
            bool cell_state = current_generation.getCell(row, col);
            bool next_state = cell_state;
            if (cell_state) {
                if (!rules.shouldBeSurvived(neighbors_num)) {
                    next_state = false;
                }
            } else {
                if (rules.shouldBeBorn(neighbors_num)) {
                    next_state = true;
                }
            }
            field.setCell(row, col, next_state);
        }
    }
    generation++;
    return field;
}

string Universe::getName() const {
    return name;
}
Grid& Universe::getField() {
    return field;
}

vector<pair<int, int>> Universe::getAliveCells() const {
    vector<std::pair<int, int>> liveCells;
    for(int row = 0; row < field.getRows(); ++row){
        for(int col = 0; col < field.getCols(); ++col){
            if (field.getCell(row, col)){
                liveCells.emplace_back(col, row);
            }
        }
    }
    return liveCells;
}

Rules Universe::getRules() const {
    return rules;
}

void Universe::display(Grid& currentField) const {
    cout << "Universe name: " << name << ", Generation number: " << generation << endl;
    for(int row = 0; row < currentField.getRows(); ++row){
        for(int col = 0; col < currentField.getCols(); ++col){
            std::cout << (currentField.getCell(row, col) ? '#' : '.');
        }
        cout << endl;
    }
}