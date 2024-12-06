
#ifndef TASK_2_RULES_H
#define TASK_2_RULES_H

#include "iostream"
#include "set"
using namespace std;
class Rules{
private:
    set<int> birth;
    set<int> survival;
public:
    Rules();
    explicit Rules(const string& birthRules, const string& survivalRules);
    bool shouldBeBorn(const int& neighbors);
    bool shouldBeSurvived(const int& neighbors);
    string getRuleString() const;

};
#endif //TASK_2_RULES_H
