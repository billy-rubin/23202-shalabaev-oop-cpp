#include "iostream"
#include "Game.h"
#include "Parser.h"

int main(int argc, char* argv[]){
    std::string inputName = "DefaultUniverse.txt";
    if (argc > 1) {
        inputName = argv[1];
        std::string outputName;
        int iterations = 0;
        Parser parser;
        const bool success = parser.parseCommandLine(argc, argv, inputName, outputName, iterations);
        if (!success) {
            return 1;
        }
        if (iterations < 0 || inputName.empty() || outputName.empty()) {
            parser.printError("Negative iterations number or file name is empty.");
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