#ifndef TASK_2_PARSER_H
#define TASK_2_PARSER_H
#include "iostream"

using namespace std;
class Parser{
public:
    bool parseCommandLine(int argc, char* argv[], string& inputFile, string& outputFile, int& iterations);
    void printError(const string& arg);
};
#endif //TASK_2_PARSER_H
