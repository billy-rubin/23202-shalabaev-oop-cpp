#ifndef TASK_2_UNIVERSE_H
#define TASK_2_UNIVERSE_H

#include "iostream"
#include "vector"
#include "Rules.h"
#include "Grid.h"
#include "fstream"

using namespace std;

class Universe{
private:
    Grid field;
    string name;
    int generation;
    Rules rules;
public:
    Universe();
    explicit Universe(const int& rows, const int& cols, const string& name, const Rules& rule);
    Grid computeNextGeneration(Grid& current_generation);
    void display(Grid& currentField) const;
    string getName() const;
    Grid& getField();
    void setField(const Grid& newField);
    vector<std::pair<int, int>> getAliveCells() const;
    Rules getRules() const;

    friend class FileManager;
};
#endif //TASK_2_UNIVERSE_H
