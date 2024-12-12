#include "CommandHandler.h"
#include "DumpCommandExecutor.h"
#include "TickCommandExecutor.h"
#include "ExitCommandExecutor.h"
#include "HelpCommandExecutor.h"
#include <iostream>
#include <sstream>
#include <algorithm>

CommandHandler::CommandHandler(Universe& universe) : universe(universe), game_state(true) {
    commandExecutors["dump"] = new DumpCommandExecutor(universe);
    commandExecutors["tick"] = new TickCommandExecutor(universe);
    commandExecutors["t"] = new TickCommandExecutor(universe);
    commandExecutors["exit"] = new ExitCommandExecutor(game_state);
    commandExecutors["help"] = new HelpCommandExecutor();
}

CommandHandler::~CommandHandler() {
    for (auto& pair : commandExecutors) {
        delete pair.second;
    }
    commandExecutors.clear();
}

void CommandHandler::processCommand(const string& command) {
    istringstream iss(command);
    string cmd;
    vector<string> args;

    iss >> cmd;
    string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }

    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

    if (commandExecutors.count(cmd) > 0) {
        commandExecutors[cmd]->execute(args);
    } else {
        cerr << "Unknown command: " << cmd << "\n";
        cout << "Type 'help' to see the list of available commands.\n";
    }
}

bool CommandHandler::getGameState() const {
    return game_state;
}
