#ifndef LAB3_CONFIGPARSER_H
#define LAB3_CONFIGPARSER_H
#include <string>
#include <vector>
#include <memory>
#include "ConverterFactory.h"

class ConfigParser {
private:
    std::vector<std::string> lines;
public:
    ConfigParser(const std::string& filename);
    std::vector<Converter*> parse() const;
    Converter* getConverterType(std::string line) const;
};

#endif //LAB3_CONFIGPARSER_H
