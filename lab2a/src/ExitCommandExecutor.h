#ifndef EXITCOMMANDEXECUTOR_H
#define EXITCOMMANDEXECUTOR_H

#include "CommandExecutor.h"
#include <iostream>

class ExitCommandExecutor : public CommandExecutor {
public:
    void execute(const std::vector<std::string>& args, Universe& universe, bool& game_state) override;
};

#endif // EXITCOMMANDEXECUTOR_H
