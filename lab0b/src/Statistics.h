#ifndef OOP_CPP_STATISTICS_H
#define OOP_CPP_STATISTICS_H

#include "map"
#include "string"
#include "vector"
#include "utility"
#include "string"
#include "list"

using std::map;
using std::string;
using std::vector;
using std::pair;
using std::list;

class Statistics {
private:
    map<string, int> wordFrequency;
    int totalWords;
public:
    Statistics();
    void addWordsToTable(const list<string>& words);
    const map<string, int>& getWordFrequency();
    int getTotalWords();
    void ConvertInfoIntoString(vector<string>& outputStrings, const vector<pair<string, int>>& sortedWords, int totalWords);
    vector<pair<string, int>> Calculate(const map<string, int>& wordFrequency);
};

#endif // OOP_CPP_STATISTICS_H
