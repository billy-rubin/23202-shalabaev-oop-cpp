#include "Parser.h"

void Parser::printError(const string& arg) {
    cerr << "Invalid argument: " << arg << endl;
    cerr << "Usage: <input file> --iterations=<n> --output=<output file>" << endl;
    cerr << "or <input file> -i <n> -o <output file>" << endl;
}

bool Parser::parseCommandLine(int argc, char* argv[], string& inputFile, string& outputFile, int& iterations) {
    for (int i = 2; i < argc; ++i) {
        string arg = argv[i];
        cout << arg << "\n";
        if ((arg == "-i" || arg.find("--iterations=") == 0)) {
            if (arg == "-i" && i + 1 < argc) {
                iterations = stoi(argv[++i]);
            } else {
                size_t pos = arg.find('=');
                iterations = stoi(arg.substr(pos + 1));
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
