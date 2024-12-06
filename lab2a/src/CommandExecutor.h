#ifndef TASK_2_COMMANDEXECUTOR_H
#define TASK_2_COMMANDEXECUTOR_H

#include <vector>
#include <string>
#include "Universe.h"
#include "FileManager.h"

class CommandExecutor {
public:
    virtual ~CommandExecutor() {}
    virtual void execute(const std::vector<std::string>& args, Universe& universe, bool& game_state) = 0;
};

#endif //TASK_2_COMMANDEXECUTOR_H
