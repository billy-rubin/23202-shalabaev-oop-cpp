#ifndef TICKCOMMANDEXECUTOR_H
#define TICKCOMMANDEXECUTOR_H

#include "CommandExecutor.h"
#include <iostream>

class TickCommandExecutor : public CommandExecutor {
public:
    void execute(const std::vector<std::string>& args, Universe& universe, bool& game_state) override;
};

#endif // TICKCOMMANDEXECUTOR_H
