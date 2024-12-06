#include "DumpCommandExecutor.h"

void DumpCommandExecutor::execute(const std::vector<std::string>& args, Universe& universe, bool& game_state) {
    if (args.empty()) {
        std::cerr << "Error: command dump needs a filename.\n";
        return;
    }
    std::string filename = args[0];
    try {
        FileManager::saveUniverse(universe, filename);
        std::cout << "Universe is saved in file " << filename << "\n";
    } catch (const std::exception& ex) {
        std::cerr << "Error occurred while saving universe in file " << ex.what() << "\n";
    }
}
