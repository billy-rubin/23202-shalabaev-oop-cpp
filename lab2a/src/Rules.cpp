#include "Rules.h"

Rules::Rules() {
    birth = {3};
    survival = {2,3};
}

Rules::Rules(const std::string &birthRules, const std::string &survivalRules) {
    for(int i = 1; i < birthRules.length(); i++){
        string neighbours_num = birthRules.substr(i, 1);
        birth.insert(stoi(neighbours_num));
    }
    for(int i = 1; i < survivalRules.length(); i++){
        string neighbours_num = survivalRules.substr(i, 1);
        survival.insert(stoi(neighbours_num));
    }
}

bool Rules::shouldBeSurvived(const int& neighbors) {
    if (survival.count(neighbors) == 0){
        return false;
    }
    return true;
}

bool Rules::shouldBeBorn(const int& neighbors) {
    if (birth.count(neighbors) == 0){
        return false;
    }
    return true;
}

string Rules::getRuleString() const {
    string result = "#R B";
    for (const auto& rule : birth) {
        result += std::to_string(rule);
    }
    result += "/S";
    for (const auto& rule : survival) {
        result += std::to_string(rule);
    }
    return result;
}