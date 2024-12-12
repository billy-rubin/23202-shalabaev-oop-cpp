#ifndef TICKCOMMANDEXECUTOR_H
#define TICKCOMMANDEXECUTOR_H

#include "CommandExecutor.h"
#include <iostream>

class TickCommandExecutor : public CommandExecutor {
private:
    Universe& universe;
public:
    TickCommandExecutor(Universe& u);
    void execute(const std::vector<std::string>& args) override;
};

#endif // TICKCOMMANDEXECUTOR_H
