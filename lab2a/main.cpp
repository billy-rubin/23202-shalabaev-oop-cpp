#include "iostream"
#include "Game.h"

void printError(const std::string& arg) {
    std::cerr << "Invalid argument: " << arg << std::endl;
    std::cerr << "Usage: <input file> --iterations=<n> --output=<output file>" << std::endl;
    std::cerr << "or <input file> -i <n> -o <output file>" << std::endl;
}

bool parseCommandLine(int argc, char* argv[], std::string& inputFile, std::string& outputFile, int& iterations) {
    for (int i = 2; i < argc; ++i) {

        std::string arg = argv[i];
        std::cout << arg << "\n";
        if ((arg == "-i" || arg.find("--iterations=") == 0)) {
            if (arg == "-i" && i + 1 < argc) {
                iterations = std::stoi(argv[++i]);
            } else {
                size_t pos = arg.find('=');

                iterations = std::stoi(arg.substr(pos + 1));
            }
        }
        else if ((arg == "-o" || arg.find("--output=") == 0)) {
            if (arg == "-o" && i + 1 < argc) {
                outputFile = argv[++i];
            } else {
                size_t pos = arg.find('=');
                outputFile = arg.substr(pos + 1);
            }
        } else {
            printError(arg);
            return false;
        }
    }

    return true;
}

int main(int argc, char* argv[]){
    std::string inputName = "DefaultUniverse.txt";
    if (argc == 2) {
        inputName = argv[1];
    }
    else if (argc == 4 || argc == 6) {

        inputName = argv[1];
        std::string outputName;
        int iterations = 0;
        const bool success = parseCommandLine(argc, argv, inputName, outputName, iterations);
        if (!success) {
            return 1;
        }
        if (iterations < 0 || inputName.empty() || outputName.empty()) {
            printError("Negative iterations number or file name is empty.");
            return 1;
        }
        Game game(inputName);
        game.runOffline(outputName, iterations);
        return 0;
    }
    Game game(inputName);
    game.run();
    return 0;
}