#include "Statistics.h"
#include <algorithm>
#include "iostream"

Statistics::Statistics() : totalWords(0) {}

void Statistics::addWordsToTable(const list<string>& words) {
    for (const auto& word : words) {
        wordFrequency[word]++;
    }
    totalWords += words.size();
}

const map<string, int>& Statistics::getWordFrequency(){
    return wordFrequency;
}

int Statistics::getTotalWords(){
    return totalWords;
}

vector<pair<string, int>> Statistics::Calculate(const map<string, int>& wordFrequency) {
    vector<pair<string, int>> sortedWords(wordFrequency.begin(), wordFrequency.end());

    std::sort(sortedWords.begin(), sortedWords.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    return sortedWords;
}

void Statistics::ConvertInfoIntoString(vector<string>& outputStrings, const vector<pair<string, int>>& sortedWords, int amountOfWords) {
    for (size_t i = 0; i < sortedWords.size(); i++) {
        const auto& [word, frequency] = sortedWords[i];
        double percentage = (frequency * 100.0) / amountOfWords;
        outputStrings[i] = word + "," + std::to_string(frequency) + "," + std::to_string(percentage);
    }
}

