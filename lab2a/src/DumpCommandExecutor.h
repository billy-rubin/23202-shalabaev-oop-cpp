#ifndef DUMPCOMMANDEXECUTOR_H
#define DUMPCOMMANDEXECUTOR_H

#include "CommandExecutor.h"
#include "FileManager.h"
#include <iostream>

class DumpCommandExecutor : public CommandExecutor {
public:
    void execute(const std::vector<std::string>& args, Universe& universe, bool& game_state) override;
};

#endif
