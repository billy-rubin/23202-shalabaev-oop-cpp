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
    static void readName(const std::string& line, std::string& name, bool& hasName);
    static void readRules(const std::string& line, Rules& rule, bool& hasRule);
    static void readDimensions(const std::string& line, int& width, int& height, bool& hasDimensions);
    static void readCoords(const std::string& line, const int& width, const int& height, std::vector<std::pair<int, int>>& liveCells, const bool& hasDimensions, bool& hasCoords);
public:
    static void saveUniverse(Universe& universe, const std::string& filename);
    static Universe loadUniverse(const std::string& filename);
};

#endif //TASK_2_FILEMANAGER_H
