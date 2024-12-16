#include "CmdParser.h"

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

    int i = 1;
    while (i < argc) {
        std::string arg = argv[i];
        if (arg == "-h") {
            isHelpNeeded = true;
            i++;
        } else if (arg == "-c") {
            i++;
            if (i >= argc) {
                std::cerr << "-c requires config file." << std::endl;
                return false;
            }
            configFile = argv[i++];
            if (i >= argc) {
                std::cerr << "-c requires output file." << std::endl;
                return false;
            }
            outputFile = argv[i++];
            if (i >= argc) {
                std::cerr << "-c requires at least 1 input file." << std::endl;
                return false;
            }
            for (; i < argc; i++) {
                inputFiles.push_back(argv[i]);
            }
            break; // Все оставшиеся аргументы это входные файлы
        } else {
            std::cerr << "Unknown argument: " << arg << std::endl;
            return false;
        }
    }

    if (!isHelpNeeded && configFile.empty()) {
        std::cerr << "Config file isn't specified." << std::endl;
        return false;
    }

    return true;
}

void CmdParser::printHelp() {
    std::cout << "Usage:\n"
              << "sound_processor [-h] [-c config.txt output.wav input1.wav [input2.wav …]]\n\n"
              << "Parameters:\n"
              << "-h : show this help\n"
              << "-c config.txt output.wav input1.wav [input2.wav ...] : run processing\n\n"
              << "Supported converters:\n"
              << "mix $<n> <insert_sec>\n"
              << "Mixes the main audio with the additional input $n starting at insert_sec.\n"
              << "mute <start_sec> <end_sec>\n"
              << "Sets the audio samples between start_sec and end_sec to zero.\n"
              << "echo <delay_sec> <attenuation>\n"
              << "Adds an echo effect with given delay and attenuation.\n";
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