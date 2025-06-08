#include "HelpCommandExecutor.h"

void HelpCommandExecutor::execute(const std::vector<std::string>& args) {
    std::cout << "Available commands:\n";
    std::cout << "  dump <filename>         - dump universe in file\n";
    std::cout << "  tick <n=1> or t <n=1>  - calculate n iterations and print the result\n";
    std::cout << "  exit                    - exit the game\n";
    std::cout << "  help                    - show command description\n";
}
