#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <string>
#include <map>
#include <memory>
#include "Universe.h"
#include "CommandExecutor.h"

using namespace std;

class CommandHandler {
private:
    Universe& universe;
    bool game_state;
    map<string, unique_ptr<CommandExecutor>> commandExecutors;

public:
    explicit CommandHandler(Universe& universe);
    void processCommand(const std::string& command);
    bool getGameState() const;
};

#endif // COMMANDHANDLER_H
