#ifndef TASK_2_FILEMANAGER_H
#define TASK_2_FILEMANAGER_H

#include "iostream"
#include "Rules.h"
#include <vector>
#include <utility>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Universe.h"

class FileManager{
private:
    void readName(const std::string& line, std::string& name, bool& hasName);
    void readRules(const std::string& line, Rules& rule, bool& hasRule);
    void readDimensions(const std::string& line, int& width, int& height, bool& hasDimensions);
    void readCoords(const std::string& line, const int& width, const int& height, std::vector<std::pair<int, int>>& liveCells, const bool& hasDimensions, bool& hasCoords);
public:
    void storeUniverse(Universe& universe, const std::string& filename);
    Universe loadUniverse(const std::string& filename);
};

#endif //TASK_2_FILEMANAGER_H
