#include "ExitCommandExecutor.h"

ExitCommandExecutor::ExitCommandExecutor(bool& game_state) : game_state(game_state) {}

void ExitCommandExecutor::execute(const std::vector<std::string>& args) {
    std::cout << "Finishing the game.\n";
    game_state = false;
}
