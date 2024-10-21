#ifndef OOP_CPP_TRANSFERTOTABLE_H
#define OOP_CPP_TRANSFERTOTABLE_H

#include "map"
#include "string"
#include "list"

using std::map;
using std::string;
using std::list;

class TransferToTable {
private:
    map<string, int> wordFrequency;
    int totalWords;
public:
    TransferToTable();
    void addWordsToTable(const list<string>& words);
    const map<string, int>& getWordFrequency();
    int getTotalWords();
};

#endif // OOP_CPP_TRANSFERTOTABLE_H
