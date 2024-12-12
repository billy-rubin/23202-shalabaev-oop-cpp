#ifndef HELPCOMMANDEXECUTOR_H
#define HELPCOMMANDEXECUTOR_H

#include "CommandExecutor.h"
#include <iostream>

class HelpCommandExecutor : public CommandExecutor {
public:
    void execute(const std::vector<std::string>& args) override;
};

#endif // HELPCOMMANDEXECUTOR_H
