#include "CommandHandler.h"
#include "DumpCommandExecutor.h"
#include "TickCommandExecutor.h"
#include "ExitCommandExecutor.h"
#include "HelpCommandExecutor.h"
#include <iostream>
#include <sstream>
#include <algorithm>

CommandHandler::CommandHandler(Universe& universe) : universe(universe), game_state(true) {
    commandExecutors["dump"] = make_unique<DumpCommandExecutor>();
    commandExecutors["tick"] = make_unique<TickCommandExecutor>();
    commandExecutors["t"] = make_unique<TickCommandExecutor>();
    commandExecutors["exit"] = make_unique<ExitCommandExecutor>();
    commandExecutors["help"] = make_unique<HelpCommandExecutor>();
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

    auto it = commandExecutors.find(cmd);
    if (it != commandExecutors.end()) {
        it->second->execute(args, universe, game_state);
    } else {
        cerr << "Unknown command: " << cmd << "\n";
        cout << "Type 'help' to see the list of available commands.\n";
    }
}

bool CommandHandler::getGameState() const {
    return game_state;
}
