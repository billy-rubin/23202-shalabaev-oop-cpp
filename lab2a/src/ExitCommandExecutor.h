#ifndef EXITCOMMANDEXECUTOR_H
#define EXITCOMMANDEXECUTOR_H

#include "CommandExecutor.h"
#include <iostream>

class ExitCommandExecutor : public CommandExecutor {
private:
    bool& game_state;
public:
    ExitCommandExecutor(bool& game_state);
    void execute(const std::vector<std::string>& args) override;
};

#endif // EXITCOMMANDEXECUTOR_H
