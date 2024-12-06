#include "Game.h"
#include "FileManager.h"
#include <iostream>

Game::Game(const string& filename)
        : universe(), commandHandler(universe) {
    try {
        universe = FileManager::loadUniverse(filename);
    } catch (const exception& ex) {
        cerr << "Error occurred while reading file'" << filename << "': " << ex.what() << "\n";
        exit(1);
    }
}

void Game::run() {
    string input;
    cout << ">> Enter a command to start the game\n";
    Grid currentField = universe.getField();
    universe.display(currentField);
    while (commandHandler.getGameState()) {
        cout << ">> ";
        if (!getline(cin, input)) {
            break;
        }
        commandHandler.processCommand(input);
    }
}

void Game::runOffline(const string& outputName, const int& iterations) {
    Grid currentField = universe.getField();
    for (int i = 0; i < iterations; ++i) {
        Grid nextField = universe.computeNextGeneration(currentField);
        universe.setField(nextField);
    }
    universe.display(currentField);
    try {
        FileManager::saveUniverse(universe, outputName);
        cout << "Universe saved in file " << outputName << "\n";
    } catch (const exception& ex) {
        cerr << "Error occurred while saving the universe: " << ex.what() << "\n";
    }
}
