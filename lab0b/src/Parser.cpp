#include "Parser.h"
#include <cctype>

list<string> Parser::Parse(const string& line) {
    list<string> words;
    string word;
    for (char ch : line) {
        if (std::isalnum(ch)) {
            word += std::tolower(ch);
        } else if (!word.empty()) {
            words.push_back(word);
            word.clear();
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    return words;
}
