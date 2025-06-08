#ifndef DUMPCOMMANDEXECUTOR_H
#define DUMPCOMMANDEXECUTOR_H

#include "CommandExecutor.h"
#include "FileManager.h"
#include <iostream>

class DumpCommandExecutor : public CommandExecutor {
private:
    Universe& universe;
public:
    DumpCommandExecutor(Universe& universe);
    void execute(const std::vector<std::string>& args) override;
};

#endif
