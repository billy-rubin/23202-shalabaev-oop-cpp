#ifndef TASK_3_CMDPARSER_H
#define TASK_3_CMDPARSER_H

#include "iostream"
#include "vector"
#include "string"

class CmdParser {
public:
    CmdParser(int argc, char** argv);
    ~CmdParser();

    bool parseArguments();
    void printHelp();

    bool showHelp();
    const std::string& getConfigFile() const;
    const std::string& getOutputFile() const;
    const std::vector<std::string>& getInputFiles() const;

private:
    int argc;
    char** argv;
    bool isHelpNeeded;
    std::string configFile;
    std::string outputFile;
    std::vector<std::string> inputFiles;
    void clear();
};
#endif //TASK_3_CMDPARSER_H
