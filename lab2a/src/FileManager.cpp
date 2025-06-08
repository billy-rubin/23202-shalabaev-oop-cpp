#include "FileManager.h"
#include <cctype>
void FileManager:: readName(const string& line, string& name, bool& hasName) {
    string namePart = line.substr(3);
    if (!namePart.empty()){
        name = namePart;
    } else {
        name = "Default Universe";
    }
    hasName = true;
}
void FileManager:: readRules(const string& line, Rules& rule, bool& hasRule){
    string rulePart = line.substr(3);
    if (!rulePart.empty()){
        int slash_pos = rulePart.find('/');
        string neighbors_r = rulePart.substr(0, slash_pos);
        string neighbors_s = rulePart.substr(slash_pos + 1);
        rule = Rules(neighbors_r, neighbors_s);
        hasRule = true;
    } else {
        rule = Rules();
    }
}

void FileManager::readDimensions(const string& line, int& width, int& height, bool& hasDimensions) {
    if (line.find("#D") == 0) {
        size_t pos = line.find_first_not_of(" \t", 2);
        if (pos != string::npos) {
            istringstream iss(line.substr(pos));
            if (!(iss >> width >> height)) {
                throw invalid_argument("Invalid Dimension format: " + line);
            }
            hasDimensions = true;
        }
    }
}

void FileManager::readCoords(const string& line, const int& width, const int& height, vector<pair<int, int>>& liveCells, const bool& hasDimensions, bool& hasCoords) {
    istringstream iss(line);
    int x, y;
    if (!(iss >> x >> y)) {
        cerr << "Invalid coordinate line: " << line << "\n";
        return;
    }

    if (hasDimensions) {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            cerr << "Coordinates (" << x << ", " << y << ")  are out of grid range (" << width << "x" << height << ").\n";
            return;
        }
    }

    for (const auto& cell : liveCells) {
        if (cell.first == x && cell.second == y) {
            cerr << "Duplicates of coordinates(" << x << ", " << y << ").\n";
            return;
        }
    }
    const pair<int, int> coords = {x, y};
    liveCells.push_back(coords);
    hasCoords = true;
}

void FileManager::storeUniverse(Universe& universe, const string& filename) {
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        throw runtime_error("The file couldn't be opened for reading: " + filename);
    }

    outfile << "#Life 1.06\n";
    outfile << "#N " << universe.getName() << "\n";
    outfile << universe.getRules().getRuleString() << "\n";
    outfile << "#D " << universe.getField().getRows() << " " << universe.getField().getCols() << "\n";


    vector<pair<int, int>> liveCells = universe.getAliveCells();
    for(const auto& cell : liveCells){
        outfile << cell.first << " " << cell.second << "\n";
    }

    outfile.close();
}

Universe FileManager::loadUniverse(const string& filename) {\

    ifstream infile(filename);
    if (!infile.is_open()) {
        throw runtime_error("The file couldn't be opened for reading: " + filename);
    }

    int width = 40;
    int height = 40;
    bool hasName = false;
    bool hasRule = false;
    bool hasDimensions = false;
    bool hasCoords = false;
    vector<pair<int, int>> liveCells;

    string line;
    string name;
    Rules rule;
    FileManager fileReader;


    if (!getline(infile, line)) {
        throw runtime_error("File is empty.");
    }

    while (getline(infile, line)) {

        if (line.empty()) {
            continue;
        }
        if (line.find("#N") == 0) {
            fileReader.readName(line, name, hasName);
        }
        else if (line.find("#R") == 0) {
            fileReader.readRules(line, rule, hasRule);
        }
        else if (line.find("#D") == 0) {
            fileReader.readDimensions(line, width, height, hasDimensions);
        }
        else {
            fileReader.readCoords(line, width, height, liveCells, hasDimensions, hasCoords);
        }
    }

    infile.close();

    Universe universe(width, height, name, rule);
    for (const auto& cell : liveCells) {
        universe.field.setCell(cell.first, cell.second, true);
    }
    return universe;
}