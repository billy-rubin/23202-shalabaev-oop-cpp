#include "DumpCommandExecutor.h"

DumpCommandExecutor::DumpCommandExecutor(Universe &universe) : universe(universe) {}

void DumpCommandExecutor::execute(const std::vector<std::string>& args) {
    FileManager fileReader;
    if (args.empty()) {
        std::cerr << "Error: command dump needs a filename.\n";
        return;
    }
    std::string filename = args[0];
    try {
        fileReader.storeUniverse(universe, filename);
        std::cout << "Universe is saved in file " << filename << "\n";
    } catch (const std::exception& ex) {
        std::cerr << "Error occurred while saving universe in file " << ex.what() << "\n";
    }
}
