#include "TransferToTable.h"

TransferToTable::TransferToTable() : totalWords(0) {}

void TransferToTable::addWordsToTable(const list<string>& words) {
    for (const auto& word : words) {
        wordFrequency[word]++;
    }
    totalWords += words.size();
}

const map<string, int>& TransferToTable::getWordFrequency(){
    return wordFrequency;
}

int TransferToTable::getTotalWords(){
    return totalWords;
}

