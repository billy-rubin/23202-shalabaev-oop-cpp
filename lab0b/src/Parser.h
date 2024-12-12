#ifndef OOP_CPP_PARSER_H
#define OOP_CPP_PARSER_H

#include "string"
#include "list"

using std::string;
using std::list;

class Parser {
public:
    list<string> Parse(const string& line);
};

#endif // OOP_CPP_PARSER_H
