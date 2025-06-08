#include "CmdParser.h"
#include "string"
#include "regex"
CmdParser::CmdParser(int argc, char** argv)
        : argc(argc), argv(argv), isHelpNeeded(false) {
}

CmdParser::~CmdParser() {
    clear();
}

void CmdParser::clear() {
    isHelpNeeded = false;
    configFile.clear();
    outputFile.clear();
    inputFiles.clear();
}
bool CmdParser::parseArguments() {
    if (argc < 2) {
        std::cerr << "Not enough arguments. Type -h for help." << std::endl;
        return false;
    }
    std::regex wav (R"((.*\.wav)$)", std::regex::icase);
    std::regex txt (R"((.*\.txt)$)", std::regex::icase);
    std::string arg = argv[1];
    if (arg == "-h"){
        printHelp();
        isHelpNeeded = true;
        return true;
    } else if (arg == "-c"){
        for (int i = 2; i < argc; i++){
            std::string fileName = argv[i];
            if (std::regex_match(fileName, txt) && configFile.empty()) {
                configFile = fileName;
            } else if (std::regex_match(fileName, wav) && outputFile.empty()){
                outputFile = fileName;
            } else if (std::regex_match(fileName, wav))
                inputFiles.push_back(fileName);
        }
    } else {
        std::cerr << "Invalid format of commandline. Type -h for help." << std::endl;
    }
    return true;
}

void CmdParser::printHelp() {
    std::cout << "Usage:\n"
              << "sound_processor [-h] [-c config.txt output.wav input1.wav [input2.wav ...]]\n\n"
              << "Parameters:\n"
              << "-h : show this help\n"
              << "-c config.txt output.wav input1.wav [input2.wav ...] : run processing\n\n";
}

bool CmdParser::showHelp() {
    return isHelpNeeded;
}

const std::string& CmdParser::getConfigFile() const {
    return configFile;
}

const std::string& CmdParser::getOutputFile() const {
    return outputFile;
}

const std::vector<std::string>& CmdParser::getInputFiles() const {
    return inputFiles;
}