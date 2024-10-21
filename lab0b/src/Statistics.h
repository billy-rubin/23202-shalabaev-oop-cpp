#ifndef OOP_CPP_STATISTICS_H
#define OOP_CPP_STATISTICS_H

#include "map"
#include "string"
#include "vector"
#include "utility"

using std::map;
using std::string;
using std::vector;
using std::pair;

class Statistics {
public:
    vector<pair<string, int>> Calculate(const map<string, int>& wordFrequency);
};

#endif // OOP_CPP_STATISTICS_H
