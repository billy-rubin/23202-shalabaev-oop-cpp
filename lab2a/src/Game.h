#ifndef TASK_2_GAME_H
#define TASK_2_GAME_H

#include "iostream"
#include "Universe.h"
#include "CommandHandler.h"
using namespace std;
class Game{
private:
    Universe universe;
    CommandHandler commandHandler;
public:
    explicit Game(const string& filename);
    void run();
    void runOffline(const string& outputName, const int& iterations);
};
#endif //TASK_2_GAME_H
