#include "ExitCommandExecutor.h"

void ExitCommandExecutor::execute(const std::vector<std::string>& args, Universe& universe, bool& game_state) {
    std::cout << "Finishing the game.\n";
    game_state = false;
}
