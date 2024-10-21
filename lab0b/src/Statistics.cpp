#include "Statistics.h"
#include <algorithm>

vector<pair<string, int>> Statistics::Calculate(const map<string, int>& wordFrequency) {
    vector<pair<string, int>> sortedWords(wordFrequency.begin(), wordFrequency.end());

    std::sort(sortedWords.begin(), sortedWords.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    return sortedWords;
}
