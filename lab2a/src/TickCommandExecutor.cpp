#include "TickCommandExecutor.h"

TickCommandExecutor::TickCommandExecutor(Universe& u) : universe(u) {}

void TickCommandExecutor::execute(const std::vector<std::string>& args) {
    int n = 1;
    if (!args.empty()) {
        try {
            n = std::stoi(args[0]);
            if (n <= 0) {
                std::cerr << "Error: num of iterations must be greater zero.\n";
                return;
            }
        } catch (const std::exception&) {
            std::cerr << "Error: invalid argument for iterations.\n";
            return;
        }
    }

    Grid currentField = universe.getField();
    for (int i = 0; i < n; ++i) {
        Grid nextField = universe.computeNextGeneration(currentField);
        currentField = nextField;
    }
    universe.display(currentField);
}
